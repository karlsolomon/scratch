cmake_minimum_required(VERSION 3.30)

project(freertos)
add_library(freertos INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(CXX C ASM)

# target_compile_definitions(freertos INTERFACE $<$<CONFIG:Debug>:DEBUG>)

set(freeRTOS "/home/ksolomon/git/FreeRTOS/FreeRTOS/Source")
set(port "${freeRTOS}/portable/GCC/ARM_CM4F")

target_include_directories(freertos INTERFACE ${freeRTOS}/include ${port})

target_sources(
    freertos
    INTERFACE ${freeRTOS}/portable/MemMang/heap_4.c
              ${freeRTOS}/list.c
              ${freeRTOS}/tasks.c
              ${freeRTOS}/timers.c
              ${freeRTOS}/queue.c
              ${port}/port.c
)

target_link_directories(freertos INTERFACE)

target_link_libraries(freertos INTERFACE)
