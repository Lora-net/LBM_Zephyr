/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "smtc_modem_api_str.h"

const char *smtc_modem_return_code_to_str(const smtc_modem_return_code_t value)
{
	switch (value) {
	case SMTC_MODEM_RC_OK:
		return "SMTC_MODEM_RC_OK";
	case SMTC_MODEM_RC_NOT_INIT:
		return "SMTC_MODEM_RC_NOT_INIT";
	case SMTC_MODEM_RC_INVALID:
		return "SMTC_MODEM_RC_INVALID";
	case SMTC_MODEM_RC_BUSY:
		return "SMTC_MODEM_RC_BUSY";
	case SMTC_MODEM_RC_FAIL:
		return "SMTC_MODEM_RC_FAIL";
	case SMTC_MODEM_RC_NO_TIME:
		return "SMTC_MODEM_RC_NO_TIME";
	case SMTC_MODEM_RC_INVALID_STACK_ID:
		return "SMTC_MODEM_RC_INVALID_STACK_ID";
	case SMTC_MODEM_RC_NO_EVENT:
		return "SMTC_MODEM_RC_NO_EVENT";
	}
	return "???";
}

const char *smtc_modem_region_to_str(const smtc_modem_region_t value)
{
	switch (value) {
	case SMTC_MODEM_REGION_EU_868:
		return "SMTC_MODEM_REGION_EU_868";
	case SMTC_MODEM_REGION_AS_923_GRP1:
		return "SMTC_MODEM_REGION_AS_923_GRP1";
	case SMTC_MODEM_REGION_US_915:
		return "SMTC_MODEM_REGION_US_915";
	case SMTC_MODEM_REGION_AU_915:
		return "SMTC_MODEM_REGION_AU_915";
	case SMTC_MODEM_REGION_CN_470:
		return "SMTC_MODEM_REGION_CN_470";
	case SMTC_MODEM_REGION_WW2G4:
		return "SMTC_MODEM_REGION_WW2G4";
	case SMTC_MODEM_REGION_AS_923_GRP2:
		return "SMTC_MODEM_REGION_AS_923_GRP2";
	case SMTC_MODEM_REGION_AS_923_GRP3:
		return "SMTC_MODEM_REGION_AS_923_GRP3";
	case SMTC_MODEM_REGION_IN_865:
		return "SMTC_MODEM_REGION_IN_865";
	case SMTC_MODEM_REGION_KR_920:
		return "SMTC_MODEM_REGION_KR_920";
	case SMTC_MODEM_REGION_RU_864:
		return "SMTC_MODEM_REGION_RU_864";
	case SMTC_MODEM_REGION_CN_470_RP_1_0:
		return "SMTC_MODEM_REGION_CN_470_RP_1_0";
	case SMTC_MODEM_REGION_AS_923_GRP4:
		return "SMTC_MODEM_REGION_AS_923_GRP4";
	}
	return "???";
}

const char *smtc_modem_adr_profile_to_str(const smtc_modem_adr_profile_t value)
{
	switch (value) {
	case SMTC_MODEM_ADR_PROFILE_NETWORK_CONTROLLED:
		return "SMTC_MODEM_ADR_PROFILE_NETWORK_CONTROLLED";
	case SMTC_MODEM_ADR_PROFILE_MOBILE_LONG_RANGE:
		return "SMTC_MODEM_ADR_PROFILE_MOBILE_LONG_RANGE";
	case SMTC_MODEM_ADR_PROFILE_MOBILE_LOW_POWER:
		return "SMTC_MODEM_ADR_PROFILE_MOBILE_LOW_POWER";
	case SMTC_MODEM_ADR_PROFILE_CUSTOM:
		return "SMTC_MODEM_ADR_PROFILE_CUSTOM";
	}
	return "???";
}

const char *smtc_modem_class_to_str(const smtc_modem_class_t value)
{
	switch (value) {
	case SMTC_MODEM_CLASS_A:
		return "SMTC_MODEM_CLASS_A";
	case SMTC_MODEM_CLASS_B:
		return "SMTC_MODEM_CLASS_B";
	case SMTC_MODEM_CLASS_C:
		return "SMTC_MODEM_CLASS_C";
	case SMTC_MODEM_CLASS_MAX:
		return "SMTC_MODEM_CLASS_MAX";
	}
	return "???";
}

const char *smtc_modem_mc_grp_id_to_str(const smtc_modem_mc_grp_id_t value)
{
	switch (value) {
	case SMTC_MODEM_MC_GRP_0:
		return "SMTC_MODEM_MC_GRP_0";
	case SMTC_MODEM_MC_GRP_1:
		return "SMTC_MODEM_MC_GRP_1";
	case SMTC_MODEM_MC_GRP_2:
		return "SMTC_MODEM_MC_GRP_2";
	case SMTC_MODEM_MC_GRP_3:
		return "SMTC_MODEM_MC_GRP_3";
	}
	return "???";
}

const char *smtc_modem_class_b_ping_slot_periodicity_to_str(
	const smtc_modem_class_b_ping_slot_periodicity_t value)
{
	switch (value) {
	case SMTC_MODEM_CLASS_B_PINGSLOT_1_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_1_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_2_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_2_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_4_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_4_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_8_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_8_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_16_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_16_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_32_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_32_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_64_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_64_S";
	case SMTC_MODEM_CLASS_B_PINGSLOT_128_S:
		return "SMTC_MODEM_CLASS_B_PINGSLOT_128_S";
	}
	return "???";
}

const char *
smtc_modem_lorawan_mac_request_mask_to_str(const smtc_modem_lorawan_mac_request_mask_t value)
{
	switch (value) {
	case SMTC_MODEM_LORAWAN_MAC_REQ_LINK_CHECK:
		return "SMTC_MODEM_LORAWAN_MAC_REQ_LINK_CHECK";
	case SMTC_MODEM_LORAWAN_MAC_REQ_DEVICE_TIME:
		return "SMTC_MODEM_LORAWAN_MAC_REQ_DEVICE_TIME";
	case SMTC_MODEM_LORAWAN_MAC_REQ_PING_SLOT_INFO:
		return "SMTC_MODEM_LORAWAN_MAC_REQ_PING_SLOT_INFO";
	}
	return "???";
}

const char *smtc_modem_dl_window_to_str(const smtc_modem_dl_window_t value)
{
	switch (value) {
	case SMTC_MODEM_DL_WINDOW_RX1:
		return "SMTC_MODEM_DL_WINDOW_RX1";
	case SMTC_MODEM_DL_WINDOW_RX2:
		return "SMTC_MODEM_DL_WINDOW_RX2";
	case SMTC_MODEM_DL_WINDOW_RXC:
		return "SMTC_MODEM_DL_WINDOW_RXC";
	case SMTC_MODEM_DL_WINDOW_RXC_MC_GRP0:
		return "SMTC_MODEM_DL_WINDOW_RXC_MC_GRP0";
	case SMTC_MODEM_DL_WINDOW_RXC_MC_GRP1:
		return "SMTC_MODEM_DL_WINDOW_RXC_MC_GRP1";
	case SMTC_MODEM_DL_WINDOW_RXC_MC_GRP2:
		return "SMTC_MODEM_DL_WINDOW_RXC_MC_GRP2";
	case SMTC_MODEM_DL_WINDOW_RXC_MC_GRP3:
		return "SMTC_MODEM_DL_WINDOW_RXC_MC_GRP3";
	case SMTC_MODEM_DL_WINDOW_RXB:
		return "SMTC_MODEM_DL_WINDOW_RXB";
	case SMTC_MODEM_DL_WINDOW_RXB_MC_GRP0:
		return "SMTC_MODEM_DL_WINDOW_RXB_MC_GRP0";
	case SMTC_MODEM_DL_WINDOW_RXB_MC_GRP1:
		return "SMTC_MODEM_DL_WINDOW_RXB_MC_GRP1";
	case SMTC_MODEM_DL_WINDOW_RXB_MC_GRP2:
		return "SMTC_MODEM_DL_WINDOW_RXB_MC_GRP2";
	case SMTC_MODEM_DL_WINDOW_RXB_MC_GRP3:
		return "SMTC_MODEM_DL_WINDOW_RXB_MC_GRP3";
	case SMTC_MODEM_DL_WINDOW_RXBEACON:
		return "SMTC_MODEM_DL_WINDOW_RXBEACON";
	case SMTC_MODEM_DL_WINDOW_RXR:
		return "SMTC_MODEM_DL_WINDOW_RXR";
	}
	return "???";
}

const char *
smtc_modem_store_and_forward_state_to_str(const smtc_modem_store_and_forward_state_t value)
{
	switch (value) {
	case SMTC_MODEM_STORE_AND_FORWARD_DISABLE:
		return "SMTC_MODEM_STORE_AND_FORWARD_DISABLE";
	case SMTC_MODEM_STORE_AND_FORWARD_ENABLE:
		return "SMTC_MODEM_STORE_AND_FORWARD_ENABLE";
	case SMTC_MODEM_STORE_AND_FORWARD_SUSPEND:
		return "SMTC_MODEM_STORE_AND_FORWARD_SUSPEND";
	}
	return "???";
}

const char *smtc_modem_stream_cipher_mode_to_str(const smtc_modem_stream_cipher_mode_t value)
{
	switch (value) {
	case SMTC_MODEM_STREAM_NO_CIPHER:
		return "SMTC_MODEM_STREAM_NO_CIPHER";
	case SMTC_MODEM_STREAM_AES_WITH_APPSKEY:
		return "SMTC_MODEM_STREAM_AES_WITH_APPSKEY";
	}
	return "???";
}

const char *
smtc_modem_file_upload_cipher_mode_to_str(const smtc_modem_file_upload_cipher_mode_t value)
{
	switch (value) {
	case SMTC_MODEM_FILE_UPLOAD_NO_CIPHER:
		return "SMTC_MODEM_FILE_UPLOAD_NO_CIPHER";
	case SMTC_MODEM_FILE_UPLOAD_AES_WITH_APPSKEY:
		return "SMTC_MODEM_FILE_UPLOAD_AES_WITH_APPSKEY";
	}
	return "???";
}

const char *
smtc_modem_dm_info_interval_format_to_str(const smtc_modem_dm_info_interval_format_t value)
{
	switch (value) {
	case SMTC_MODEM_DM_INFO_INTERVAL_IN_SECOND:
		return "SMTC_MODEM_DM_INFO_INTERVAL_IN_SECOND";
	case SMTC_MODEM_DM_INFO_INTERVAL_IN_DAY:
		return "SMTC_MODEM_DM_INFO_INTERVAL_IN_DAY";
	case SMTC_MODEM_DM_INFO_INTERVAL_IN_HOUR:
		return "SMTC_MODEM_DM_INFO_INTERVAL_IN_HOUR";
	case SMTC_MODEM_DM_INFO_INTERVAL_IN_MINUTE:
		return "SMTC_MODEM_DM_INFO_INTERVAL_IN_MINUTE";
	}
	return "???";
}

const char *smtc_modem_dm_field_to_str(const smtc_modem_dm_field_t value)
{
	switch (value) {
	case SMTC_MODEM_DM_FIELD_STATUS:
		return "SMTC_MODEM_DM_FIELD_STATUS";
	case SMTC_MODEM_DM_FIELD_CHARGE:
		return "SMTC_MODEM_DM_FIELD_CHARGE";
	case SMTC_MODEM_DM_FIELD_VOLTAGE:
		return "SMTC_MODEM_DM_FIELD_VOLTAGE";
	case SMTC_MODEM_DM_FIELD_TEMPERATURE:
		return "SMTC_MODEM_DM_FIELD_TEMPERATURE";
	case SMTC_MODEM_DM_FIELD_SIGNAL:
		return "SMTC_MODEM_DM_FIELD_SIGNAL";
	case SMTC_MODEM_DM_FIELD_UP_TIME:
		return "SMTC_MODEM_DM_FIELD_UP_TIME";
	case SMTC_MODEM_DM_FIELD_RX_TIME:
		return "SMTC_MODEM_DM_FIELD_RX_TIME";
	case SMTC_MODEM_DM_FIELD_ADR_MODE:
		return "SMTC_MODEM_DM_FIELD_ADR_MODE";
	case SMTC_MODEM_DM_FIELD_JOIN_EUI:
		return "SMTC_MODEM_DM_FIELD_JOIN_EUI";
	case SMTC_MODEM_DM_FIELD_INTERVAL:
		return "SMTC_MODEM_DM_FIELD_INTERVAL";
	case SMTC_MODEM_DM_FIELD_REGION:
		return "SMTC_MODEM_DM_FIELD_REGION";
	case SMTC_MODEM_DM_FIELD_CRASHLOG:
		return "SMTC_MODEM_DM_FIELD_CRASHLOG";
	case SMTC_MODEM_DM_FIELD_RST_COUNT:
		return "SMTC_MODEM_DM_FIELD_RST_COUNT";
	case SMTC_MODEM_DM_FIELD_DEV_EUI:
		return "SMTC_MODEM_DM_FIELD_DEV_EUI";
	case SMTC_MODEM_DM_FIELD_SESSION:
		return "SMTC_MODEM_DM_FIELD_SESSION";
	case SMTC_MODEM_DM_FIELD_CHIP_EUI:
		return "SMTC_MODEM_DM_FIELD_CHIP_EUI";
	case SMTC_MODEM_DM_INFO_STREAMPAR:
		return "SMTC_MODEM_DM_INFO_STREAMPAR";
	case SMTC_MODEM_DM_FIELD_APP_STATUS:
		return "SMTC_MODEM_DM_FIELD_APP_STATUS";
	}
	return "???";
}

const char *smtc_modem_event_type_to_str(const smtc_modem_event_type_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_RESET:
		return "SMTC_MODEM_EVENT_RESET";
	case SMTC_MODEM_EVENT_ALARM:
		return "SMTC_MODEM_EVENT_ALARM";
	case SMTC_MODEM_EVENT_JOINED:
		return "SMTC_MODEM_EVENT_JOINED";
	case SMTC_MODEM_EVENT_TXDONE:
		return "SMTC_MODEM_EVENT_TXDONE";
	case SMTC_MODEM_EVENT_DOWNDATA:
		return "SMTC_MODEM_EVENT_DOWNDATA";
	case SMTC_MODEM_EVENT_JOINFAIL:
		return "SMTC_MODEM_EVENT_JOINFAIL";
	case SMTC_MODEM_EVENT_ALCSYNC_TIME:
		return "SMTC_MODEM_EVENT_ALCSYNC_TIME";
	case SMTC_MODEM_EVENT_LINK_CHECK:
		return "SMTC_MODEM_EVENT_LINK_CHECK";
	case SMTC_MODEM_EVENT_CLASS_B_PING_SLOT_INFO:
		return "SMTC_MODEM_EVENT_CLASS_B_PING_SLOT_INFO";
	case SMTC_MODEM_EVENT_CLASS_B_STATUS:
		return "SMTC_MODEM_EVENT_CLASS_B_STATUS";
	case SMTC_MODEM_EVENT_LORAWAN_MAC_TIME:
		return "SMTC_MODEM_EVENT_LORAWAN_MAC_TIME";
	case SMTC_MODEM_EVENT_LORAWAN_FUOTA_DONE:
		return "SMTC_MODEM_EVENT_LORAWAN_FUOTA_DONE";
	case SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_C:
		return "SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_C";
	case SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_B:
		return "SMTC_MODEM_EVENT_NO_MORE_MULTICAST_SESSION_CLASS_B";
	case SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_C:
		return "SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_C";
	case SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_B:
		return "SMTC_MODEM_EVENT_NEW_MULTICAST_SESSION_CLASS_B";
	case SMTC_MODEM_EVENT_FIRMWARE_MANAGEMENT:
		return "SMTC_MODEM_EVENT_FIRMWARE_MANAGEMENT";
	case SMTC_MODEM_EVENT_STREAM_DONE:
		return "SMTC_MODEM_EVENT_STREAM_DONE";
	case SMTC_MODEM_EVENT_UPLOAD_DONE:
		return "SMTC_MODEM_EVENT_UPLOAD_DONE";
	case SMTC_MODEM_EVENT_DM_SET_CONF:
		return "SMTC_MODEM_EVENT_DM_SET_CONF";
	case SMTC_MODEM_EVENT_MUTE:
		return "SMTC_MODEM_EVENT_MUTE";
	case SMTC_MODEM_EVENT_GNSS_SCAN_DONE:
		return "SMTC_MODEM_EVENT_GNSS_SCAN_DONE";
	case SMTC_MODEM_EVENT_GNSS_TERMINATED:
		return "SMTC_MODEM_EVENT_GNSS_TERMINATED";
	case SMTC_MODEM_EVENT_GNSS_ALMANAC_DEMOD_UPDATE:
		return "SMTC_MODEM_EVENT_GNSS_ALMANAC_DEMOD_UPDATE";
	case SMTC_MODEM_EVENT_WIFI_SCAN_DONE:
		return "SMTC_MODEM_EVENT_WIFI_SCAN_DONE";
	case SMTC_MODEM_EVENT_WIFI_TERMINATED:
		return "SMTC_MODEM_EVENT_WIFI_TERMINATED";
	case SMTC_MODEM_EVENT_RELAY_TX_DYNAMIC:
		return "SMTC_MODEM_EVENT_RELAY_TX_DYNAMIC";
	case SMTC_MODEM_EVENT_RELAY_TX_MODE:
		return "SMTC_MODEM_EVENT_RELAY_TX_MODE";
	case SMTC_MODEM_EVENT_RELAY_TX_SYNC:
		return "SMTC_MODEM_EVENT_RELAY_TX_SYNC";
	case SMTC_MODEM_EVENT_MAX:
		return "SMTC_MODEM_EVENT_MAX";
	}
	return "???";
}

const char *smtc_modem_event_txdone_status_to_str(const smtc_modem_event_txdone_status_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_TXDONE_NOT_SENT:
		return "SMTC_MODEM_EVENT_TXDONE_NOT_SENT";
	case SMTC_MODEM_EVENT_TXDONE_SENT:
		return "SMTC_MODEM_EVENT_TXDONE_SENT";
	case SMTC_MODEM_EVENT_TXDONE_CONFIRMED:
		return "SMTC_MODEM_EVENT_TXDONE_CONFIRMED";
	}
	return "???";
}

const char *smtc_modem_event_class_b_status_to_str(const smtc_modem_event_class_b_status_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_CLASS_B_NOT_READY:
		return "SMTC_MODEM_EVENT_CLASS_B_NOT_READY";
	case SMTC_MODEM_EVENT_CLASS_B_READY:
		return "SMTC_MODEM_EVENT_CLASS_B_READY";
	}
	return "???";
}

const char *
smtc_modem_event_mac_request_status_to_str(const smtc_modem_event_mac_request_status_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_MAC_REQUEST_NOT_ANSWERED:
		return "SMTC_MODEM_EVENT_MAC_REQUEST_NOT_ANSWERED";
	case SMTC_MODEM_EVENT_MAC_REQUEST_ANSWERED:
		return "SMTC_MODEM_EVENT_MAC_REQUEST_ANSWERED";
	}
	return "???";
}

const char *smtc_modem_event_fmp_status_to_str(const smtc_modem_event_fmp_status_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_FMP_REBOOT_IMMEDIATELY:
		return "SMTC_MODEM_EVENT_FMP_REBOOT_IMMEDIATELY";
	case SMTC_MODEM_EVENT_FMP_CANCEL_REBOOT:
		return "SMTC_MODEM_EVENT_FMP_CANCEL_REBOOT";
	}
	return "???";
}

const char *smtc_modem_event_setconf_opcode_to_str(const smtc_modem_event_setconf_opcode_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_SETCONF_ADR_MODE_UPDATED:
		return "SMTC_MODEM_EVENT_SETCONF_ADR_MODE_UPDATED";
	case SMTC_MODEM_EVENT_SETCONF_JOIN_EUI_UPDATED:
		return "SMTC_MODEM_EVENT_SETCONF_JOIN_EUI_UPDATED";
	case SMTC_MODEM_EVENT_SETCONF_DM_INTERVAL_UPDATED:
		return "SMTC_MODEM_EVENT_SETCONF_DM_INTERVAL_UPDATED";
	case SMTC_MODEM_EVENT_SETCONF_REGION_UPDATED:
		return "SMTC_MODEM_EVENT_SETCONF_REGION_UPDATED";
	}
	return "???";
}

const char *smtc_modem_event_mute_status_to_str(const smtc_modem_event_mute_status_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_MUTE_OFF:
		return "SMTC_MODEM_EVENT_MUTE_OFF";
	case SMTC_MODEM_EVENT_MUTE_ON:
		return "SMTC_MODEM_EVENT_MUTE_ON";
	}
	return "???";
}

const char *
smtc_modem_event_uploaddone_status_to_str(const smtc_modem_event_uploaddone_status_t value)
{
	switch (value) {
	case SMTC_MODEM_EVENT_UPLOAD_DONE_ABORTED:
		return "SMTC_MODEM_EVENT_UPLOAD_DONE_ABORTED";
	case SMTC_MODEM_EVENT_UPLOAD_DONE_SUCCESSFUL:
		return "SMTC_MODEM_EVENT_UPLOAD_DONE_SUCCESSFUL";
	}
	return "???";
}
