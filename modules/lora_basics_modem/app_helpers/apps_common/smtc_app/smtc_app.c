/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <smtc_app.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

#include <smtc_modem_api.h>
#include <smtc_modem_api_str.h>

#include <smtc_modem_hal_init.h>

LOG_MODULE_REGISTER(smtc_app, CONFIG_LORA_BASICS_MODEM_LOG_LEVEL);

/* Offset in second between GPS EPOCH and UNIX EPOCH time */
#define OFFSET_BETWEEN_GPS_EPOCH_AND_UNIX_EPOCH 315964800

/* Number of leap seconds as of September 15th 2021 */
#define OFFSET_LEAP_SECONDS 18

static void prv_event_process(void);
static struct smtc_app_event_callbacks *prv_callbacks;
static struct smtc_app_env_callbacks *prv_env_callbacks;
static struct smtc_app_lorawan_cfg *prv_cfg;

/* Callbacks for HAL implementation */
static struct smtc_modem_hal_cb prv_hal_cb;

static k_tid_t prv_sleeping_thread_id;

/* macro to ease repeated error checking in apps_modem_common_init */
#define SMTC_ERR_CHECK(func_name, rc)                                                              \
	do {                                                                                       \
		if (rc != SMTC_MODEM_RC_OK) {                                                      \
			LOG_ERR("%s, err: %s (%d)", func_name, smtc_modem_return_code_to_str(rc),  \
				rc);                                                               \
			return rc;                                                                 \
		}                                                                                  \
	} while (0);

/**
 * @brief Convert gps time to unix epoch time
 *
 * @param[in] gps_time_s GPS time to convert. In seconds.
 * @return uint32_t The same time in unix epoch format, in seconds.
 */
static uint32_t prv_convert_gps_to_utc_time(uint32_t gps_time_s)
{
	return gps_time_s + OFFSET_BETWEEN_GPS_EPOCH_AND_UNIX_EPOCH - OFFSET_LEAP_SECONDS;
}

/**
 * @brief Callback for modem hal
 */
static int prv_get_battery_level_cb(uint32_t *value)
{
	if (!prv_env_callbacks || !prv_env_callbacks->get_battery_level) {
		return -1;
	}

	return prv_env_callbacks->get_battery_level(value);
}

/**
 * @brief Callback for modem hal
 */
static int prv_get_temperature_cb(int32_t *value)
{
	if (!prv_env_callbacks || !prv_env_callbacks->get_temperature) {
		return -1;
	}

	return prv_env_callbacks->get_temperature(value);
}

void smtc_app_run_now(void)
{
	smtc_modem_hal_wake_up();
	// if(prv_sleeping_thread_id != NULL) {
	// 	k_wakeup(prv_sleeping_thread_id);
	// }
}

/**
 * @brief Callback for modem hal
 */
static int prv_get_voltage_cb(uint32_t *value)
{
	if (!prv_env_callbacks || !prv_env_callbacks->get_voltage_level) {
		return -1;
	}

	return prv_env_callbacks->get_voltage_level(value);
}

void smtc_app_init(const struct device *lora_radio, struct smtc_app_event_callbacks *callbacks,
		   struct smtc_app_env_callbacks *env_callbacks)
{
	__ASSERT(lora_radio, "radio must be provided");
	__ASSERT(callbacks, "callbacks must be provided");
	/* env_callbacks can be NULL */
#ifdef CONFIG_LORA_BASICS_MODEM_USER_STORAGE_IMPL
	__ASSERT(env_callbacks->context_store, "context_store must be provided");
	__ASSERT(env_callbacks->context_restore, "context_restore must be provided");

#endif
	prv_callbacks = callbacks;
	prv_env_callbacks = env_callbacks;

	/* Create callback structure for HAL impl */
	prv_hal_cb = (struct smtc_modem_hal_cb){
		.get_battery_level = prv_get_battery_level_cb,
		.get_temperature = prv_get_temperature_cb,
		.get_voltage = prv_get_voltage_cb,

#ifdef CONFIG_LORA_BASICS_MODEM_USER_STORAGE_IMPL
		.context_store = env_callbacks->context_store,
		.context_restore = env_callbacks->context_restore,
#endif
	};

	smtc_modem_hal_init(lora_radio);
	smtc_modem_hal_register_callbacks(&prv_hal_cb);

	smtc_modem_set_radio_context(lora_radio);
	smtc_modem_init(&prv_event_process);
}

smtc_modem_return_code_t smtc_app_configure_lorawan_params(uint8_t stack_id,
							   struct smtc_app_lorawan_cfg *cfg)
{
	prv_cfg = cfg;
	smtc_modem_return_code_t rc = SMTC_MODEM_RC_OK;

	if (cfg->use_chip_eui_as_dev_eui) {
		rc = smtc_modem_get_chip_eui(stack_id, cfg->dev_eui);
		SMTC_ERR_CHECK("smtc_modem_get_chip_eui", rc);
	}

	rc = smtc_modem_set_deveui(stack_id, cfg->dev_eui);
	SMTC_ERR_CHECK("smtc_modem_set_deveui", rc);

	rc = smtc_modem_set_joineui(stack_id, cfg->join_eui);
	SMTC_ERR_CHECK("smtc_modem_set_joineui", rc);

	// rc = smtc_modem_set_appkey(stack_id, cfg->app_key);
	// SMTC_ERR_CHECK("smtc_modem_set_appkey", rc);

	rc = smtc_modem_set_nwkkey(stack_id, cfg->app_key);
	SMTC_ERR_CHECK("smtc_modem_set_nwkkey", rc);

	rc = smtc_modem_set_region(stack_id, cfg->region);
	SMTC_ERR_CHECK("smtc_modem_set_region", rc);

	/* Print what was set */
	LOG_INF("Configured LoRaWAN parameters:");
	LOG_HEXDUMP_INF(cfg->dev_eui, 8, "DevEui: ");
	LOG_HEXDUMP_INF(cfg->join_eui, 8, "JoinEui: ");
	LOG_HEXDUMP_INF(cfg->app_key, 16, "AppKey: ");
	LOG_INF("Region: %s (%d)", smtc_modem_region_to_str(cfg->region), cfg->region);

	return SMTC_MODEM_RC_OK;
}

smtc_modem_return_code_t smtc_app_on_join(uint8_t stack_id, struct smtc_app_lorawan_cfg *cfg)
{
	smtc_modem_return_code_t rc = SMTC_MODEM_RC_OK;

	rc = smtc_modem_set_class(stack_id, cfg->class);
	SMTC_ERR_CHECK("smtc_modem_set_class", rc);

	LOG_INF("Class: %s (%d)", smtc_modem_class_to_str(cfg->class), cfg->class);

	return SMTC_MODEM_RC_OK;
}

void smtc_app_run_engine(void)
{
	/* Execute modem runtime, this function must be called again as soon as possible */
	uint32_t sleep_time_ms = smtc_modem_run_engine();
	// uint32_t sleep_time_ms = 3000;

	LOG_INF("Sleeping for %d ms", sleep_time_ms);

	prv_sleeping_thread_id  = k_current_get();



	smtc_modem_hal_interruptible_msleep(K_MSEC(sleep_time_ms));
	// k_sleep(K_MSEC(sleep_time_ms));
}

void smtc_app_display_versions(void)
{
	smtc_modem_return_code_t rc = SMTC_MODEM_RC_OK;
	smtc_modem_version_t firmware_version;

	rc = smtc_modem_get_modem_version(&firmware_version);
	if (rc == SMTC_MODEM_RC_OK) {
		LOG_INF("LoRa Basics Modem version: %d.%d.%d", firmware_version.major,
			firmware_version.minor, firmware_version.patch);
	}
}

smtc_modem_return_code_t smtc_app_get_gps_time(uint8_t stack_id, uint32_t *gps_time)
{
	uint32_t gps_fractional_s = 0;
	return smtc_modem_get_lorawan_mac_time(stack_id, gps_time, &gps_fractional_s);
}

smtc_modem_return_code_t smtc_app_get_utc_time(uint8_t stack_id, uint32_t *utc_time)
{
	uint32_t gps_time_s;
	smtc_modem_return_code_t ret = smtc_app_get_gps_time(stack_id, &gps_time_s);
	if (ret != SMTC_MODEM_RC_OK) {
		return ret;
	}

	*utc_time = prv_convert_gps_to_utc_time(gps_time_s);
	return SMTC_MODEM_RC_OK;
}

/* PRIVATE EVENT PROCESSOR - this calls registered callbacks from app layer */

static void prv_event_process(void)
{
	smtc_modem_event_t current_event;
	smtc_modem_return_code_t return_code = SMTC_MODEM_RC_OK;
	uint8_t event_pending_count;

	do {
		/* Read modem event */
		return_code = smtc_modem_get_event(&current_event, &event_pending_count);

		if (return_code != SMTC_MODEM_RC_OK) {
			LOG_ERR("smtc_modem_get_event, err: %d", return_code);
			return;
		}
		if (prv_callbacks == NULL) {
			LOG_DBG("prv_callbacks is NULL, can not call callback functions");
			continue;
		}

		/* Handle event by calling external callback */
		switch (current_event.event_type) {
		case SMTC_MODEM_EVENT_RESET:
			LOG_DBG("RESET EVENT");
			LOG_DBG("Reset count: %u", current_event.event_data.reset.count);
			if (prv_callbacks->reset != NULL) {
				prv_callbacks->reset(current_event.event_data.reset.count);
			}
			break;
		case SMTC_MODEM_EVENT_ALARM:
			LOG_DBG("ALARM EVENT");
			if (prv_callbacks->alarm != NULL) {
				prv_callbacks->alarm();
			}
			break;
		case SMTC_MODEM_EVENT_JOINED:
			LOG_DBG("JOINED EVENT");
			if (prv_callbacks->joined != NULL) {
				prv_callbacks->joined();
			}
			break;
		case SMTC_MODEM_EVENT_TXDONE:
			LOG_DBG("TX DONE EVENT");
			LOG_DBG("TX DONE status: %d", current_event.event_data.txdone.status);
			if (prv_callbacks->tx_done != NULL) {
				prv_callbacks->tx_done(current_event.event_data.txdone.status);
			}
			break;
		case SMTC_MODEM_EVENT_DOWNDATA:
			LOG_DBG("DOWNLINK EVENT");
			if (prv_callbacks->down_data != NULL) {
				prv_callbacks->down_data();
			}
			break;
		case SMTC_MODEM_EVENT_JOINFAIL:
			LOG_DBG("JOIN FAILED EVENT");
			if (prv_callbacks->join_fail != NULL) {
				prv_callbacks->join_fail();
			}
			break;
		case SMTC_MODEM_EVENT_ALCSYNC_TIME:
			LOG_DBG("ALC SYNC TIME EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_LINK_CHECK:
			LOG_DBG("LINK CHECK EVENT");
			LOG_DBG("Link status: %s (%d)",
				smtc_modem_event_mac_request_status_to_str(
					current_event.event_data.link_check.status),
				current_event.event_data.link_check.status);
			if (prv_callbacks->link_check != NULL) {
				prv_callbacks->link_check(
					current_event.event_data.link_check.status);
			}
			break;
		case SMTC_MODEM_EVENT_CLASS_B_PING_SLOT_INFO:
			LOG_DBG("CLASS B PING SLOT EVENT");
			LOG_DBG("Class B ping slot status: %s (%d)",
				smtc_modem_event_mac_request_status_to_str(
					current_event.event_data.class_b_ping_slot_info.status),
				current_event.event_data.class_b_ping_slot_info.status);
			if (prv_callbacks->class_b_ping_slot_info != NULL) {
				prv_callbacks->class_b_ping_slot_info(
					current_event.event_data.class_b_ping_slot_info.status);
			}
			break;
		case SMTC_MODEM_EVENT_CLASS_B_STATUS:
			LOG_DBG("CLASS B STATUS EVENT");
			LOG_DBG("Class B status: %s (%d)",
				smtc_modem_event_class_b_status_to_str(
					current_event.event_data.class_b_status.status),
				current_event.event_data.class_b_status.status);
			if (prv_callbacks->class_b_status != NULL) {
				prv_callbacks->class_b_status(
					current_event.event_data.class_b_status.status);
			}
			break;
		case SMTC_MODEM_EVENT_LORAWAN_MAC_TIME:
			LOG_DBG("LORAWAN MAC TIME EVENT");
			LOG_DBG("Time status: %s (%d)",
				smtc_modem_event_mac_request_status_to_str(
					current_event.event_data.lorawan_mac_time.status),
				current_event.event_data.lorawan_mac_time.status);
			if (prv_callbacks->mac_time != NULL) {
				prv_callbacks->mac_time(
					current_event.event_data.lorawan_mac_time.status);
			}
			break;
		case SMTC_MODEM_EVENT_LORAWAN_FUOTA_DONE:
			LOG_DBG("LORAWAN FUOTA DONE EVENT");
			if (prv_callbacks->fouta_done != NULL) {
				prv_callbacks->fouta_done();
			}
			break;
		case SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_C:
			LOG_DBG("LORAWAN NO_MORE_MULTICAST_SESSION_CLASS_C EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_B:
			LOG_DBG("LORAWAN NO_MORE_MULTICAST_SESSION_CLASS_B EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_C:
			LOG_DBG("LORAWAN NEW_MULTICAST_SESSION_CLASS_C EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_B:
			LOG_DBG("LORAWAN NEW_MULTICAST_SESSION_CLASS_B EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_FIRMWARE_MANAGEMENT:
			LOG_DBG("LORAWAN FIRMWARE_MANAGEMENT EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_STREAM_DONE:
			LOG_DBG("LORAWAN STREAM_DONE EVENT");
			if (prv_callbacks->stream_done != NULL) {
				prv_callbacks->stream_done();
			}
			break;
		case SMTC_MODEM_EVENT_UPLOAD_DONE:
			LOG_DBG("LORAWAN UPLOAD_DONE EVENT");
			LOG_DBG("Upload status: %s (%d)",
				smtc_modem_event_uploaddone_status_to_str(
					current_event.event_data.uploaddone.status),
				current_event.event_data.uploaddone.status);
			if (prv_callbacks->upload_done != NULL) {
				prv_callbacks->upload_done(
					current_event.event_data.uploaddone.status);
			}
			break;
		case SMTC_MODEM_EVENT_DM_SET_CONF:
			LOG_DBG("LORAWAN DM_SET_CONF EVENT");
			LOG_DBG("Opcode: %s (%d)",
				smtc_modem_event_setconf_opcode_to_str(
					current_event.event_data.setconf.opcode),
				current_event.event_data.setconf.opcode);
			if (prv_callbacks->dm_set_conf != NULL) {
				prv_callbacks->dm_set_conf(current_event.event_data.setconf.opcode);
			}
			break;
		case SMTC_MODEM_EVENT_MUTE:
			LOG_DBG("MUTE EVENT");
			LOG_DBG("Mute: %s (%d)",
				smtc_modem_event_mute_status_to_str(
					current_event.event_data.mute.status),
				current_event.event_data.mute.status);
			if (prv_callbacks->mute != NULL) {
				prv_callbacks->mute(current_event.event_data.mute.status);
			}
			break;
		case SMTC_MODEM_EVENT_GNSS_SCAN_DONE:
			LOG_DBG("LORAWAN GNSS_SCAN_DONE EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_GNSS_TERMINATED:
			LOG_DBG("LORAWAN GNSS_TERMINATED EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_GNSS_ALMANAC_DEMOD_UPDATE:
			LOG_DBG("LORAWAN ALMANAC_DEMOD_UPDATE EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_WIFI_SCAN_DONE:
			LOG_DBG("LORAWAN WIFI_SCAN_DONE EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_WIFI_TERMINATED:
			LOG_DBG("LORAWAN WIFI_TERMINATED EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_RELAY_TX_DYNAMIC:
			LOG_DBG("LORAWAN TX_DYNAMIC EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_RELAY_TX_MODE:
			LOG_DBG("LORAWAN RELAY_TX_MODE EVENT");
			/* TODO: */
			break;
		case SMTC_MODEM_EVENT_RELAY_TX_SYNC:
			LOG_DBG("LORAWAN RELAY_TX_SYNC EVENT");
			/* TODO: */
			break;
		default:
			LOG_WRN("UNKNOWN EVENT: %d", current_event.event_type);
			break;
		}
	} while ((return_code == SMTC_MODEM_RC_OK) && (event_pending_count > 0));
}
