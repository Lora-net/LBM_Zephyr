/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef HW_MODEM_H__
#define HW_MODEM_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types
#include <stdbool.h>  // bool type

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
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

/**
 * @brief Init the hw_modem. It takes care of all hw part of the modem and the init of the soft modem part
 */
void hw_modem_init( void );

/**
 * @brief Process the latest received command
 */
void hw_modem_process_cmd( void );

/**
 * @brief Indicates if a command is ready to by processed
 *
 * @return true if a command is ready to by processed, false otherwise
 */
bool hw_modem_is_a_cmd_available( void );

/**
 * @brief Indicates if main application can go in low power
 *
 * @return true/false
 */
bool hw_modem_is_low_power_ok( void );

#ifdef __cplusplus
}
#endif

#endif  // HW_MODEM_H__

/* --- EOF ------------------------------------------------------------------ */
