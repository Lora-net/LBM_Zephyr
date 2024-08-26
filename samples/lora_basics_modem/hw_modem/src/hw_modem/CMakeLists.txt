# Copyright (c) 2024 Semtech Corporation - Félix Piédallu
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(.)

target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cmd_parser.c)
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/git_version.c)
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hw_modem.c)
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main_hw_modem.c)

if(CONFIG_LORA_BASICS_MODEM_GEOLOCATION)
  target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/geoloc_bsp.c)
endif()
