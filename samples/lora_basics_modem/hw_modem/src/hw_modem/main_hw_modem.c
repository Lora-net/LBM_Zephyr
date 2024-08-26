/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h> // bool type
#include <stdint.h>  // C99 types
#include <zephyr/kernel.h>

#include "main.h"

#include "git_version.h"

#include "smtc_modem_hal.h"
#include "smtc_hal_dbg_trace.h"

#include "smtc_modem_api.h"
#include "smtc_hal_mcu.h"
#include "smtc_hal_watchdog.h"

#include "hw_modem.h"
#include "smtc_modem_utilities.h"

#include <zephyr/kernel.h>
#include <smtc_modem_hal_init.h>

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(hw_modem, 3);


/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE MACROS-----------------------------------------------------------
 */

/**
 * @brief Returns the minimum value between a and b
 *
 * @param [in] a 1st value
 * @param [in] b 2nd value
 * @retval Minimum value
 */
#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

/**
 * @brief Watchdog counter reload value during sleep (The period must be lower than MCU watchdog period (here 32s))
 */
#define WATCHDOG_RELOAD_PERIOD_MS 20000
/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */


/**
 * @brief Main function for hw modem use
 */
void main_hw_modem( void )
{
    hal_mcu_disable_irq( );

    hal_mcu_init( );

    hal_watchdog_init( );

    hw_modem_init( );

    hal_mcu_enable_irq( );

    SMTC_HAL_TRACE_INFO( "Modem is starting\n" );
    SMTC_HAL_TRACE_PRINTF( "Commit SHA1: %s\n", get_software_git_commit( ) );
    SMTC_HAL_TRACE_PRINTF( "Commit date: %s\n", get_software_git_date( ) );
    SMTC_HAL_TRACE_PRINTF( "Build date: %s\n", get_software_build_date( ) );

    uint32_t sleep_time_ms = 0;
    while( 1 )
    {
        // Check if a command is available
        if( hw_modem_is_a_cmd_available( ) == true )
        {
            // Command may generate work for the stack, so drop down to smtc_modem_run_engine().
            hw_modem_process_cmd( );
        }

        // Modem process launch
        sleep_time_ms = smtc_modem_run_engine( );


	// Atomically check sleep conditions (no command available and low power is possible)
	//
	// NOTE: We have to remove the hal_mcu_disable_irq() and hal_mcu_enable_irq() calls
	// here because of the way GPIO interrupts are implemented in smtc_hal_gpio.c.
	//
	// Even as the code as now, any command received while hal_mcu_set_sleep_for_ms is active
	// will wait for hal_mcu_set_sleep_for_ms to finish before being processed.
	// Is this intended?? (up to 20s delay between commands?)

        // hal_mcu_disable_irq( );
        if( ( hw_modem_is_a_cmd_available( ) == false ) && ( hw_modem_is_low_power_ok( ) == true ) &&
            ( smtc_modem_is_irq_flag_pending( ) == false ) )
        {
            hal_watchdog_reload( );

            uint32_t real_sleep_time_ms = MIN( sleep_time_ms, WATCHDOG_RELOAD_PERIOD_MS );
            // LOG_INF( "Sleeping for %d ms", real_sleep_time_ms);
            // hal_mcu_set_sleep_for_ms(real_sleep_time_ms);
            // real_sleep_time_ms = 1;
            smtc_modem_hal_interruptible_msleep(K_MSEC(real_sleep_time_ms));
        }
        hal_watchdog_reload( );
	// hal_mcu_enable_irq( );
    }
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

/* --- EOF ------------------------------------------------------------------ */
