cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++17

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_executable(test1.exe
        src/sample1_test.cpp
)
target_link_libraries(test1.exe gtest_main)
target_include_directories(test1.exe PRIVATE src)
