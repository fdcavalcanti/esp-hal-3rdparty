// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __ESP_PARTITION_H__
#define __ESP_PARTITION_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"
#include "esp_spi_flash.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_PARTITION_TYPE_APP = 0x00,
    ESP_PARTITION_TYPE_DATA = 0x01,
    ESP_PARTITION_TYPE_FILESYSTEM = 0x02,
} esp_partition_type_t;

typedef enum {
    ESP_PARTITION_SUBTYPE_APP_FACTORY = 0x00,
    ESP_PARTITION_SUBTYPE_APP_OTA_MIN = 0x10,
    ESP_PARTITION_SUBTYPE_APP_OTA_0 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 0,
    ESP_PARTITION_SUBTYPE_APP_OTA_1 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 1,
    ESP_PARTITION_SUBTYPE_APP_OTA_2 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 2,
    ESP_PARTITION_SUBTYPE_APP_OTA_3 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 3,
    ESP_PARTITION_SUBTYPE_APP_OTA_4 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 4,
    ESP_PARTITION_SUBTYPE_APP_OTA_5 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 5,
    ESP_PARTITION_SUBTYPE_APP_OTA_6 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 6,
    ESP_PARTITION_SUBTYPE_APP_OTA_7 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 7,
    ESP_PARTITION_SUBTYPE_APP_OTA_8 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 8,
    ESP_PARTITION_SUBTYPE_APP_OTA_9 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 9,
    ESP_PARTITION_SUBTYPE_APP_OTA_10 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 10,
    ESP_PARTITION_SUBTYPE_APP_OTA_11 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 11,
    ESP_PARTITION_SUBTYPE_APP_OTA_12 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 12,
    ESP_PARTITION_SUBTYPE_APP_OTA_13 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 13,
    ESP_PARTITION_SUBTYPE_APP_OTA_14 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 14,
    ESP_PARTITION_SUBTYPE_APP_OTA_15 = ESP_PARTITION_SUBTYPE_APP_OTA_MIN + 15,
    ESP_PARTITION_SUBTYPE_APP_OTA_MAX = 15,
    ESP_PARTITION_SUBTYPE_APP_TEST = 0x20,

    ESP_PARTITION_SUBTYPE_DATA_OTA = 0x00,
    ESP_PARTITION_SUBTYPE_DATA_RF =  0x01,
    ESP_PARTITION_SUBTYPE_DATA_NVS = 0x02,

    ESP_PARTITION_SUBTYPE_FILESYSTEM_ESPHTTPD = 0x00,
    ESP_PARTITION_SUBTYPE_FILESYSTEM_FAT = 0x01,
    ESP_PARTITION_SUBTYPE_FILESYSTEM_SPIFFS = 0x02,

    ESP_PARTITION_SUBTYPE_ANY = 0xff,
} esp_partition_subtype_t;

#define ESP_PARTITION_SUBTYPE_OTA(i) ((esp_partition_subtype_t)(ESP_PARTITION_SUBTYPE_APP_OTA_MIN + ((i) & 0xf)))


typedef struct esp_partition_iterator_opaque_* esp_partition_iterator_t;

typedef struct {
    esp_partition_type_t type;
    esp_partition_subtype_t subtype;
    uint32_t address;
    uint32_t size;
    char label[17];
    bool encrypted;
} esp_partition_t;

/**
 * @brief Find partition based on one or more parameters
 *
 * @param type Partition type, one of esp_partition_type_t values
 * @param subtype Partition subtype, of esp_partition_subtype_t values.
 *             To find all partitions of given type, use
 *             ESP_PARTITION_SUBTYPE_ANY.
 * @param label (optional) Partition label. Set this value if looking
 *             for partition with a specific name. Pass NULL otherwise.
 *
 * @return iterator which can be used to enumerate all the partitions found,
 *         or NULL if no partitions were found.
 *         Iterator obtained through this function has to be released
 *         using esp_partition_iterator_release when not used any more.
 */
esp_partition_iterator_t esp_partition_find(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* label);

/**
 * @brief Find first partition based on one or more parameters
 *
 * @param type Partition type, one of esp_partition_type_t values
 * @param subtype Partition subtype, of esp_partition_subtype_t values.
 *             To find all partitions of given type, use
 *             ESP_PARTITION_SUBTYPE_ANY.
 * @param label (optional) Partition label. Set this value if looking
 *             for partition with a specific name. Pass NULL otherwise.
 *
 * @return pointer to esp_partition_t structure, or NULL if no parition is found.
 *         This pointer is valid for the lifetime of the application.
 */
const esp_partition_t* esp_partition_find_first(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* label);

/**
 * @brief Get esp_partition_t structure for given partition
 *
 * @param iterator  Iterator obtained using esp_partition_find. Must be non-NULL.
 *
 * @return pointer to esp_partition_t structure. This pointer is valid for the lifetime
 *         of the application.
 */
const esp_partition_t* esp_partition_get(esp_partition_iterator_t iterator);

/**
 * @brief Move partition iterator to the next partition found
 *
 * Any copies of the iterator will be invalid after this call.
 *
 * @param iterator Iterator obtained using esp_partition_find. Must be non-NULL.
 *
 * @return NULL if no partition was found, valid esp_partition_iterator_t otherwise.
 */
esp_partition_iterator_t esp_partition_next(esp_partition_iterator_t iterator);

/**
 * @brief Release partition iterator
 *
 * Any pointers obtained using esp_partition_label function will be invalid
 * after this call.
 *
 * @param iterator Iterator obtained using esp_partition_find. Must be non-NULL.
 *
 */
void esp_partition_iterator_release(esp_partition_iterator_t iterator);

/**
 * @brief Read data from the partition
 *
 * @param partition Pointer to partition structure obtained using
 *                  esp_partition_find_first or esp_partition_get.
 *                  Must be non-NULL.
 * @param dst Pointer to the buffer where data should be stored.
 *            Pointer must be non-NULL and buffer must be at least 'size' bytes long.
 * @param src_offset Address of the data to be read, relative to the
 *                   beginning of the partition.
 * @param size Size of data to be read, in bytes.
 *
 * @return ESP_OK, if data was read successfully;
 *         ESP_ERR_INVALID_ARG, if iterator or src are NULL;
 *         ESP_ERR_INVALID_SIZE, if read would go out of bounds of the partition;
 *         or one of error codes from lower-level flash driver.
 */
esp_err_t esp_partition_read(const esp_partition_t* partition,
                             size_t src_offset, void* dst, size_t size);

/**
 * @brief Write data to the partition
 *
 * Before writing data to flash, corresponding region of flash needs to be erased.
 * This can be done using esp_partition_erase_range function.
 *
 * @param partition Pointer to partition structure obtained using
 *                  esp_partition_find_first or esp_partition_get.
 *                  Must be non-NULL.
 * @param dst_offset Address where the data should be written, relative to the
 *                   beginning of the partition.
 * @param src Pointer to the source buffer.  Pointer must be non-NULL and
 *            buffer must be at least 'size' bytes long.
 * @param size Size of data to be written, in bytes.
 *
 * @note Prior to writing to flash memory, make sure it has been erased with
 *       esp_partition_erase_range call.
 *
 * @return ESP_OK, if data was written successfully;
 *         ESP_ERR_INVALID_ARG, if iterator or dst are NULL;
 *         ESP_ERR_INVALID_SIZE, if write would go out of bounds of the partition;
 *         or one of error codes from lower-level flash driver.
 */
esp_err_t esp_partition_write(const esp_partition_t* partition,
                             size_t dst_offset, const void* src, size_t size);

/**
 * @brief Erase part of the partition
 *
 * @param partition Pointer to partition structure obtained using
 *                  esp_partition_find_first or esp_partition_get.
 *                  Must be non-NULL.
 * @param start_addr Address where erase operation should start. Must be aligned
 *                   to 4 kilobytes.
 * @param size Size of the range which should be erased, in bytes.
 *                   Must be divisible by 4 kilobytes.
 *
 * @return ESP_OK, if the range was erased successfully;
 *         ESP_ERR_INVALID_ARG, if iterator or dst are NULL;
 *         ESP_ERR_INVALID_SIZE, if erase would go out of bounds of the partition;
 *         or one of error codes from lower-level flash driver.
 */
esp_err_t esp_partition_erase_range(const esp_partition_t* partition,
                                    uint32_t start_addr, uint32_t size);

/**
 * @brief Configure MMU to map partition into data memory
 *
 * Unlike spi_flash_mmap function, which requires a 64kB aligned base address,
 * this function doesn't impose such a requirement.
 * If offset results in a flash address which is not aligned to 64kB boundary,
 * address will be rounded to the lower 64kB boundary, so that mapped region
 * includes requested range.
 * Pointer returned via out_ptr argument will be adjusted to point to the
 * requested offset (not necessarily to the beginning of mmap-ed region).
 *
 * To release mapped memory, pass handle returned via out_handle argument to
 * spi_flash_munmap function.
 *
 * @param partition Pointer to partition structure obtained using
 *                  esp_partition_find_first or esp_partition_get.
 *                  Must be non-NULL.
 * @param offset Offset from the beginning of partition where mapping should start.
 * @param size Size of the area to be mapped.
 * @param memory  Memory space where the region should be mapped
 * @param out_ptr  Output, pointer to the mapped memory region
 * @param out_handle  Output, handle which should be used for spi_flash_munmap call
 *
 * @return ESP_OK, if successful
 */
esp_err_t esp_partition_mmap(const esp_partition_t* partition, uint32_t offset, uint32_t size,
                             spi_flash_mmap_memory_t memory,
                             const void** out_ptr, spi_flash_mmap_handle_t* out_handle);


#ifdef __cplusplus
}
#endif


#endif /* __ESP_PARTITION_H__ */
