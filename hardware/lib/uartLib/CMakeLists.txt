cmake_minimum_required(VERSION 3.25)
set(CMAKE_C_STANDARD 99)

if(NOT UART_HW_CONFIG_FILE)
    message(FATAL_ERROR "please set UART_HW_CONFIG_FILE - fullpath to uart config file")
endif ()

# Setup aviaradar as lib
file(GLOB_RECURSE UART_HW_SOURCES
        "src/*.*"
        "${HAL_DRIVERS}/Src/*.*"
)


add_definitions(-DUSE_HAL_DRIVER -DSTM32H523xx)
add_library(startup STATIC ${STM32_STARTUP_FILE})
add_library(uartLib STATIC ${UART_HW_SOURCES} )

target_compile_definitions(uartLib PUBLIC UART_APP_CONFIG="${UART_HW_CONFIG_FILE}")
target_include_directories(uartLib

        PRIVATE  src ${HAL_DRIVERS}/Inc
        PUBLIC src/user_layer ${HAL_CONFIG_FILE_DIR}
)


target_link_libraries(uartLib PUBLIC STM32_Drivers
       )
