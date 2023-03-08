cmake_minimum_required(VERSION 3.8)

project(asio_ws)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(ROOT_DIR ${PROJECT_SOURCE_DIR})
set(SRC_ROOT_DIR ${ROOT_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(asio_ws ${SRC_ROOT_DIR}/multithread_asio.cpp)