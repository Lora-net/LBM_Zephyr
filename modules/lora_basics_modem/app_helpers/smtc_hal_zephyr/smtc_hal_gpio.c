/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "smtc_hal_gpio.h"

#include <stdbool.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(hal_gpio, 3);

#define PIN_COUNT 4
/* Storage for interrupt context pointers */
struct cb_data {
	hal_gpio_irq_t *irq;
	struct gpio_callback cb;
	const struct gpio_dt_spec *gpio;
	bool used;
};

static struct cb_data prv_cb_data[PIN_COUNT];

static bool prv_irq_enable = true;

static struct cb_data *prv_get_cb_data(const struct gpio_dt_spec *pin)
{
	/* Check if this pin has an associated callback */
	for (int i = 0; i < PIN_COUNT; i++) {
		if (prv_cb_data[i].gpio == pin) {
			return &prv_cb_data[i];
		}
	}

	/* If not, assign a free one */
	for (int i = 0; i < PIN_COUNT; i++) {
		if (!prv_cb_data[i].used) {
			prv_cb_data[i].gpio = pin;
			prv_cb_data[i].used = true;
			return &prv_cb_data[i];
		}
	}

	__ASSERT(false, "All callback slots are used!");
	return NULL;
}

/**
 * @brief Call the corresponding callback function for the given pin
 */
void prv_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	if (!prv_irq_enable) {
		return;
	}

	struct cb_data *data = CONTAINER_OF(cb, struct cb_data, cb);
	data->irq->callback(data->irq->context);
}

void hal_gpio_init_out(const struct gpio_dt_spec *pin, const uint32_t value)
{
	gpio_flags_t flag = value ? GPIO_OUTPUT_ACTIVE : GPIO_OUTPUT_INACTIVE;
	gpio_pin_configure_dt(pin, flag);
}

void hal_gpio_init_in(const struct gpio_dt_spec *pin, const hal_gpio_pull_mode_t pull_mode,
		      const hal_gpio_irq_mode_t irq_mode, hal_gpio_irq_t *irq)
{
	/* Init pin as input */
	gpio_flags_t flags = GPIO_INPUT;
	switch (pull_mode) {
	case BSP_GPIO_PULL_MODE_UP:
		flags |= GPIO_PULL_UP;
		break;
	case BSP_GPIO_PULL_MODE_DOWN:
		flags |= GPIO_PULL_DOWN;
		break;
	case BSP_GPIO_PULL_MODE_NONE:
		break;
	}

	gpio_pin_configure_dt(pin, flags);

	/* Init IRQ */

	gpio_flags_t irq_flags = GPIO_INT_ENABLE;
	switch (irq_mode) {
	case BSP_GPIO_IRQ_MODE_RISING:
		irq_flags |= GPIO_INT_EDGE_RISING;
		break;
	case BSP_GPIO_IRQ_MODE_FALLING:
		irq_flags |= GPIO_INT_EDGE_FALLING;
		break;
	case BSP_GPIO_IRQ_MODE_RISING_FALLING:
		irq_flags |= GPIO_INT_EDGE_BOTH;
		break;
	case BSP_GPIO_IRQ_MODE_OFF:
		irq_flags = GPIO_INT_DISABLE;
		break;
	}

	gpio_pin_interrupt_configure_dt(pin, irq_flags);

	/* Configure callback */
	struct cb_data *cb_data = prv_get_cb_data(pin);

	if (irq_mode == BSP_GPIO_IRQ_MODE_OFF) {
		gpio_remove_callback(pin->port, &cb_data->cb);
		return;
	}

	cb_data->irq = irq;
	gpio_init_callback(&cb_data->cb, prv_callback, BIT(pin->pin));
	gpio_add_callback(pin->port, &cb_data->cb);
}

void hal_gpio_set_value(const struct gpio_dt_spec *pin, const uint32_t value)
{
	gpio_pin_set_dt(pin, value);
}

uint32_t hal_gpio_get_value(const struct gpio_dt_spec *pin)
{
	return gpio_pin_get_dt(pin);
}

void hal_gpio_irq_enable_set(bool enable)
{
	prv_irq_enable = enable;
}
