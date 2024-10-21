cmake_minimum_required(VERSION 3.10)

# Set the project name
project(meta_ws VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set include directory
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add include directories
include_directories(${INCLUDE_DIR})

# Add executable targets
add_executable(meta_ws ${SOURCE_DIR}/main.cpp)

# Add flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)