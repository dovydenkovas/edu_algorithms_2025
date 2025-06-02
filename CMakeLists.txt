cmake_minimum_required(VERSION 3.21)

SET (CMAKE_CXX_FLAGS_INIT "-Wall -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(operatordb)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS On)
enable_testing()

add_subdirectory(algo)

add_executable(operatordb src/main.cpp src/operator.cpp src/tui/application.cpp
               src/tui/table.cpp src/tui/forms.cpp src/validators.cpp)
target_link_libraries(operatordb algo::algo)
add_executable(tests tests/test.cpp)
target_link_libraries(tests gtest gmock pthread algo::algo)
