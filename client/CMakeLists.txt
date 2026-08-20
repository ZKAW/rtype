cmake_minimum_required(VERSION 3.15)

set(FREETYPE_INCLUDE_DIRS /usr/include/freetype2)
set(FREETYPE_LIBRARIES /usr/lib/x86_64-linux-gnu/libfreetype.so)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Client)

# Find packages using vcpkg
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
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
add_executable(client ${SOURCE_FILES})

# Link the libraries
target_link_libraries(client PRIVATE
    network game_engine
    unofficial::enet::enet
)

target_link_libraries(client PRIVATE
    flatbuffers::flatbuffers
)


target_link_libraries(client PRIVATE
    lz4::lz4
)

target_link_libraries(client
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
) # Link SDL2 and SDL2_image

# Add debug flag if on debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(client PRIVATE -g)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
