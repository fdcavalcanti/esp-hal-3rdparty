/*
 * SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hal/regi2c_impl.h"
#include "esp_rom_regi2c.h"

uint8_t _regi2c_impl_read(uint8_t block, uint8_t host_id, uint8_t reg_add)
{
  return esp_rom_regi2c_read(block, host_id, reg_add);
}

uint8_t _regi2c_impl_read_mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb)
{
  return esp_rom_regi2c_read_mask(block, host_id, reg_add, msb, lsb);
}

void _regi2c_impl_write(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t data)
{
  esp_rom_regi2c_write(block, host_id, reg_add, data);
}

void _regi2c_impl_write_mask(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t msb, uint8_t lsb, uint8_t data)
{
  esp_rom_regi2c_write_mask(block, host_id, reg_add, msb, lsb, data);
}
