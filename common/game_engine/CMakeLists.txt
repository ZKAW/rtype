cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(GameEngine)

find_package(unofficial-enet CONFIG REQUIRED)

# Include directories for the library
file(GLOB_RECURSE INCLUDE_DIRS "src/*.hpp" "src/*.h" "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Create the game engine library
add_library(game_engine STATIC ${SOURCE_FILES})

if(WIN32)
    target_compile_definitions(game_engine PRIVATE NOMINMAX)
    # Undefine DELETE for MSVC or MinGW compilers
    if(MSVC)
        target_compile_definitions(game_engine PRIVATE "DELETE=")
    else()
        target_compile_options(game_engine PRIVATE -UDELETE)
    endif()
endif()


# Link the library with the required libraries
target_link_libraries(game_engine PRIVATE network
    unofficial::enet::enet)

# Include directories for the library
target_include_directories(game_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(game_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include directories for generated FlatBuffers headers
file(GLOB_RECURSE FLATBUFFERS_HEADERS "${CMAKE_BINARY_DIR}/packets/compiled_packets/*.h")
target_include_directories(network PUBLIC ${CMAKE_BINARY_DIR}/packets/compiled_packets)

# Add debug flag if on debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(game_engine PRIVATE -g)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
