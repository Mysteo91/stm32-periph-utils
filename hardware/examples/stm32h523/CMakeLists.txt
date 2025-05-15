#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.29)


# project settings
project(stm32_periph_util C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include_directories(Core/HAL_CONFIG Core/Inc USBX/App USBX/Target Drivers/STM32H5xx_HAL_Driver/Inc Drivers/STM32H5xx_HAL_Driver/Inc/Legacy Drivers/CMSIS/Device/ST/STM32H5xx/Include Middlewares/ST/usbx/common/core/inc Middlewares/ST/usbx/ports/generic/inc Drivers/CMSIS/Include)

add_definitions(-DUSE_HAL_DRIVER -DSTM32H523xx)

file(GLOB_RECURSE SOURCES  "Core/Src/*.*" "Middlewares/*.*" "Drivers/*.*")

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m33 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

set (UART_HW_CONFIG_FILE  ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/UART_HW_CONFIG.h)


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


add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

target_link_libraries(${PROJECT_NAME}.elf PRIVATE STM32_Drivers  -Wl,--whole-archive uart_hw_hal_lib -Wl,--no-whole-archive  startup)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")
