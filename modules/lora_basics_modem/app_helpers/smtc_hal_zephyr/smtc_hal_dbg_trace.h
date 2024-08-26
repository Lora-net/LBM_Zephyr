/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SMTC_HAL_DBG_TRACE_H__
#define __SMTC_HAL_DBG_TRACE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */
#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type

// #include "smtc_hal_trace.h"
#include "smtc_modem_hal_dbg_trace.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

// clang-format off
#define HAL_FEATURE_OFF                             0
#define HAL_FEATURE_ON                              !HAL_FEATURE_OFF

// Sensible default values. Change in Makefile if needed
#ifndef HAL_DBG_TRACE
#define HAL_DBG_TRACE                               HAL_FEATURE_ON
#endif

#ifndef HAL_DBG_TRACE_COLOR
#define HAL_DBG_TRACE_COLOR                         HAL_FEATURE_ON
#endif

#ifndef HAL_DBG_TRACE_RP
#define HAL_DBG_TRACE_RP                            HAL_FEATURE_OFF
#endif
// clang-format on

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

#if ( HAL_DBG_TRACE )

	#define SMTC_HAL_TRACE_PRINTF( ... )				SMTC_MODEM_HAL_TRACE_PRINTF(__VA_ARGS__)
	#define SMTC_HAL_TRACE_MSG( msg )					SMTC_MODEM_HAL_TRACE_MSG(msg)
	#define SMTC_HAL_TRACE_INFO( ... )					SMTC_MODEM_HAL_TRACE_INFO(__VA_ARGS__)
	#define SMTC_HAL_TRACE_WARNING( ... )				SMTC_MODEM_HAL_TRACE_WARNING(__VA_ARGS__)
	#define SMTC_HAL_TRACE_ERROR( ... )					SMTC_MODEM_HAL_TRACE_ERROR(__VA_ARGS__)
	#define SMTC_HAL_TRACE_ARRAY( msg, array, len )		SMTC_MODEM_HAL_TRACE_ARRAY(msg, array, len)
	#define SMTC_HAL_TRACE_PACKARRAY( ... )				SMTC_MODEM_HAL_TRACE_PACKARRAY(__VA_ARGS__)

#else
    #define SMTC_HAL_TRACE_PRINTF( ... )
    #define SMTC_HAL_TRACE_MSG( msg )
    #define SMTC_HAL_TRACE_MSG_COLOR( msg, color )
    #define SMTC_HAL_TRACE_INFO( ... )
    #define SMTC_HAL_TRACE_WARNING( ... )
    #define SMTC_HAL_TRACE_ERROR( ... )
    #define SMTC_HAL_TRACE_ARRAY( msg, array, len )
    #define SMTC_HAL_TRACE_PACKARRAY( ... )

#endif

// clang-format on

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif  // __SMTC_HAL_DBG_TRACE_H__

/* --- EOF ------------------------------------------------------------------ */
