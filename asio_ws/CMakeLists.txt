cmake_minimum_required(VERSION 3.10)

# Set the project name
project(asio_ws VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add executable targets
add_executable(asio_ws_async_timer          ${SOURCE_DIR}/async_timer.cpp)
add_executable(asio_ws_bind_timer           ${SOURCE_DIR}/bind_timer.cpp)
add_executable(asio_ws_completion_handler   ${SOURCE_DIR}/completion_handler.cpp)
add_executable(asio_ws_multithread_asio     ${SOURCE_DIR}/multithread_asio.cpp)

# Add flags
add_compile_options(-Wall -Wextra -Wpedantic -Werror)