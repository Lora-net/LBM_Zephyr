/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "modem_pinout.h"

static const struct gpio_dt_spec hw_modem_event_gpios =
	GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), hw_modem_event_gpios);
static const struct gpio_dt_spec hw_modem_busy_gpios =
	GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), hw_modem_busy_gpios);
static const struct gpio_dt_spec hw_modem_command_gpios =
	GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), hw_modem_command_gpios);
static const struct gpio_dt_spec hw_modem_led_scan_gpios =
	GPIO_DT_SPEC_GET(DT_PATH(zephyr_user), hw_modem_led_scan_gpios);

const struct gpio_dt_spec *modem_pinout_get_hw_modem_event_gpios(void)
{
	return &hw_modem_event_gpios;
}

const struct gpio_dt_spec *modem_pinout_get_hw_modem_busy_gpios(void)
{
	return &hw_modem_busy_gpios;
}

const struct gpio_dt_spec *modem_pinout_get_hw_modem_command_gpios(void)
{
	return &hw_modem_command_gpios;
}

const struct gpio_dt_spec *modem_pinout_get_hw_modem_led_scan_gpios(void)
{
	return &hw_modem_led_scan_gpios;
}
