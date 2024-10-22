cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_STANDARD 18)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Define the build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

# Set the project name
set(CMAKE_PROJECT_NAME scratch)
project(${CMAKE_PROJECT_NAME})

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(CXX C ASM)

# Core project settings
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/freertos)
add_subdirectory(cmake/stm32)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE inc)

set(freeRTOS "/home/ksolomon/git/FreeRTOS/FreeRTOS/Source")
set(port "${freeRTOS}/portable/GCC/ARM_CM4F")

# Add sources to executable
target_sources(
    ${CMAKE_PROJECT_NAME}
    PRIVATE startup_stm32l4a6xx.s
            STM32L4A6ZGTx_FLASH.ld
            src/main.cpp
            src/stm32l4xx_it.c
            src/stm32l4xx_hal_msp.c
            src/system_stm32l4xx.c
            src/tasks/rtosInit.cpp
            ${port}/port.c
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE stm32 freertos # Add user defined libraries
)
