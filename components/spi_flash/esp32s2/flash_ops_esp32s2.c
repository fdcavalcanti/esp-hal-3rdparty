/*
 * SPDX-FileCopyrightText: 2018-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <sys/param.h>

#include "esp_spi_flash.h"
#include "soc/system_reg.h"
#include "soc/soc_memory_layout.h"
#include "esp32s2/rom/spi_flash.h"
#include "esp32s2/rom/cache.h"
#include "bootloader_flash.h"
#include "hal/spi_flash_hal.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_rom_spiflash.h"

static const char *TAG = "spiflash_s2";

#define SPICACHE SPIMEM0
#define SPIFLASH SPIMEM1

extern void IRAM_ATTR flash_rom_init(void);
esp_rom_spiflash_result_t IRAM_ATTR spi_flash_write_encrypted_chip(size_t dest_addr, const void *src, size_t size)
{
    const spi_flash_guard_funcs_t *ops = spi_flash_guard_get();
    esp_rom_spiflash_result_t rc;

    assert((dest_addr % 16) == 0);
    assert((size % 16) == 0);

    if (!esp_ptr_internal(src)) {
        uint8_t block[128]; // Need to buffer in RAM as we write
        while (size > 0) {
            size_t next_block = MIN(size, sizeof(block));
            memcpy(block, src, next_block);

            esp_rom_spiflash_result_t r = spi_flash_write_encrypted_chip(dest_addr, block, next_block);
            if (r != ESP_ROM_SPIFLASH_RESULT_OK) {
                return r;
            }

            size -= next_block;
            dest_addr += next_block;
            src = ((uint8_t *)src) + next_block;
        }
        bzero(block, sizeof(block));

        return ESP_ROM_SPIFLASH_RESULT_OK;
    }
    else { // Already in internal memory
        ESP_LOGV(TAG, "calling SPI_Encrypt_Write addr 0x%x src %p size 0x%x", dest_addr, src, size);

#ifndef CONFIG_SPI_FLASH_USE_LEGACY_IMPL
        /* The ROM function SPI_Encrypt_Write assumes ADDR_BITLEN is already set but new
           implementation doesn't automatically set this to a usable value */
        SPIFLASH.user1.usr_addr_bitlen = 23;
#endif

        if (ops && ops->start) {
            ops->start();
        }
        flash_rom_init();
        rc = esp_rom_spiflash_write_encrypted(dest_addr, (uint32_t*)src, size);
        if (ops && ops->end) {
            ops->end();
        }
        return rc;
    }
}

esp_err_t spi_flash_wrap_set(spi_flash_wrap_mode_t mode)
{
    return bootloader_flash_wrap_set(mode);
}

esp_err_t spi_flash_enable_wrap(uint32_t wrap_size)
{
    switch(wrap_size) {
        case 8:
            return bootloader_flash_wrap_set(FLASH_WRAP_MODE_8B);
        case 16:
            return bootloader_flash_wrap_set(FLASH_WRAP_MODE_16B);
        case 32:
            return bootloader_flash_wrap_set(FLASH_WRAP_MODE_32B);
        case 64:
            return bootloader_flash_wrap_set(FLASH_WRAP_MODE_64B);
        default:
            return ESP_FAIL;
    }
}

void spi_flash_disable_wrap(void)
{
    bootloader_flash_wrap_set(FLASH_WRAP_MODE_DISABLE);
}

bool spi_flash_support_wrap_size(uint32_t wrap_size)
{
    if (!REG_GET_BIT(SPI_MEM_CTRL_REG(0), SPI_MEM_FREAD_QIO) || !REG_GET_BIT(SPI_MEM_CTRL_REG(0), SPI_MEM_FASTRD_MODE)){
        return ESP_FAIL;
    }
    switch(wrap_size) {
        case 0:
        case 8:
        case 16:
        case 32:
        case 64:
            return true;
        default:
            return false;
    }
}
