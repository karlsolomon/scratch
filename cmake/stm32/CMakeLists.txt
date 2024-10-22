cmake_minimum_required(VERSION 3.30)

project(stm32)
add_library(stm32 INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(CXX C ASM)

target_compile_definitions(
    stm32
    INTERFACE USE_FULL_LL_DRIVER
              USE_HAL_DRIVER
              STM32L4A6xx
              $<$<CONFIG:Debug>:DEBUG>
)

set(cube "/home/ksolomon/STM32Cube/Repository/STM32Cube_FW_L4_V1.18.1")
set(cubeDrivers "${cube}/Drivers")
set(hal "${cubeDrivers}/STM32L4xx_HAL_Driver")

target_include_directories(
    stm32
    INTERFACE ${hal}/Inc
              ${hal}/Inc/Legacy
              ${cubeDrivers}/CMSIS/Device/ST/STM32L4xx/Include
              ${cubeDrivers}/CMSIS/Include
)

message(STATUS "HAL: ${hal}")

target_sources(
    stm32
    PUBLIC ${hal}/Src/stm32l4xx_ll_utils.c
           ${hal}/Src/stm32l4xx_ll_exti.c
           ${hal}/Src/stm32l4xx_ll_gpio.c
           ${hal}/Src/stm32l4xx_hal_pcd.c
           ${hal}/Src/stm32l4xx_hal_pcd_ex.c
           ${hal}/Src/stm32l4xx_ll_usb.c
           ${hal}/Src/stm32l4xx_hal.c
           ${hal}/Src/stm32l4xx_hal_rcc.c
           ${hal}/Src/stm32l4xx_hal_rcc_ex.c
           ${hal}/Src/stm32l4xx_hal_flash.c
           ${hal}/Src/stm32l4xx_hal_flash_ex.c
           ${hal}/Src/stm32l4xx_hal_flash_ramfunc.c
           ${hal}/Src/stm32l4xx_hal_gpio.c
           ${hal}/Src/stm32l4xx_hal_i2c.c
           ${hal}/Src/stm32l4xx_hal_i2c_ex.c
           ${hal}/Src/stm32l4xx_hal_dma.c
           ${hal}/Src/stm32l4xx_hal_dma_ex.c
           ${hal}/Src/stm32l4xx_hal_pwr.c
           ${hal}/Src/stm32l4xx_hal_pwr_ex.c
           ${hal}/Src/stm32l4xx_hal_cortex.c
           ${hal}/Src/stm32l4xx_hal_exti.c
           ${hal}/Src/stm32l4xx_hal_cryp.c
           ${hal}/Src/stm32l4xx_hal_cryp_ex.c
           ${hal}/Src/stm32l4xx_hal_hash.c
           ${hal}/Src/stm32l4xx_hal_hash_ex.c
           ${hal}/Src/stm32l4xx_ll_i2c.c
           ${hal}/Src/stm32l4xx_ll_dma.c
           ${hal}/Src/stm32l4xx_ll_lptim.c
           ${hal}/Src/stm32l4xx_ll_rcc.c
           ${hal}/Src/stm32l4xx_ll_lpuart.c
           ${hal}/Src/stm32l4xx_ll_usart.c
           ${hal}/Src/stm32l4xx_hal_qspi.c
           ${hal}/Src/stm32l4xx_ll_rng.c
           ${hal}/Src/stm32l4xx_ll_spi.c
           ${hal}/Src/stm32l4xx_hal_tim.c
           ${hal}/Src/stm32l4xx_hal_tim_ex.c
           ${hal}/Src/stm32l4xx_ll_tim.c
)

target_link_directories(stm32 INTERFACE)

target_link_libraries(stm32 INTERFACE)

# Validate that STM32CubeMX code is compatible with C standard
if (CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif ()
