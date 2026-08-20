cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Server)

# Find packages using vcpkg
find_package(unofficial-enet CONFIG REQUIRED)
find_package(flatbuffers CONFIG REQUIRED)
find_package(lz4 CONFIG REQUIRED)

# Include directories
file(GLOB_RECURSE INCLUDE_DIRS "src/*.hpp" "src/*.h" "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "libs/*.cpp")

foreach(INCLUDE_DIR ${INCLUDE_DIRS})
    get_filename_component(DIR ${INCLUDE_DIR} DIRECTORY)
    include_directories(${DIR})
endforeach()

# Add the executable
add_executable(server ${SOURCE_FILES})

# Link the libraries
target_link_libraries(server PRIVATE
    network game_engine utils
    unofficial::enet::enet
)

target_link_libraries(server PRIVATE
    flatbuffers::flatbuffers
)

target_link_libraries(server PRIVATE
    lz4::lz4
)

# Add debug flag if on debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(server PRIVATE -g)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
