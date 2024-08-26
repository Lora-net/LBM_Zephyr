# Copyright (c) 2024 Semtech Corporation - Félix Piédallu
# SPDX-License-Identifier: Apache-2.0

# Used by LBM
zephyr_compile_definitions(SX127X)
zephyr_compile_definitions(SX127X_DISABLE_WARNINGS)

# sx127x families
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1271_NEW_ENABLED SX1272)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1272_NEW_ENABLED SX1272)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1273_NEW_ENABLED SX1272)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1276_NEW_ENABLED SX1276)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1277_NEW_ENABLED SX1276)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1278_NEW_ENABLED SX1276)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1279_NEW_ENABLED SX1276)

# "exact" macros
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1271_NEW_ENABLED SX1271)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1272_NEW_ENABLED SX1272)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1273_NEW_ENABLED SX1273)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1276_NEW_ENABLED SX1276)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1277_NEW_ENABLED SX1277)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1278_NEW_ENABLED SX1278)
zephyr_compile_definitions_ifdef(CONFIG_DT_HAS_SEMTECH_SX1279_NEW_ENABLED SX1279)

set(LBM_SX127X_LIB_DIR ${LBM_RADIO_DRIVERS_DIR}/sx127x_driver/src)
zephyr_include_directories(${LBM_SX127X_LIB_DIR})

#-----------------------------------------------------------------------------
# Radio specific sources
#-----------------------------------------------------------------------------

zephyr_library_sources(
  ${LBM_SX127X_LIB_DIR}/sx127x.c
)

# Used later
set(LBM_RAL_SOURCES ${LBM_SMTC_MODEM_CORE_DIR}/smtc_ral/src/ral_sx127x.c)
set(LBM_RALF_SOURCES ${LBM_SMTC_MODEM_CORE_DIR}/smtc_ralf/src/ralf_sx127x.c)
