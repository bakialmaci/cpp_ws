cmake_minimum_required(VERSION 3.10)

# Set the project name
project(union_ws VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add executable targets
add_executable(union_ws_basic                   ${SOURCE_DIR}/union_basic.cpp)
add_executable(union_ws_safe_holds_alternative  ${SOURCE_DIR}/union_safe_holds_alternative.cpp)
add_executable(union_ws_safe_visit              ${SOURCE_DIR}/union_safe_visit.cpp)

# Add flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)