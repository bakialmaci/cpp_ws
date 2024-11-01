# Minimum CMake version required to build the project
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(web2os VERSION 1.0)

# Set C++ standard to C++17 and require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output the project name and version
message(STATUS "Project: ${PROJECT_NAME}, Version: ${PROJECT_VERSION}")

# Aliases for directories to keep the CMakeLists.txt clean
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# Add include directories
include_directories(
    ${INCLUDE_DIR}
    ${EXTERNAL_DIR}/json/include
    ${EXTERNAL_DIR}/httplib
)

# Specify the source files for the project
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/server/server.cpp
    ${SRC_DIR}/server/router.cpp
    ${SRC_DIR}/database/database.cpp
)

# Create the executable with the specified sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Find and link the SQLite3 library
find_package(SQLite3 REQUIRED)
target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)

# Add custom compiler warnings for better code quality (optional, but recommended)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
endif()

# Set properties for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Display a message indicating successful configuration
message(STATUS "Configuration complete. Ready to build ${PROJECT_NAME}.")
