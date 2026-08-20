cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Utils)

# Include directories for the library
file(GLOB_RECURSE INCLUDE_DIRS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Create the game engine library
add_library(utils STATIC ${SOURCE_FILES})

if(WIN32)
    target_compile_definitions(utils PRIVATE NOMINMAX)
    if(MSVC)
        target_compile_definitions(utils PRIVATE "DELETE=")
    else()
        target_compile_options(utils PRIVATE -UDELETE)
    endif()
endif()

# Include directories for the library
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add debug flag if on debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(utils PRIVATE -g)
endif()

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
