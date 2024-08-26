/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "main.h"
#include "smtc_modem_hal_init.h"
#include "smtc_modem_utilities.h"
#include <smtc_modem_api.h>

#include "cmd_parser.h"

/* lr11xx radio context and its use in the ralf layer */
static const struct device *transceiver = DEVICE_DT_GET(DT_ALIAS(lora_transceiver));

/* Callbacks for HAL implementation */
static struct smtc_modem_hal_cb prv_hal_cb;

/**
 * @brief Callback for modem hal
 */
static int prv_get_battery_level_cb(uint32_t *value)
{
	*value = 98;
	return 0;
}

/**
 * @brief Callback for modem hal
 */
static int prv_get_temperature_cb(int32_t *value)
{
	*value = 25;
	return 0;
}

/**
 * @brief Callback for modem hal
 */
static int prv_get_voltage_cb(uint32_t *value)
{
	*value = 3300;
	return 0;
}

#ifdef CONFIG_LORA_BASICS_MODEM_FUOTA
static int prv_get_hw_version_for_fuota(uint32_t *version)
{
	*version = 1;
	return 0;
}

static int prv_get_fw_version_for_fuota(uint32_t *version)
{
	*version = 1;
	return 0;
}

static int prv_get_fw_status_available_for_fuota(uint8_t *status)
{
	*status = 1;
	return 0;
}

static int prv_get_next_fw_version_for_fuota(uint32_t *version)
{
	*version = 1;
	return 0;
}

static int prv_get_fw_delete_status_for_fuota(uint32_t status)
{
	return 0;
}
#endif /* CONFIG_LORA_BASICS_MODEM_FUOTA */

int main(void)
{
	/* Create callback structure for HAL impl */
	prv_hal_cb = (struct smtc_modem_hal_cb){
		.get_battery_level = prv_get_battery_level_cb,
		.get_temperature = prv_get_temperature_cb,
		.get_voltage = prv_get_voltage_cb,

#ifdef CONFIG_LORA_BASICS_MODEM_FUOTA
		.get_hw_version_for_fuota = prv_get_hw_version_for_fuota,
		.get_fw_version_for_fuota = prv_get_fw_version_for_fuota,
		.get_fw_status_available_for_fuota = prv_get_fw_status_available_for_fuota,
		.get_next_fw_version_for_fuota = prv_get_next_fw_version_for_fuota,
		.get_fw_delete_status_for_fuota = prv_get_fw_delete_status_for_fuota,
#endif /* CONFIG_LORA_BASICS_MODEM_FUOTA */
	};

	smtc_modem_set_radio_context(transceiver);
	smtc_modem_hal_init(transceiver);
	smtc_modem_hal_register_callbacks(&prv_hal_cb);

	cmd_parser_set_transceiver_context((void*)transceiver);

	main_hw_modem();
	return 0;
}
