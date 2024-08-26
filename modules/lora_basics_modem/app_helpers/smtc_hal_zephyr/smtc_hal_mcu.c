/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "smtc_hal_mcu.h"

#include "smtc_hal_gpio.h"

#include <zephyr/kernel.h>

void hal_mcu_disable_irq(void)
{
	/* We cheat a bit and disable only the IRQs that are used by the modem HAL. In Zephyr, you
	 * don't really want to disable IRQs on the whole port */
	hal_gpio_irq_enable_set(false);

	/* If this function has to disable other IRQs that are used within the SMTC HAL and LR11XX
	 * driver HAL, then this has to be expanded... */
}

void hal_mcu_enable_irq(void)
{
	hal_gpio_irq_enable_set(true);
}

void hal_mcu_init(void)
{
	/* Nothing to do */
}

void hal_mcu_wait_us(const int32_t microseconds)
{
	k_busy_wait(microseconds);
}

void hal_mcu_set_sleep_for_ms(const int32_t milliseconds)
{
	k_sleep(K_MSEC(milliseconds));
}
