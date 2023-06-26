/**
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 *  SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/** LPINTR_SW_INT_RAW_REG register
 *  need_des
 */
#define LPINTR_SW_INT_RAW_REG (DR_REG_LPINTR_BASE + 0x0)
/** LPINTR_LP_SW_INT_RAW : R/W/WTC; bitpos: [31]; default: 0;
 *  need_des
 */
#define LPINTR_LP_SW_INT_RAW    (BIT(31))
#define LPINTR_LP_SW_INT_RAW_M  (LPINTR_LP_SW_INT_RAW_V << LPINTR_LP_SW_INT_RAW_S)
#define LPINTR_LP_SW_INT_RAW_V  0x00000001U
#define LPINTR_LP_SW_INT_RAW_S  31

/** LPINTR_SW_INT_ST_REG register
 *  need_des
 */
#define LPINTR_SW_INT_ST_REG (DR_REG_LPINTR_BASE + 0x4)
/** LPINTR_LP_SW_INT_ST : RO; bitpos: [31]; default: 0;
 *  need_des
 */
#define LPINTR_LP_SW_INT_ST    (BIT(31))
#define LPINTR_LP_SW_INT_ST_M  (LPINTR_LP_SW_INT_ST_V << LPINTR_LP_SW_INT_ST_S)
#define LPINTR_LP_SW_INT_ST_V  0x00000001U
#define LPINTR_LP_SW_INT_ST_S  31

/** LPINTR_SW_INT_ENA_REG register
 *  need_des
 */
#define LPINTR_SW_INT_ENA_REG (DR_REG_LPINTR_BASE + 0x8)
/** LPINTR_LP_SW_INT_ENA : R/W; bitpos: [31]; default: 0;
 *  need_des
 */
#define LPINTR_LP_SW_INT_ENA    (BIT(31))
#define LPINTR_LP_SW_INT_ENA_M  (LPINTR_LP_SW_INT_ENA_V << LPINTR_LP_SW_INT_ENA_S)
#define LPINTR_LP_SW_INT_ENA_V  0x00000001U
#define LPINTR_LP_SW_INT_ENA_S  31

/** LPINTR_SW_INT_CLR_REG register
 *  need_des
 */
#define LPINTR_SW_INT_CLR_REG (DR_REG_LPINTR_BASE + 0xc)
/** LPINTR_LP_SW_INT_CLR : WT; bitpos: [31]; default: 0;
 *  need_des
 */
#define LPINTR_LP_SW_INT_CLR    (BIT(31))
#define LPINTR_LP_SW_INT_CLR_M  (LPINTR_LP_SW_INT_CLR_V << LPINTR_LP_SW_INT_CLR_S)
#define LPINTR_LP_SW_INT_CLR_V  0x00000001U
#define LPINTR_LP_SW_INT_CLR_S  31

/** LPINTR_STATUS_REG register
 *  need_des
 */
#define LPINTR_STATUS_REG (DR_REG_LPINTR_BASE + 0x10)
/** LPINTR_LP_HUK_INTR_ST : RO; bitpos: [10]; default: 0;
 *  need_des
 */
#define LPINTR_LP_HUK_INTR_ST    (BIT(10))
#define LPINTR_LP_HUK_INTR_ST_M  (LPINTR_LP_HUK_INTR_ST_V << LPINTR_LP_HUK_INTR_ST_S)
#define LPINTR_LP_HUK_INTR_ST_V  0x00000001U
#define LPINTR_LP_HUK_INTR_ST_S  10
/** LPINTR_SYSREG_INTR_ST : RO; bitpos: [11]; default: 0;
 *  need_des
 */
#define LPINTR_SYSREG_INTR_ST    (BIT(11))
#define LPINTR_SYSREG_INTR_ST_M  (LPINTR_SYSREG_INTR_ST_V << LPINTR_SYSREG_INTR_ST_S)
#define LPINTR_SYSREG_INTR_ST_V  0x00000001U
#define LPINTR_SYSREG_INTR_ST_S  11
/** LPINTR_LP_SW_INTR_ST : RO; bitpos: [12]; default: 0;
 *  need_des
 */
#define LPINTR_LP_SW_INTR_ST    (BIT(12))
#define LPINTR_LP_SW_INTR_ST_M  (LPINTR_LP_SW_INTR_ST_V << LPINTR_LP_SW_INTR_ST_S)
#define LPINTR_LP_SW_INTR_ST_V  0x00000001U
#define LPINTR_LP_SW_INTR_ST_S  12
/** LPINTR_LP_EFUSE_INTR_ST : RO; bitpos: [13]; default: 0;
 *  need_des
 */
#define LPINTR_LP_EFUSE_INTR_ST    (BIT(13))
#define LPINTR_LP_EFUSE_INTR_ST_M  (LPINTR_LP_EFUSE_INTR_ST_V << LPINTR_LP_EFUSE_INTR_ST_S)
#define LPINTR_LP_EFUSE_INTR_ST_V  0x00000001U
#define LPINTR_LP_EFUSE_INTR_ST_S  13
/** LPINTR_LP_UART_INTR_ST : RO; bitpos: [14]; default: 0;
 *  need_des
 */
#define LPINTR_LP_UART_INTR_ST    (BIT(14))
#define LPINTR_LP_UART_INTR_ST_M  (LPINTR_LP_UART_INTR_ST_V << LPINTR_LP_UART_INTR_ST_S)
#define LPINTR_LP_UART_INTR_ST_V  0x00000001U
#define LPINTR_LP_UART_INTR_ST_S  14
/** LPINTR_LP_TSENS_INTR_ST : RO; bitpos: [15]; default: 0;
 *  need_des
 */
#define LPINTR_LP_TSENS_INTR_ST    (BIT(15))
#define LPINTR_LP_TSENS_INTR_ST_M  (LPINTR_LP_TSENS_INTR_ST_V << LPINTR_LP_TSENS_INTR_ST_S)
#define LPINTR_LP_TSENS_INTR_ST_V  0x00000001U
#define LPINTR_LP_TSENS_INTR_ST_S  15
/** LPINTR_LP_TOUCH_INTR_ST : RO; bitpos: [16]; default: 0;
 *  need_des
 */
#define LPINTR_LP_TOUCH_INTR_ST    (BIT(16))
#define LPINTR_LP_TOUCH_INTR_ST_M  (LPINTR_LP_TOUCH_INTR_ST_V << LPINTR_LP_TOUCH_INTR_ST_S)
#define LPINTR_LP_TOUCH_INTR_ST_V  0x00000001U
#define LPINTR_LP_TOUCH_INTR_ST_S  16
/** LPINTR_LP_SPI_INTR_ST : RO; bitpos: [17]; default: 0;
 *  need_des
 */
#define LPINTR_LP_SPI_INTR_ST    (BIT(17))
#define LPINTR_LP_SPI_INTR_ST_M  (LPINTR_LP_SPI_INTR_ST_V << LPINTR_LP_SPI_INTR_ST_S)
#define LPINTR_LP_SPI_INTR_ST_V  0x00000001U
#define LPINTR_LP_SPI_INTR_ST_S  17
/** LPINTR_LP_I2S_INTR_ST : RO; bitpos: [18]; default: 0;
 *  need_des
 */
#define LPINTR_LP_I2S_INTR_ST    (BIT(18))
#define LPINTR_LP_I2S_INTR_ST_M  (LPINTR_LP_I2S_INTR_ST_V << LPINTR_LP_I2S_INTR_ST_S)
#define LPINTR_LP_I2S_INTR_ST_V  0x00000001U
#define LPINTR_LP_I2S_INTR_ST_S  18
/** LPINTR_LP_I2C_INTR_ST : RO; bitpos: [19]; default: 0;
 *  need_des
 */
#define LPINTR_LP_I2C_INTR_ST    (BIT(19))
#define LPINTR_LP_I2C_INTR_ST_M  (LPINTR_LP_I2C_INTR_ST_V << LPINTR_LP_I2C_INTR_ST_S)
#define LPINTR_LP_I2C_INTR_ST_V  0x00000001U
#define LPINTR_LP_I2C_INTR_ST_S  19
/** LPINTR_LP_GPIO_INTR_ST : RO; bitpos: [20]; default: 0;
 *  need_des
 */
#define LPINTR_LP_GPIO_INTR_ST    (BIT(20))
#define LPINTR_LP_GPIO_INTR_ST_M  (LPINTR_LP_GPIO_INTR_ST_V << LPINTR_LP_GPIO_INTR_ST_S)
#define LPINTR_LP_GPIO_INTR_ST_V  0x00000001U
#define LPINTR_LP_GPIO_INTR_ST_S  20
/** LPINTR_LP_ADC_INTR_ST : RO; bitpos: [21]; default: 0;
 *  need_des
 */
#define LPINTR_LP_ADC_INTR_ST    (BIT(21))
#define LPINTR_LP_ADC_INTR_ST_M  (LPINTR_LP_ADC_INTR_ST_V << LPINTR_LP_ADC_INTR_ST_S)
#define LPINTR_LP_ADC_INTR_ST_V  0x00000001U
#define LPINTR_LP_ADC_INTR_ST_S  21
/** LPINTR_ANAPERI_INTR_ST : RO; bitpos: [22]; default: 0;
 *  need_des
 */
#define LPINTR_ANAPERI_INTR_ST    (BIT(22))
#define LPINTR_ANAPERI_INTR_ST_M  (LPINTR_ANAPERI_INTR_ST_V << LPINTR_ANAPERI_INTR_ST_S)
#define LPINTR_ANAPERI_INTR_ST_V  0x00000001U
#define LPINTR_ANAPERI_INTR_ST_S  22
/** LPINTR_PMU_REG_1_INTR_ST : RO; bitpos: [23]; default: 0;
 *  need_des
 */
#define LPINTR_PMU_REG_1_INTR_ST    (BIT(23))
#define LPINTR_PMU_REG_1_INTR_ST_M  (LPINTR_PMU_REG_1_INTR_ST_V << LPINTR_PMU_REG_1_INTR_ST_S)
#define LPINTR_PMU_REG_1_INTR_ST_V  0x00000001U
#define LPINTR_PMU_REG_1_INTR_ST_S  23
/** LPINTR_PMU_REG_0_INTR_ST : RO; bitpos: [24]; default: 0;
 *  need_des
 */
#define LPINTR_PMU_REG_0_INTR_ST    (BIT(24))
#define LPINTR_PMU_REG_0_INTR_ST_M  (LPINTR_PMU_REG_0_INTR_ST_V << LPINTR_PMU_REG_0_INTR_ST_S)
#define LPINTR_PMU_REG_0_INTR_ST_V  0x00000001U
#define LPINTR_PMU_REG_0_INTR_ST_S  24
/** LPINTR_MB_LP_INTR_ST : RO; bitpos: [25]; default: 0;
 *  need_des
 */
#define LPINTR_MB_LP_INTR_ST    (BIT(25))
#define LPINTR_MB_LP_INTR_ST_M  (LPINTR_MB_LP_INTR_ST_V << LPINTR_MB_LP_INTR_ST_S)
#define LPINTR_MB_LP_INTR_ST_V  0x00000001U
#define LPINTR_MB_LP_INTR_ST_S  25
/** LPINTR_MB_HP_INTR_ST : RO; bitpos: [26]; default: 0;
 *  need_des
 */
#define LPINTR_MB_HP_INTR_ST    (BIT(26))
#define LPINTR_MB_HP_INTR_ST_M  (LPINTR_MB_HP_INTR_ST_V << LPINTR_MB_HP_INTR_ST_S)
#define LPINTR_MB_HP_INTR_ST_V  0x00000001U
#define LPINTR_MB_HP_INTR_ST_S  26
/** LPINTR_LP_TIMER_REG_1_INTR_ST : RO; bitpos: [27]; default: 0;
 *  need_des
 */
#define LPINTR_LP_TIMER_REG_1_INTR_ST    (BIT(27))
#define LPINTR_LP_TIMER_REG_1_INTR_ST_M  (LPINTR_LP_TIMER_REG_1_INTR_ST_V << LPINTR_LP_TIMER_REG_1_INTR_ST_S)
#define LPINTR_LP_TIMER_REG_1_INTR_ST_V  0x00000001U
#define LPINTR_LP_TIMER_REG_1_INTR_ST_S  27
/** LPINTR_LP_TIMER_REG_0_INTR_ST : RO; bitpos: [28]; default: 0;
 *  need_des
 */
#define LPINTR_LP_TIMER_REG_0_INTR_ST    (BIT(28))
#define LPINTR_LP_TIMER_REG_0_INTR_ST_M  (LPINTR_LP_TIMER_REG_0_INTR_ST_V << LPINTR_LP_TIMER_REG_0_INTR_ST_S)
#define LPINTR_LP_TIMER_REG_0_INTR_ST_V  0x00000001U
#define LPINTR_LP_TIMER_REG_0_INTR_ST_S  28
/** LPINTR_LP_WDT_INTR_ST : RO; bitpos: [29]; default: 0;
 *  need_des
 */
#define LPINTR_LP_WDT_INTR_ST    (BIT(29))
#define LPINTR_LP_WDT_INTR_ST_M  (LPINTR_LP_WDT_INTR_ST_V << LPINTR_LP_WDT_INTR_ST_S)
#define LPINTR_LP_WDT_INTR_ST_V  0x00000001U
#define LPINTR_LP_WDT_INTR_ST_S  29
/** LPINTR_LP_RTC_INTR_ST : RO; bitpos: [30]; default: 0;
 *  need_des
 */
#define LPINTR_LP_RTC_INTR_ST    (BIT(30))
#define LPINTR_LP_RTC_INTR_ST_M  (LPINTR_LP_RTC_INTR_ST_V << LPINTR_LP_RTC_INTR_ST_S)
#define LPINTR_LP_RTC_INTR_ST_V  0x00000001U
#define LPINTR_LP_RTC_INTR_ST_S  30
/** LPINTR_HP_INTR_ST : RO; bitpos: [31]; default: 0;
 *  need_des
 */
#define LPINTR_HP_INTR_ST    (BIT(31))
#define LPINTR_HP_INTR_ST_M  (LPINTR_HP_INTR_ST_V << LPINTR_HP_INTR_ST_S)
#define LPINTR_HP_INTR_ST_V  0x00000001U
#define LPINTR_HP_INTR_ST_S  31

/** LPINTR_DATE_REG register
 *  need_des
 */
#define LPINTR_DATE_REG (DR_REG_LPINTR_BASE + 0x3fc)
/** LPINTR_CLK_EN : R/W; bitpos: [31]; default: 0;
 *  need_des
 */
#define LPINTR_CLK_EN    (BIT(31))
#define LPINTR_CLK_EN_M  (LPINTR_CLK_EN_V << LPINTR_CLK_EN_S)
#define LPINTR_CLK_EN_V  0x00000001U
#define LPINTR_CLK_EN_S  31

#ifdef __cplusplus
}
#endif
