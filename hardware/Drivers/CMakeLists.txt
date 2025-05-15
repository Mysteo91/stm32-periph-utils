project(STM32_Drivers)

file(GLOB_RECURSE Sources
        "STM32H5xx_HAL_Driver/Src/*.*"
)


add_definitions(-DUSE_HAL_DRIVER -DSTM32H523xx)
add_library(STM32_Drivers ${Sources})
target_include_directories(STM32_Drivers PUBLIC STM32H5xx_HAL_Driver/Inc CMSIS/Device/Include CMSIS/Device/ST/STM32H5xx/Include ${HAL_CONFIG_FILE_DIR})
