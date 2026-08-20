# CompilerConfig.cmake - Sets up compiler-specific flags and definitions

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

if(WIN32)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-p=${CMAKE_BINARY_DIR}")
    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    endif()

    # Windows-only definitions
    add_definitions(-DNOMINMAX)
    if(MSVC)
        add_definitions("DELETE=")
    else()
        add_definitions(-UDELETE)
    endif()
endif()

# # Linux: General clang-tidy settings
if(UNIX)
    # set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-extra-arg=-I/usr/include/c++/11;-extra-arg=-I/usr/include/x86_64-linux-gnu/c++/11;-p=${CMAKE_BINARY_DIR}")
endif()
