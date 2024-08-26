/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "smtc_hal_uart.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(hal_uart, 3);

static const struct device *prv_uart_dev = DEVICE_DT_GET(DT_ALIAS(smtc_hal_uart));

static uint8_t *prv_buff;
static uint16_t prv_i;
static uint16_t prv_size;

/**
 * @brief Interrupt driven UART handler
 *
 * @param[in] dev UART device pointer
 * @param[in] user_data not used
 */
static void prv_uart_irq_rx_callback_handler(const struct device *dev, void *user_data)
{
	ARG_UNUSED(user_data);
	uint8_t c;

	if (!uart_irq_update(dev)) {
		return;
	}

	if (!uart_irq_rx_ready(dev)) {
		return;
	}

	int status = uart_err_check(dev);
	if (status > 0) {
		LOG_ERR("UART error detected: %d", status);
	}

	/* read until FIFO empty */
	while (uart_fifo_read(dev, &c, 1) == 1) {
		// __ASSERT(prv_i < prv_size, "Received more data than the buffer can hold!");
		prv_buff[prv_i++] = c;
	}
}

/**
 * @brief Configure UART in interrupt based mode
 *
 * Data must be received into the buffer provided
 *
 * @param[in] buff The buffer to store the received data in
 * @param[in] size The size of the buffer
 */
void hw_modem_uart_dma_start_rx(uint8_t *buff, uint16_t size)
{
	/* Remember where to store data into */
	int ret = 0;
	prv_i = 0;
	prv_buff = buff;
	prv_size = size;

	/* configure interrupt and callback to receive data */
	ret = uart_irq_callback_user_data_set(prv_uart_dev,
		prv_uart_irq_rx_callback_handler, NULL);
	// printk("uart_irq_callback_user_data_set returned %d\n", ret);
	uart_irq_rx_enable(prv_uart_dev);
	LOG_WRN("UART RX started");
}

/**
 * @brief Turn off the UART RX
 */
void hw_modem_uart_dma_stop_rx(void)
{
	uart_irq_rx_disable(prv_uart_dev);
	LOG_WRN("UART RX stopped");
}

/**
 * @brief Send data over UART, polling
 *
 * @param[in] buff The buffer to send
 * @param[in] len The length of the buffer
 */
void hw_modem_uart_tx(uint8_t *buff, uint8_t len)
{
	for (size_t i = 0; i < len; i++) {
		uart_poll_out(prv_uart_dev, buff[i]);
	}
}
