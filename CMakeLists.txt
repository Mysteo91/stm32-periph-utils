#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
cmake_minimum_required(VERSION 3.29)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)


set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(test_project C CXX ASM)

# project settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(UART_HW_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/examples/stm32h523/Core/Src/UART_HW_CONFIG.h)
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/examples/stm32h523/STM32H523CEUX_FLASH.ld)
set(HAL_CONFIG_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples/stm32h523/Core/HAL_CONFIG)
set(STM32_STARTUP_FILE ${CMAKE_CURRENT_SOURCE_DIR}/examples/stm32h523/Core/Startup/startup_stm32h523ceux.s)

add_definitions(-DUSE_HAL_DRIVER -DSTM32H523xx)
add_compile_options(-mcpu=cortex-m33 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

add_subdirectory(lib/uartLib)
add_subdirectory(Drivers)
add_subdirectory(examples/stm32h523)


