#THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.29)

if (BUILD_TESTS)
    project(TESTS)
    add_subdirectory(tests)
else ()
    add_subdirectory(hardware)
endif ()