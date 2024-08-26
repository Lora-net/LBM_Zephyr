# Copyright (c) 2024 Semtech Corporation - Félix Piédallu
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/apps_common/smtc_app
  ${CMAKE_CURRENT_LIST_DIR}/apps_common/printers
  ${CMAKE_CURRENT_LIST_DIR}/smtc_hal_zephyr
)

zephyr_library_sources(
  ${CMAKE_CURRENT_LIST_DIR}/smtc_hal_zephyr/smtc_hal_gpio.c
  ${CMAKE_CURRENT_LIST_DIR}/smtc_hal_zephyr/smtc_hal_mcu.c
  ${CMAKE_CURRENT_LIST_DIR}/smtc_hal_zephyr/smtc_hal_uart.c
  ${CMAKE_CURRENT_LIST_DIR}/smtc_hal_zephyr/smtc_hal_watchdog.c
  ${CMAKE_CURRENT_LIST_DIR}/apps_common/smtc_app/smtc_app.c
)
zephyr_library_sources_ifdef(CONFIG_LORA_BASICS_MODEM_PRINTERS
  ${CMAKE_CURRENT_LIST_DIR}/apps_common/printers/smtc_modem_api_str.c
)
