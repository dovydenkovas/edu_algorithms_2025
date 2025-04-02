add_library(algo
  vector.hpp
)

target_include_directories(algo
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(algo PROPERTIES LINKER_LANGUAGE CXX)
