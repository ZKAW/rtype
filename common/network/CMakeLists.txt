cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Network)

find_package(unofficial-enet CONFIG REQUIRED)

# Include directories for the library
file(GLOB_RECURSE INCLUDE_DIRS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Create the game engine library
add_library(network STATIC ${SOURCE_FILES})

if(WIN32)
    target_compile_definitions(network PRIVATE NOMINMAX)
    if(MSVC)
        target_compile_definitions(network PRIVATE "DELETE=")
    else()
        target_compile_options(network PRIVATE -UDELETE)
    endif()
endif()

# Link the game engine library with the required libraries
target_link_libraries(network PRIVATE game_engine utils
    unofficial::enet::enet)

# Include directories for the library
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include directories for generated FlatBuffers headers
file(GLOB_RECURSE FLATBUFFERS_HEADERS "${CMAKE_BINARY_DIR}/packets/compiled_packets/*.h")
target_include_directories(network PUBLIC ${CMAKE_BINARY_DIR}/packets/compiled_packets)

# Add debug flag if on debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(network PRIVATE -g)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
