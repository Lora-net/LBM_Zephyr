/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <smtc_hal_watchdog.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/watchdog.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(watchdog, 3);

#define TIMEOUT_MS (30 * 1000) /* 30s. Stm32 supports only up to 32'768 ms */

/* Watchdog device */
static const struct device *const prv_wdt_dev = DEVICE_DT_GET(DT_ALIAS(smtc_watchdog));

/* Assigned watchdog ID after initialization */
static int prv_wdt_channel_id;

void hal_watchdog_init(void)
{
	if (!device_is_ready(prv_wdt_dev)) {
		LOG_ERR("%s: device not ready", prv_wdt_dev->name);
		return;
	}

	struct wdt_timeout_cfg wdt_config = {
		/* Reset SoC when watchdog timer expires. */
		.flags = WDT_FLAG_RESET_SOC,

		/* Expire watchdog after max window */
		.window.min = 0,
		.window.max = TIMEOUT_MS,
	};

	prv_wdt_channel_id = wdt_install_timeout(prv_wdt_dev, &wdt_config);

	/* NOTE: This never fails */
	if (prv_wdt_channel_id < 0) {
		LOG_ERR("wdt_setup, err: %d", prv_wdt_channel_id);
		return;
	}
	int err = wdt_setup(prv_wdt_dev, WDT_OPT_PAUSE_HALTED_BY_DBG);
	if (err < 0) {
		LOG_ERR("wdt_setup, err: %d", err);
	}
}

void hal_watchdog_reload(void)
{
	wdt_feed(prv_wdt_dev, prv_wdt_channel_id);
}
