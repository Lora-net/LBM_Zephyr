# Copyright (c) 2024 Semtech Corporation - Félix Piédallu
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

# create compile_commands.json for clang
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(Zephyr HINTS $ENV{ZEPHYR_BASE})
project(hw_modem)

zephyr_compile_options(-fdiagnostics-color=always)

add_subdirectory(src)

# Based on some LBM features, different flags are used in the sample for some
# reason, so we map to them here.
zephyr_compile_definitions_ifdef(CONFIG_LORA_BASICS_MODEM_GEOLOCATION
                                 ADD_APP_GEOLOCATION)

zephyr_compile_definitions_ifdef(LORA_BASICS_MODEM_CRYPTOGRAPHY_LR11XX
                                 USE_LR11XX_CRYPTO)
zephyr_compile_definitions_ifdef(
  LORA_BASICS_MODEM_CRYPTOGRAPHY_LR11XX_WITH_CREDENTIALS USE_LR11XX_CRYPTO)

zephyr_compile_definitions_ifdef(CONFIG_LORA_BASICS_MODEM_RELAY_TX_ENABLE
                                 USE_RELAY_TX)
