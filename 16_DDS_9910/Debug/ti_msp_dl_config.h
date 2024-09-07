/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMG6
#define PWM_0_INST_IRQHandler                                   TIMG6_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMG6_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                              4000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_2
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM15)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM15_PF_TIMG6_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (24999U)
/* Defines for TIMER_ADC */
#define TIMER_ADC_INST                                                   (TIMA0)
#define TIMER_ADC_INST_IRQHandler                               TIMA0_IRQHandler
#define TIMER_ADC_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define TIMER_ADC_INST_LOAD_VALUE                                          (31U)
#define TIMER_ADC_INST_PUB_0_CH                                              (1)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                        DL_GPIO_PIN_28
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM3)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                        DL_GPIO_PIN_31
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM6)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM6_PF_I2C0_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_16_MHZ_9600_BAUD                                       (104)
#define UART_0_FBRD_16_MHZ_9600_BAUD                                        (11)





/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC0
#define ADC12_0_INST_IRQHandler                                  ADC0_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC0_INT_IRQn)
#define ADC12_0_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define ADC12_0_INST_SUB_CH                                                  (1)
#define GPIO_ADC12_0_C0_PORT                                               GPIOA
#define GPIO_ADC12_0_C0_PIN                                       DL_GPIO_PIN_27



/* Defines for DMA_CH0 */
#define DMA_CH0_CHAN_ID                                                      (0)
#define ADC12_0_INST_DMA_TRIGGER                      (DMA_ADC0_EVT_GEN_BD_TRIG)



/* Defines for PIN_0: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_led_PIN_0_PORT                                              (GPIOA)
#define GPIO_led_PIN_0_PIN                                       (DL_GPIO_PIN_0)
#define GPIO_led_PIN_0_IOMUX                                      (IOMUX_PINCM1)
/* Defines for PIN_22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_led_PIN_22_PORT                                             (GPIOB)
#define GPIO_led_PIN_22_PIN                                     (DL_GPIO_PIN_22)
#define GPIO_led_PIN_22_IOMUX                                    (IOMUX_PINCM50)
/* Defines for PIN_18: GPIOA.18 with pinCMx 40 on package pin 11 */
#define GPIO_key_PIN_18_PORT                                             (GPIOA)
#define GPIO_key_PIN_18_PIN                                     (DL_GPIO_PIN_18)
#define GPIO_key_PIN_18_IOMUX                                    (IOMUX_PINCM40)
/* Defines for PIN_21: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_key_PIN_21_PORT                                             (GPIOB)
#define GPIO_key_PIN_21_PIN                                     (DL_GPIO_PIN_21)
#define GPIO_key_PIN_21_IOMUX                                    (IOMUX_PINCM49)
/* Defines for PIN_B12_MRT: GPIOB.12 with pinCMx 29 on package pin 64 */
#define GPIO_DDS_PIN_B12_MRT_PORT                                        (GPIOB)
#define GPIO_DDS_PIN_B12_MRT_PIN                                (DL_GPIO_PIN_12)
#define GPIO_DDS_PIN_B12_MRT_IOMUX                               (IOMUX_PINCM29)
/* Defines for PIN_B17_CSN: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GPIO_DDS_PIN_B17_CSN_PORT                                        (GPIOB)
#define GPIO_DDS_PIN_B17_CSN_PIN                                (DL_GPIO_PIN_17)
#define GPIO_DDS_PIN_B17_CSN_IOMUX                               (IOMUX_PINCM43)
/* Defines for PIN_B15_SCK: GPIOB.15 with pinCMx 32 on package pin 3 */
#define GPIO_DDS_PIN_B15_SCK_PORT                                        (GPIOB)
#define GPIO_DDS_PIN_B15_SCK_PIN                                (DL_GPIO_PIN_15)
#define GPIO_DDS_PIN_B15_SCK_IOMUX                               (IOMUX_PINCM32)
/* Defines for PIN_B6_SDI: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_DDS_PIN_B6_SDI_PORT                                         (GPIOB)
#define GPIO_DDS_PIN_B6_SDI_PIN                                  (DL_GPIO_PIN_6)
#define GPIO_DDS_PIN_B6_SDI_IOMUX                                (IOMUX_PINCM23)
/* Defines for PIN_B0_IUP: GPIOB.0 with pinCMx 12 on package pin 47 */
#define GPIO_DDS_PIN_B0_IUP_PORT                                         (GPIOB)
#define GPIO_DDS_PIN_B0_IUP_PIN                                  (DL_GPIO_PIN_0)
#define GPIO_DDS_PIN_B0_IUP_IOMUX                                (IOMUX_PINCM12)
/* Defines for PIN_B16_DRH: GPIOB.16 with pinCMx 33 on package pin 4 */
#define GPIO_DDS_PIN_B16_DRH_PORT                                        (GPIOB)
#define GPIO_DDS_PIN_B16_DRH_PIN                                (DL_GPIO_PIN_16)
#define GPIO_DDS_PIN_B16_DRH_IOMUX                               (IOMUX_PINCM33)
/* Defines for PIN_B4_DRC: GPIOB.4 with pinCMx 17 on package pin 52 */
#define GPIO_DDS_PIN_B4_DRC_PORT                                         (GPIOB)
#define GPIO_DDS_PIN_B4_DRC_PIN                                  (DL_GPIO_PIN_4)
#define GPIO_DDS_PIN_B4_DRC_IOMUX                                (IOMUX_PINCM17)
/* Defines for PIN_B1_OSK: GPIOB.1 with pinCMx 13 on package pin 48 */
#define GPIO_DDS_PIN_B1_OSK_PORT                                         (GPIOB)
#define GPIO_DDS_PIN_B1_OSK_PIN                                  (DL_GPIO_PIN_1)
#define GPIO_DDS_PIN_B1_OSK_IOMUX                                (IOMUX_PINCM13)
/* Defines for PIN_B20_PF0: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_DDS_PIN_B20_PF0_PORT                                        (GPIOB)
#define GPIO_DDS_PIN_B20_PF0_PIN                                (DL_GPIO_PIN_20)
#define GPIO_DDS_PIN_B20_PF0_IOMUX                               (IOMUX_PINCM48)
/* Defines for PIN_B13_PF1: GPIOB.13 with pinCMx 30 on package pin 1 */
#define GPIO_DDS_PIN_B13_PF1_PORT                                        (GPIOB)
#define GPIO_DDS_PIN_B13_PF1_PIN                                (DL_GPIO_PIN_13)
#define GPIO_DDS_PIN_B13_PF1_IOMUX                               (IOMUX_PINCM30)
/* Defines for PIN_A12_PF2: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_DDS_PIN_A12_PF2_PORT                                        (GPIOA)
#define GPIO_DDS_PIN_A12_PF2_PIN                                (DL_GPIO_PIN_12)
#define GPIO_DDS_PIN_A12_PF2_IOMUX                               (IOMUX_PINCM34)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSCTL_CLK_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_ADC_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_ADC12_0_init(void);
void SYSCFG_DL_DMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
