cmake_minimum_required(VERSION 3.10)

# Set the project name
project(thread_ws VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add executable targets
add_executable(thread_ws_prod_cons          ${SOURCE_DIR}/prod_cons.cpp)
add_executable(thread_ws_prod_cons_future   ${SOURCE_DIR}/prod_cons_future.cpp)

# Add flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)