/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __MODEM_PIN_NAMES_H__
#define __MODEM_PIN_NAMES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <zephyr/drivers/gpio.h>

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/********************************************************************************/
/*                         Application     dependant                            */
/********************************************************************************/

const struct gpio_dt_spec *modem_pinout_get_hw_modem_event_gpios(void);
const struct gpio_dt_spec *modem_pinout_get_hw_modem_busy_gpios(void);
const struct gpio_dt_spec *modem_pinout_get_hw_modem_command_gpios(void);
const struct gpio_dt_spec *modem_pinout_get_hw_modem_led_scan_gpios(void);

#define HW_MODEM_EVENT_PIN   modem_pinout_get_hw_modem_event_gpios()
#define HW_MODEM_BUSY_PIN    modem_pinout_get_hw_modem_busy_gpios()
#define HW_MODEM_COMMAND_PIN modem_pinout_get_hw_modem_command_gpios()
#define SMTC_LED_SCAN	     modem_pinout_get_hw_modem_led_scan_gpios()

#define PIN_COUNT 4

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */
#ifdef __cplusplus
}
#endif

#endif //__MODEM_PIN_NAMES_H__
