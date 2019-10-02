// Copyright 2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include "esp_flash_partitions.h"
#include "esp_image_format.h"
#include "esp_app_format.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Type of hold a GPIO in low state
typedef enum {
    GPIO_LONG_HOLD  = 1,    /*!< The long hold GPIO */
    GPIO_SHORT_HOLD = -1,   /*!< The short hold GPIO */
    GPIO_NOT_HOLD   = 0     /*!< If the GPIO input is not low */
} esp_comm_gpio_hold_t;

/**
 * @brief Calculate crc for the OTA data select.
 *
 * @param[in] s The OTA data select.
 * @return    Returns crc value.
 */
uint32_t bootloader_common_ota_select_crc(const esp_ota_select_entry_t *s);

/**
 * @brief Verifies the validity of the OTA data select
 *
 * @param[in] s The OTA data select.
 * @return    Returns true on valid, false otherwise.
 */
bool bootloader_common_ota_select_valid(const esp_ota_select_entry_t *s);

/**
 * @brief Returns true if OTADATA is not marked as bootable partition.
 *
 * @param[in] s The OTA data select.
 * @return    Returns true if OTADATA invalid, false otherwise.
 */
bool bootloader_common_ota_select_invalid(const esp_ota_select_entry_t *s);

/**
 * @brief Check if the GPIO input is a long hold or a short hold.
 *
 * Number of the GPIO input will be configured as an input with internal pull-up enabled.
 * If the GPIO input is held low continuously for delay_sec period then it is a long hold.
 * If the GPIO input is held low for less period then it is a short hold.
 *
 * @param[in] num_pin Number of the GPIO input.
 * @param[in] delay_sec Input must be driven low for at least this long, continuously.
 * @return esp_comm_gpio_hold_t Defines type of hold a GPIO in low state.
 */
esp_comm_gpio_hold_t bootloader_common_check_long_hold_gpio(uint32_t num_pin, uint32_t delay_sec);

/**
 * @brief Erase the partition data that is specified in the transferred list.
 *
 * @param[in] list_erase String containing a list of cleared partitions. Like this "nvs, phy". The string must be null-terminal.
 * @param[in] ota_data_erase If true then the OTA data partition will be cleared (if there is it in partition table).
 * @return    Returns true on success, false otherwise.
 */
bool bootloader_common_erase_part_type_data(const char *list_erase, bool ota_data_erase);

/**
 * @brief Determines if the list contains the label
 *
 * @param[in] list  A string of names delimited by commas or spaces. Like this "nvs, phy, data". The string must be null-terminated.
 * @param[in] label The substring that will be searched in the list.
 * @return    Returns true if the list contains the label, false otherwise.
 */
bool bootloader_common_label_search(const char *list, char *label);

/**
 * @brief Configure default SPI pin modes and drive strengths
 *
 * @param drv GPIO drive level (determined by clock frequency)
 */
void bootloader_configure_spi_pins(int drv);

/**
 * @brief Calculates a sha-256 for a given partition or returns a appended digest.
 *
 * This function can be used to return the SHA-256 digest of application, bootloader and data partitions.
 * For apps with SHA-256 appended to the app image, the result is the appended SHA-256 value for the app image content.
 * The hash is verified before returning, if app content is invalid then the function returns ESP_ERR_IMAGE_INVALID.
 * For apps without SHA-256 appended to the image, the result is the SHA-256 of all bytes in the app image.
 * For other partition types, the result is the SHA-256 of the entire partition.
 *
 * @param[in]  address      Address of partition.
 * @param[in]  size         Size of partition.
 * @param[in]  type         Type of partition. For applications the type is 0, otherwise type is data.
 * @param[out] out_sha_256  Returned SHA-256 digest for a given partition.
 *
 * @return
 *          - ESP_OK: In case of successful operation.
 *          - ESP_ERR_INVALID_ARG: The size was 0 or the sha_256 was NULL.
 *          - ESP_ERR_NO_MEM: Cannot allocate memory for sha256 operation.
 *          - ESP_ERR_IMAGE_INVALID: App partition doesn't contain a valid app image.
 *          - ESP_FAIL: An allocation error occurred.
 */
esp_err_t bootloader_common_get_sha256_of_partition(uint32_t address, uint32_t size, int type, uint8_t *out_sha_256);

/**
 * @brief Returns the number of active otadata.
 *
 * @param[in] two_otadata Pointer on array from two otadata structures.
 *
 * @return The number of active otadata (0 or 1).
 *        - -1: If it does not have active otadata.
 */
int bootloader_common_get_active_otadata(esp_ota_select_entry_t *two_otadata);

/**
 * @brief Returns the number of active otadata.
 *
 * @param[in] two_otadata       Pointer on array from two otadata structures.
 * @param[in] valid_two_otadata Pointer on array from two bools. True means select.
 * @param[in] max               True - will select the maximum ota_seq number, otherwise the minimum.
 *
 * @return The number of active otadata (0 or 1).
 *        - -1: If it does not have active otadata.
 */
int bootloader_common_select_otadata(const esp_ota_select_entry_t *two_otadata, bool *valid_two_otadata, bool max);

/**
 * @brief Returns esp_app_desc structure for app partition. This structure includes app version.
 *
 * Returns a description for the requested app partition.
 * @param[in] partition      App partition description.
 * @param[out] app_desc      Structure of info about app.
 * @return
 *  - ESP_OK:                Successful.
 *  - ESP_ERR_INVALID_ARG:   The arguments passed are not valid.
 *  - ESP_ERR_NOT_FOUND:     app_desc structure is not found. Magic word is incorrect.
 *  - ESP_FAIL:              mapping is fail.
 */
esp_err_t bootloader_common_get_partition_description(const esp_partition_pos_t *partition, esp_app_desc_t *app_desc);

/**
 * @brief Get chip revision
 *
 * @return Chip revision number
 */
uint8_t bootloader_common_get_chip_revision(void);

/**
 * @brief Check if the image (bootloader and application) has valid chip ID and revision
 *
 * @param img_hdr: image header
 * @return
 *      - ESP_OK: image and chip are matched well
 *      - ESP_FAIL: image doesn't match to the chip
 */
esp_err_t bootloader_common_check_chip_validity(const esp_image_header_t* img_hdr);

/**
 * @brief Configure VDDSDIO, call this API to rise VDDSDIO to 1.9V when VDDSDIO regulator is enabled as 1.8V mode.
 */
void bootloader_common_vddsdio_configure(void);

#if defined( CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP ) || defined( CONFIG_BOOTLOADER_CUSTOM_RESERVE_RTC )
/**
 * @brief Returns partition from rtc_retain_mem
 *
 * Uses to get the partition of application which was worked before to go to the deep sleep.
 * This partition was stored in rtc_retain_mem.
 * Note: This function operates the RTC FAST memory which available only for PRO_CPU.
 *       Make sure that this function is used only PRO_CPU.
 *
 * @return partition: If rtc_retain_mem is valid.
 *        - NULL: If it is not valid.
 */
esp_partition_pos_t* bootloader_common_get_rtc_retain_mem_partition(void);

/**
 * @brief Update the partition and reboot_counter in rtc_retain_mem.
 *
 * This function saves the partition of application for fast booting from the deep sleep.
 * An algorithm uses this partition to avoid reading the otadata and does not validate an image.
 * Note: This function operates the RTC FAST memory which available only for PRO_CPU.
 *       Make sure that this function is used only PRO_CPU.
 *
 * @param[in] partition      App partition description. Can be NULL, in this case rtc_retain_mem.partition is not updated.
 * @param[in] reboot_counter If true then update reboot_counter.
 *
 */
void bootloader_common_update_rtc_retain_mem(esp_partition_pos_t* partition, bool reboot_counter);

/**
 * @brief Reset entire rtc_retain_mem.
 *
 * Note: This function operates the RTC FAST memory which available only for PRO_CPU.
 *       Make sure that this function is used only PRO_CPU.
 */
void bootloader_common_reset_rtc_retain_mem(void);

/**
 * @brief Returns reboot_counter from rtc_retain_mem
 *
 * The reboot_counter counts the number of reboots. Reset only when power is off.
 * The very first launch of the application will be from 1.
 * Overflow is not possible, it will stop at the value UINT16_MAX.
 * Note: This function operates the RTC FAST memory which available only for PRO_CPU.
 *       Make sure that this function is used only PRO_CPU.
 *
 * @return reboot_counter: 1..65535
 *         - 0: If rtc_retain_mem is not valid.
 */
uint16_t bootloader_common_get_rtc_retain_mem_reboot_counter(void);

/**
 * @brief Returns rtc_retain_mem
 *
 * Note: This function operates the RTC FAST memory which available only for PRO_CPU.
 *       Make sure that this function is used only PRO_CPU.
 *
 * @return rtc_retain_mem
 */
rtc_retain_mem_t* bootloader_common_get_rtc_retain_mem(void);

#endif

#ifdef __cplusplus
}
#endif
