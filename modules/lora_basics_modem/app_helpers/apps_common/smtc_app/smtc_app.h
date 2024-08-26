/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SMTC_APP_H
#define SMTC_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr/device.h>

#include <smtc_modem_api.h>
#include <smtc_modem_utilities.h>

/**
 * @brief Configuration structure for initializing common LoRaWAN parameters
 */
struct smtc_app_lorawan_cfg {
	/* If true, lr11xx chip eui will be used as dev_eui, and bellow dev_eui value will be
	 * ignored. */
	bool use_chip_eui_as_dev_eui;

	/* DevEUI to use (if use_chip_eui_as_dev_eui is set to false) */
	uint8_t dev_eui[8];

	/* JoinEUI to use */
	uint8_t join_eui[8];

	/* AppKey/NwKey to use */
	uint8_t app_key[16];

	/* LoRaWAN class to use */
	smtc_modem_class_t class;

	/* Regional parameters to use */
	smtc_modem_region_t region;
};

/**
 * @brief Lora Basics Modem callbacks
 */
struct smtc_app_event_callbacks {
	/**
	 * @brief Modem reset
	 *
	 * @param [in] reset_count The number of resets (persistently stored)
	 */
	void (*reset)(uint16_t reset_count);

	/**
	 * @brief Alarm timer expired
	 */
	void (*alarm)(void);

	/**
	 * @brief Attempt to join network succeeded
	 */
	void (*joined)(void);

	/**
	 * @brief Attempt to join network failed
	 */
	void (*join_fail)(void);

	/**
	 * @brief Tx done
	 *
	 * @param [in] status Status of the transmission
	 */
	void (*tx_done)(smtc_modem_event_txdone_status_t status);

	/**
	 * @brief Downlink data received
	 *
	 * Call smtc_modem_get_downlink_data to get the data
	 */
	void (*down_data)(void);

	/**
	 * @brief ALC Sync time was updated
	 *
	 * TODO: figure out what this means and how to get the new time.
	 */
	void (*alcsync_update)(void);

	/**
	 * @brief Link Check result (result of link check)
	 *
	 * If successful, call smtc_modem_get_lorawan_link_check_data for link check details.
	 *
	 * @param [in] status Result status.
	 */
	void (*link_check)(smtc_modem_event_mac_request_status_t status);

	/**
	 * @brief Class B ping slot info
	 *
	 * TODO: Is there any fuinction to call to get more info about this?
	 *
	 * @param [in] status Result status.
	 */
	void (*class_b_ping_slot_info)(smtc_modem_event_mac_request_status_t status);

	/**
	 * @brief Class B status
	 *
	 * @param [in] status Class B status.
	 */
	void (*class_b_status)(smtc_modem_event_class_b_status_t status);

	/**
	 * @brief MAC time request done
	 *
	 * If successful, call smtc_modem_get_lorawan_mac_time to get the time.
	 *
	 * @param [in] status Status of the request.
	 */
	void (*mac_time)(smtc_modem_event_mac_request_status_t status);

	/**
	 * @brief End of FUOTA session
	 */
	void (*fouta_done)(void);

	/* TODO: Class B and C event callbacks */
	/* TODO: FMP (Firmware management) event callback */

	/**
	 * @brief Data stream fragments sent
	 *
	 * All data in the stream has been sent.
	 */
	void (*stream_done)(void);

	/**
	 * @brief File upload completed
	 *
	 * @param [in] status The upload status
	 */
	void (*upload_done)(smtc_modem_event_uploaddone_status_t status);

	/**
	 * @brief Configuration changed by device management
	 *
	 * For example. If opcode == SMTC_MODEM_EVENT_SETCONF_REGION_UPDATED,
	 * use smtc_modem_get_region to get the new region.
	 *
	 * @param [in] opcode What was updated by DM.
	 */
	void (*dm_set_conf)(smtc_modem_event_setconf_opcode_t opcode);

	/**
	 * @brief Mute callback
	 *
	 * @param [in] status \see smtc_modem_event_mute_status_t
	 */
	void (*mute)(smtc_modem_event_mute_status_t status);

	/* TODO: GNSS event callbacks */
	/* TODO: WiFi event callbacks */
	/* TODO: Relay TX event callbacks */
};

/**
 * @brief Function callbacks for providing environmental sensor values.
 *
 * These callbacks are used by the device management (DM) subsystem of the lora basics modem stack.
 * They will be called from the modem stack whenever a new DM info message is being prepared, but
 * only if that DM info field is configured to be sent.
 *
 * if the app does not provide the callbacks, a default (minimum) will be sent by the DM subsystem.
 *
 * If CONFIG_LORA_BASICS_MODEM_USER_STORAGE_IMPL=y, two additional callbacks MUST be implemented.
 */
struct smtc_app_env_callbacks {
	/**
	 * @brief Get battery level callback.
	 *
	 * @param [out] battery_level The battery level in permilles (‰) (where 1000‰ means full
	 * battery). The application should set this to the most recent battery level it has
	 * available.
	 *
	 * @return int 0 if the battery level was set, or a negative error code if no valid battery
	 * level is available.
	 */
	int (*get_battery_level)(uint32_t *battery_level);

	/**
	 * @brief Get temperature callback.
	 *
	 * @param [out] temperature The temperature (in deg C). The application should set this to
	 * the most recent temperature value it has available.
	 *
	 * @return int 0 if the temperature was set, or a negative error code if no valid
	 * temperature is available.
	 */
	int (*get_temperature)(int32_t *temperature);

	/**
	 * @brief Get voltage level callback.
	 *
	 * @param [out] voltage_level The voltage level (in mV). The application should set this to
	 * the most recent voltage level it has available.
	 *
	 * @return int 0 if the voltage level was set, or a negative error code if no valid voltage
	 * level is available.
	 */
	int (*get_voltage_level)(uint32_t *voltage_level);

#ifdef CONFIG_LORA_BASICS_MODEM_USER_STORAGE_IMPL

	/* TODO: Since the expectations of smtc_hal.h regarding the storage and retrieval of
	 * contexts has changed signicicantly with the introduction of the offset parameter and the
	 * FUOTA and "store and forward" features, we need to re-evaluate the whole persistent
	 * storage situation. See notes.md */

	/**
	 * @brief Persistently store context from the lora basics modem
	 *
	 * The application should use some persistent storage to store the context.
	 *
	 * The data behind the context should be updated based on the offset and size.
	 *
	 * @param[in] ctx_id The ID of the context to store. Each ID must be stored separately.
	 * @param[in] offset The offset in the buffer to use.
	 * @param[in] buffer The buffer to store.
	 * @param[in] size The size of the buffer to store, in bytes.
	 */
	void (*context_store)(const uint8_t ctx_id, uint32_t offset, const uint8_t *buffer,
			      const uint32_t size);

	/**
	 * @brief Restore context to the lora basics modem
	 *
	 * The application should load the context from the persistent storage used in
	 * context_store.
	 *
	 * Data should be provided based on the offset and size.
	 *
	 * @param[in] ctx_id The ID of the context to restore.
	 * @param[in] offset The offset in the buffer to use.
	 * @param[in] buffer The buffer to read into.
	 * @param[in] size The size of the buffer, in bytes.
	 */
	void (*context_restore)(const uint8_t ctx_id, uint32_t offset, uint8_t *buffer,
				const uint32_t size);

#endif /* CONFIG_LORA_BASICS_MODEM_USER_STORAGE_IMPL */
};

/**
 * @brief Initialize modem with the provided radio and callbacks
 *
 * Internally, this registers a private "raw" event handler to the modem stack.
 * Within the handler, callbacks provided in @p callback are called when corresponding events are
 * generated by the modem stack.
 *
 * @param[in] radio The LoRa radio device to use.
 * @param[in] callback Desired callbacks. All callbacks that are not required by the application can
 * be set to NULL.
 * @param[in] env_callbacks Desired environment callbacks. Can be NULL. All callbacks that are not
 * required by the application can be set to NULL.
 */
void smtc_app_init(const struct device *lora_radio, struct smtc_app_event_callbacks *callbacks,
		   struct smtc_app_env_callbacks *env_callbacks);

/**
 * @brief Configure common LoRaWAN parameters
 *
 * Sets LoRaWAN parameters in the modem.
 * If cfg->use_chip_eui_as_dev_eui is true, this function will save the chip eui into cfg->dev_eui,
 * so the cfg struct must not be const.
 *
 * @param[in] stack_id The stack ID to configure.
 * @param[in] cfg The configuration to apply. The config struct must live for as long as the modem
 * engine is in use.
 *
 * @return SMTC_MODEM_RC_OK if successful, or other error code if unsuccessful
 */
smtc_modem_return_code_t smtc_app_configure_lorawan_params(uint8_t stack_id,
							   struct smtc_app_lorawan_cfg *cfg);

/**
 * @brief When the device successfully joined a network, configure the devices class.
 *
 * DEV: Other on-join configuration can be handled here.
 *
 * @param[in] stack_id
 * @param[in] cfg
 * @return smtc_modem_return_code_t
 */
smtc_modem_return_code_t smtc_app_on_join(uint8_t stack_id, struct smtc_app_lorawan_cfg *cfg);

/**
 * @brief Display version information
 *
 * Displays LoRa Basics Modem, LoRaWAN and Regional parameters versions.
 * This is especially usefull to correctly setup a device server side.
 *
 */
void smtc_app_display_versions(void);

/**
 * @brief Get time in gps epoch
 *
 * @param[in] stack_id The stack ID to use.
 * @param[out] gps_time The current gps time (number of seconds since the GPS epoch)
 *
 * @return smtc_modem_return_code_t SMTC_MODEM_RC_OK if time was read successfully, or other error
 * code if unsuccessful
 */
smtc_modem_return_code_t smtc_app_get_gps_time(uint8_t stack_id, uint32_t *gps_time);

/**
 * @brief Get utc time
 *
 * @param[in] stack_id The stack ID to use.
 * @param[out] gps_time The current unix time (number of seconds since the unix epoch)
 *
 * @return SMTC_MODEM_RC_OK if time was read successfully, or other error
 * code if unsuccessful
 */
smtc_modem_return_code_t smtc_app_get_utc_time(uint8_t stack_id, uint32_t *utc_time);

/**
 * @brief Run the modem engine and sleep for returned duration.
 *
 */
void smtc_app_run_engine(void);

/**
 * @brief Interrupt sleep in smtc_app_run_engine to cause the engine to run immediately.
 *
 */
void smtc_app_run_now(void);

#ifdef __cplusplus
}
#endif

#endif // SMTC_APP_H
