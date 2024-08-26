/*
 * Copyright (c) 2024 Semtech Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SMTC_HAL_GPIO_H__
#define __SMTC_HAL_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h>
#include <zephyr/drivers/gpio.h>

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

/*!
 * GPIO IRQ data context
 */
typedef struct gpio_irq_s
{
    const struct gpio_dt_spec *pin;
    void*   context;
    void ( *callback )( void* context );
} hal_gpio_irq_t;

/*!
 * GPIO Pull modes
 */
typedef enum gpio_pull_mode_e
{
    BSP_GPIO_PULL_MODE_NONE = 0,
    BSP_GPIO_PULL_MODE_UP   = 1,
    BSP_GPIO_PULL_MODE_DOWN = 2,
} hal_gpio_pull_mode_t;

/*!
 * GPIO IRQ modes
 */
typedef enum gpio_irq_mode_e
{
    BSP_GPIO_IRQ_MODE_OFF            = 0,
    BSP_GPIO_IRQ_MODE_RISING         = 1,
    BSP_GPIO_IRQ_MODE_FALLING        = 2,
    BSP_GPIO_IRQ_MODE_RISING_FALLING = 3,
} hal_gpio_irq_mode_t;

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/*!
 * Initializes given pin as output with given initial value
 *
 * \param [in] pin   MCU pin to be initialized
 * \param [in] value MCU initial pit state
 *
 */
void hal_gpio_init_out( const struct gpio_dt_spec *pin, const uint32_t value );

/*!
 * Initializes given pin as input
 *
 * \param [in]     pin       MCU pin to be initialized
 * \param [in]     pull_mode MCU pin pull mode [BSP_GPIO_PULL_MODE_NONE,
 *                                              BSP_GPIO_PULL_MODE_UP,
 *                                              BSP_GPIO_PULL_MODE_DOWN]
 * \param [in]     irq_mode  MCU IRQ mode [BSP_GPIO_IRQ_MODE_OFF,
 *                                         BSP_GPIO_IRQ_MODE_RISING,
 *                                         BSP_GPIO_IRQ_MODE_FALLING,
 *                                         BSP_GPIO_IRQ_MODE_RISING_FALLING]
 * \param [in/out] irq       Pointer to IRQ data context.
 *                              NULL when BSP_GPIO_IRQ_MODE_OFF
 *                              pin parameter is initialized
 */
void hal_gpio_init_in( const struct gpio_dt_spec *pin, const hal_gpio_pull_mode_t pull_mode, const hal_gpio_irq_mode_t irq_mode,
                       hal_gpio_irq_t* irq );

/*!
 * Sets MCU pin to given value
 *
 * \param [in] pin   MCU pin to be set
 * \param [in] value MCU pin state to be set
 */
void hal_gpio_set_value( const struct gpio_dt_spec *pin, const uint32_t value );

/*!
 * Gets MCU pin state value
 *
 * \param [in] pin   MCU pin to be read
 *
 * \retval value Current MCU pin state
 */
uint32_t hal_gpio_get_value( const struct gpio_dt_spec *pin );

void hal_gpio_irq_enable_set(bool enable);

#ifdef __cplusplus
}
#endif

#endif  // __SMTC_HAL_GPIO_H__

/* --- EOF ------------------------------------------------------------------ */
