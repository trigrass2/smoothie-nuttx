/****************************************************************************
 * configs/smoothie-v2minialpha/src/smoothie-v2minialpha.h
 *
 *   Copyright (C) 2016 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *           Alan Carvalho de Assis acassis@gmail.com [nuttx] <nuttx@yahoogroups.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#pragma once

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include "lpc43_pinconfig.h"
#include "lpc43_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 *  LED1   GPIO2[10]
 *  LED2   GPIO2[9]
 *  LED3   GPIO6[13]
 *  LED4   GPIO6[12]
 *
 ****************************************************************************/

/* Definitions to configure LED pins as GPIOs:
 *
 * - Floating
 * - Normal drive
 * - No buffering, glitch filtering, slew=slow
 */

#define PINCONFIG_LED1 PINCONF_GPIO2p10
#define PINCONFIG_LED2 PINCONF_GPIO2p9
#define GPIO_LED1      (GPIO_MODE_OUTPUT | GPIO_VALUE_ONE | GPIO_PORT2 | GPIO_PIN10)
#define GPIO_LED2      (GPIO_MODE_OUTPUT | GPIO_VALUE_ONE | GPIO_PORT2 | GPIO_PIN9)

/****************************************************************************
 *  Buttons GPIO
 *  ----------------------------
 *  gpio0[7]  - User Button USR1
 ****************************************************************************/

#define SMOOTHIE_BUT1 (GPIO_INT_EDGE_BOTH | GPIO_FLOAT | GPIO_PORT0 | GPIO_PIN7)

/****************************************************************************
 *  SD Card Detection
 *  ----------------------------
 *  gpio6[7]  - SD_CD pin
 ****************************************************************************/

#define GPIO_SD_CD (GPIO_MODE_PININTR | GPIO_INT_EDGE_BOTH | GPIO_PORT6 | GPIO_PIN7)

/* Used by High Priority Test */

// #define GPIO_TEST      (GPIO_MODE_OUTPUT | GPIO_VALUE_ONE | GPIO_PORT1 | GPIO_PIN10)

// #define PINCONFIG_TEST PINCONF_GPIO1p10

/* Button IRQ numbers */

#define SMOOTHIE_BUT1_IRQ  LPC43_IRQ_P0p23

/* SD_CD IRQ number */

#define GPIO_SD_CD_IRQ  LPC43M4_IRQ_PININT7 /* Pin 7 of Port 6 */

#define GPIO_SSP0_SCK  GPIO_SSP0_SCK_1
#define GPIO_SSP0_SSEL GPIO_SSP0_SSEL_1
#define GPIO_SSP0_MISO GPIO_SSP0_MISO_1
#define GPIO_SSP0_MOSI GPIO_SSP0_MOSI_1

/* We need to redefine USB_PWRD as GPIO to get USB Host working
 * Also remember to add 2 resistors of 15K to D+ and D- pins.
 */

#ifdef CONFIG_USBHOST
#  ifdef GPIO_USB_PWRD
#    undef  GPIO_USB_PWRD
#    define GPIO_USB_PWRD  (GPIO_INPUT | GPIO_PORT1 | GPIO_PIN22)
#  endif
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public data
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lpc43_sspdev_initialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the Lincoln 80 board.
 *
 ****************************************************************************/

void weak_function lpc43_sspdev_initialize(void);

/************************************************************************************
 * Name: lpc43xx_timerinitialize()
 *
 * Description:
 *   Perform architecture-specific initialization of the timer hardware.
 *
 ************************************************************************************/

#ifdef CONFIG_TIMER
int lpc43_timerinitialize(void);
#else
#  define lpc43_timerinitialize() (0)
#endif

/****************************************************************************
 * Name: lpc43_mmcsd_initialize
 *
 * Description:
 *   Perform architecture specific initialization
 *
 ****************************************************************************/

#ifdef CONFIG_LPC43_SDMMC
int lpc43_mmcsd_initialize(void);
#endif

#endif /* __ASSEMBLY__ */
