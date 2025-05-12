cmake_minimum_required(VERSION 3.25)
set(CMAKE_C_STANDARD 99)

if(NOT UART_HW_CONFIG_FILE)
    message(FATAL_ERROR "please set UART_HW_CONFIG_FILE - fullpath to uart config file")
endif ()

# Setup aviaradar as lib
file(GLOB_RECURSE UART_HW_SOURCES
    "src/*.*"
)

add_library(uart_hw_hal_lib STATIC ${UART_HW_SOURCES})
target_compile_definitions(uart_hw_hal_lib PUBLIC UART_APP_CONFIG="${UART_HW_CONFIG_FILE}")
target_include_directories(uart_hw_hal_lib

        PRIVATE  src
        PUBLIC src/user_layer
)
