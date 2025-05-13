cmake_minimum_required(VERSION 3.25)
set(CMAKE_C_STANDARD 99)

if(NOT UART_HW_CONFIG_FILE)
    message(FATAL_ERROR "please set UART_HW_CONFIG_FILE - fullpath to uart config file")
endif ()

if(NOT STM32_STARTUP_FILE)
    message(FATAL_ERROR "please set STM32_STARTUP_FILE - fullpath to startup file of STM32")
endif ()

if(NOT LINKER_SCRIPT)
    message(FATAL_ERROR "please set LINKER_SCRIPT - fullpath to LINKER_SCRIPT file of STM32")
endif ()


# Setup aviaradar as lib
file(GLOB_RECURSE UART_HW_SOURCES
        "src/*.*"
        "${HAL_DRIVERS}/Src/*.*"
)


add_definitions(-DUSE_HAL_DRIVER -DSTM32H523xx)
add_library(uart_hw_hal_lib STATIC ${UART_HW_SOURCES} )

target_compile_definitions(uart_hw_hal_lib PUBLIC UART_APP_CONFIG="${UART_HW_CONFIG_FILE}")
target_include_directories(uart_hw_hal_lib

        PRIVATE  src ${HAL_DRIVERS}/Inc
        PUBLIC src/user_layer ${HAL_CONFIG_FILE_DIR}
)
target_link_libraries(uart_hw_hal_lib PUBLIC STM32_Drivers)
