cmake_minimum_required(VERSION 3.10)

# Set the project name
project(variant_ws VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add executable targets
add_executable(variant_ws_polymorphism  ${SOURCE_DIR}/polymorphism.cpp)
add_executable(variant_ws_state_machine ${SOURCE_DIR}/state_machine.cpp)
add_executable(variant_ws_type_holder   ${SOURCE_DIR}/type_holder.cpp)

# Add flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)