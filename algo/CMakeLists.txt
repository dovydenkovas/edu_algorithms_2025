cmake_minimum_required(VERSION 3.21)

project(algo
  VERSION 1.0.0
  DESCRIPTION "Basic data structures"
  LANGUAGES CXX
)

# Объявление библиотеки для добавления в проекты
add_library(algo)
add_library(algo::algo ALIAS algo)

# include(cmake/utils.cmake)
include(GNUInstallDirs)

# Опции сборки
option(ALGO_BUILD_TESTS "Build algo tests" OFF)
option(ALGO_INSTALL "Generate target for installing algo" ${PROJECT_IS_TOP_LEVEL})


set(public_headers
  include/algo/vector.hpp
  include/algo/list.hpp
  include/algo/map.hpp
  include/algo/hash.h
  include/algo/hashmap.hpp
)

set(sources
  ${public_headers}
  src/hash.cpp
  src/search.cpp
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

include(CMakePackageConfigHelpers)

target_sources(algo PRIVATE ${sources})

target_include_directories(algo
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(algo PROPERTIES
    PUBLIC_HEADER "${public_headers}"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if (ALGO_BUILD_TESTS OR ALGO_INSTALL)
  enable_testing()
  add_executable(tests tests/test.cpp)
  target_link_libraries(tests gtest gmock pthread algo::algo)
endif()
