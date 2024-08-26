/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SMTC_MODEM_API_STR_H
#define SMTC_MODEM_API_STR_H

#include "smtc_modem_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/* If printers are disabled, the function bellow will lack an implementation. Since they are mostly
 * used inline in LOG_* calls, we replace them with macros that desugar to "" (empty string), so the
 * LOG call is still valid.
 */
#ifdef CONFIG_LORA_BASICS_MODEM_PRINTERS

const char *smtc_modem_return_code_to_str(const smtc_modem_return_code_t value);
const char *smtc_modem_region_to_str(const smtc_modem_region_t value);
const char *smtc_modem_adr_profile_to_str(const smtc_modem_adr_profile_t value);
const char *smtc_modem_class_to_str(const smtc_modem_class_t value);
const char *smtc_modem_mc_grp_id_to_str(const smtc_modem_mc_grp_id_t value);
const char *smtc_modem_class_b_ping_slot_periodicity_to_str(
	const smtc_modem_class_b_ping_slot_periodicity_t value);
const char *
smtc_modem_lorawan_mac_request_mask_to_str(const smtc_modem_lorawan_mac_request_mask_t value);
const char *smtc_modem_dl_window_to_str(const smtc_modem_dl_window_t value);
const char *
smtc_modem_store_and_forward_state_to_str(const smtc_modem_store_and_forward_state_t value);
const char *smtc_modem_stream_cipher_mode_to_str(const smtc_modem_stream_cipher_mode_t value);
const char *
smtc_modem_file_upload_cipher_mode_to_str(const smtc_modem_file_upload_cipher_mode_t value);
const char *
smtc_modem_dm_info_interval_format_to_str(const smtc_modem_dm_info_interval_format_t value);
const char *smtc_modem_dm_field_to_str(const smtc_modem_dm_field_t value);
const char *smtc_modem_event_type_to_str(const smtc_modem_event_type_t value);
const char *smtc_modem_event_txdone_status_to_str(const smtc_modem_event_txdone_status_t value);
const char *smtc_modem_event_class_b_status_to_str(const smtc_modem_event_class_b_status_t value);
const char *
smtc_modem_event_mac_request_status_to_str(const smtc_modem_event_mac_request_status_t value);
const char *smtc_modem_event_fmp_status_to_str(const smtc_modem_event_fmp_status_t value);
const char *smtc_modem_event_setconf_opcode_to_str(const smtc_modem_event_setconf_opcode_t value);
const char *smtc_modem_event_mute_status_to_str(const smtc_modem_event_mute_status_t value);
const char *
smtc_modem_event_uploaddone_status_to_str(const smtc_modem_event_uploaddone_status_t value);

#else

#define smtc_modem_return_code_to_str(...)		     ""
#define smtc_modem_region_to_str(...)			     ""
#define smtc_modem_adr_profile_to_str(...)		     ""
#define smtc_modem_class_to_str(...)			     ""
#define smtc_modem_mc_grp_id_to_str(...)		     ""
#define smtc_modem_class_b_ping_slot_periodicity_to_str(...) ""
#define smtc_modem_lorawan_mac_request_mask_to_str(...)	     ""
#define smtc_modem_dl_window_to_str(...)		     ""
#define smtc_modem_store_and_forward_state_to_str(...)	     ""
#define smtc_modem_stream_cipher_mode_to_str(...)	     ""
#define smtc_modem_file_upload_cipher_mode_to_str(...)	     ""
#define smtc_modem_dm_info_interval_format_to_str(...)	     ""
#define smtc_modem_dm_field_to_str(...)			     ""
#define smtc_modem_event_type_to_str(...)		     ""
#define smtc_modem_event_txdone_status_to_str(...)	     ""
#define smtc_modem_event_class_b_status_to_str(...)	     ""
#define smtc_modem_event_mac_request_status_to_str(...)	     ""
#define smtc_modem_event_fmp_status_to_str(...)		     ""
#define smtc_modem_event_setconf_opcode_to_str(...)	     ""
#define smtc_modem_event_mute_status_to_str(...)	     ""
#define smtc_modem_event_uploaddone_status_to_str(...)	     ""

#endif /* CONFIG_LORA_BASICS_MODEM_PRINTERS */

#ifdef __cplusplus
}
#endif

#endif // SMTC_MODEM_API_STR_H
