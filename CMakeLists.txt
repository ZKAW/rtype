cmake_minimum_required(VERSION 3.15)
project(RTypeGame)

# Required for flatbuffers to work on Windows
if (WIN32 AND NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set up C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compile commands and suppress regeneration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SUPPRESS_REGENERATION ON)

# Load CMake modules
include(cmake/CompilerConfig.cmake)
include(cmake/Dependencies.cmake)
include(cmake/VCPKGSetup.cmake)
include(cmake/FlatbuffersSetup.cmake)

# Add directories for common, client, and server
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
