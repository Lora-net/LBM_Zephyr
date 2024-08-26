/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SMTC_HAL_MCU_H__
#define __SMTC_HAL_MCU_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>   // C99 types

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

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

/*!
 * Disable all irq at mcu side
 */
void hal_mcu_disable_irq( void );

/*!
 * Enable all irq at mcu side
 */
void hal_mcu_enable_irq( void );

/*!
 * Initializes BSP used MCU
 */
void hal_mcu_init( void );

/*!
 * Blocking wait
 */
void hal_mcu_wait_us( const int32_t microseconds );

/*!
 * Sets the MCU in sleep mode for the given number of milliseconds.
 *
 * \param[IN] milliseconds Number of milliseconds to stay in sleep mode
 */
void hal_mcu_set_sleep_for_ms( const int32_t milliseconds );


#ifdef __cplusplus
}
#endif

#endif  // __SMTC_HAL_MCU_H__

/* --- EOF ------------------------------------------------------------------ */
