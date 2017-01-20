#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include <unity.h>
#include <esp_spi_flash.h>
#include <esp_attr.h>
#include <esp_flash_encrypt.h>

#include "test_config.h"

static uint32_t buffer[1024];

/* read-only region used for mmap tests */
static const uint32_t start = 0x100000;
static const uint32_t end = 0x200000;


TEST_CASE("Prepare data for mmap tests", "[mmap]")
{
    srand(0);
    for (int block = start / 0x10000; block < end / 0x10000; ++block) {
        printf("Writing block %d\n", block);
        for (int sector = 0; sector < 16; ++sector) {
            for (uint32_t word = 0; word < 1024; ++word) {
                uint32_t val = rand();
                if (block == start / 0x10000 && sector == 0 && word == 0) {
                    printf("first word: %08x\n", val);
                }
                buffer[word] = val;
            }
            uint32_t abs_sector = (block) * 16 + sector;
            printf("Writing sector %d\n", abs_sector);
            ESP_ERROR_CHECK( spi_flash_erase_sector((uint16_t) abs_sector) );
            ESP_ERROR_CHECK( spi_flash_write(abs_sector * SPI_FLASH_SEC_SIZE, (const uint8_t *) buffer, sizeof(buffer)) );
        }
    }
}

TEST_CASE("Can mmap into data address space", "[mmap]")
{

    printf("Mapping %x (+%x)\n", start, end - start);
    spi_flash_mmap_handle_t handle1;
    const void *ptr1;
    ESP_ERROR_CHECK( spi_flash_mmap(start, end - start, SPI_FLASH_MMAP_DATA, &ptr1, &handle1) );
    printf("mmap_res: handle=%d ptr=%p\n", handle1, ptr1);

    spi_flash_mmap_dump();

    srand(0);
    const uint32_t *data = (const uint32_t *) ptr1;
    for (int block = 0; block < (end - start) / 0x10000; ++block) {
        for (int sector = 0; sector < 16; ++sector) {
            for (uint32_t word = 0; word < 1024; ++word) {
                TEST_ASSERT_EQUAL_UINT32(rand(), data[(block * 16 + sector) * 1024 + word]);
            }
        }
    }
    printf("Mapping %x (+%x)\n", start - 0x10000, 0x20000);
    spi_flash_mmap_handle_t handle2;
    const void *ptr2;
    ESP_ERROR_CHECK( spi_flash_mmap(start - 0x10000, 0x20000, SPI_FLASH_MMAP_DATA, &ptr2, &handle2) );
    printf("mmap_res: handle=%d ptr=%p\n", handle2, ptr2);
    spi_flash_mmap_dump();

    printf("Mapping %x (+%x)\n", start, 0x10000);
    spi_flash_mmap_handle_t handle3;
    const void *ptr3;
    ESP_ERROR_CHECK( spi_flash_mmap(start, 0x10000, SPI_FLASH_MMAP_DATA, &ptr3, &handle3) );
    printf("mmap_res: handle=%d ptr=%p\n", handle3, ptr3);
    spi_flash_mmap_dump();

    printf("Unmapping handle1\n");
    spi_flash_munmap(handle1);
    spi_flash_mmap_dump();

    printf("Unmapping handle2\n");
    spi_flash_munmap(handle2);
    spi_flash_mmap_dump();

    printf("Unmapping handle3\n");
    spi_flash_munmap(handle3);
}

TEST_CASE("flash_mmap invalidates just-written data", "[spi_flash]")
{
    spi_flash_mmap_handle_t handle1;
    const void *ptr1;

    const size_t test_size = 128;

    if (esp_flash_encryption_enabled()) {
        TEST_IGNORE_MESSAGE("flash encryption enabled, spi_flash_write_encrypted() test won't pass as-is");
    }

    ESP_ERROR_CHECK( spi_flash_erase_sector(TEST_REGION_START / SPI_FLASH_SEC_SIZE) );

    /* map erased test region to ptr1 */
    ESP_ERROR_CHECK( spi_flash_mmap(TEST_REGION_START, test_size, SPI_FLASH_MMAP_DATA, &ptr1, &handle1) );
    printf("mmap_res ptr1: handle=%d ptr=%p\n", handle1, ptr1);

    /* verify it's all 0xFF */
    for (int i = 0; i < test_size; i++) {
        TEST_ASSERT_EQUAL_HEX(0xFF, ((uint8_t *)ptr1)[i]);
    }

    /* unmap the erased region */
    spi_flash_munmap(handle1);

    /* write flash region to 0xEE */
    uint8_t buf[test_size];
    memset(buf, 0xEE, test_size);
    ESP_ERROR_CHECK( spi_flash_write(TEST_REGION_START, buf, test_size) );

    /* re-map the test region at ptr1.

       this is a fresh mmap call so should trigger a cache flush,
       ensuring we see the updated flash.
    */
    ESP_ERROR_CHECK( spi_flash_mmap(TEST_REGION_START, test_size, SPI_FLASH_MMAP_DATA, &ptr1, &handle1) );
    printf("mmap_res ptr1 #2: handle=%d ptr=%p\n", handle1, ptr1);

    /* assert that ptr1 now maps to the new values on flash,
       ie contents of buf array.
    */
    TEST_ASSERT_EQUAL_HEX8_ARRAY(buf, ptr1, test_size);

    spi_flash_munmap(handle1);
}
