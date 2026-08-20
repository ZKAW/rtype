if (WIN32)
    # Force the use of Ninja on Windows
    find_program(NINJA_EXECUTABLE NAMES ninja)

    if (NOT NINJA_EXECUTABLE)
        message(FATAL_ERROR "Ninja build system is required but not found.\nPlease install Ninja from https://github.com/ninja-build/ninja/releases")
    else()
        set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)
    endif()
endif()
