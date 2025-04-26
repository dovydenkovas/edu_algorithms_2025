cmake_minimum_required(VERSION 3.20)

SET (CMAKE_CXX_FLAGS_INIT "-Wall -std=c++23")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(operatordb)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS On)
enable_testing()

add_executable(operatordb src/main.cpp)

add_executable(tests tests/test.cpp)
target_link_libraries(tests gtest gmock pthread algo)
