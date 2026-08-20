# Dependencies.cmake - Handles vcpkg setup and dependency installation

# Enable vcpkg manifest mode
set(VCPKG_ENABLE_MANIFEST TRUE CACHE BOOL "Enable vcpkg manifest")

# Define vcpkg directory
set(VCPKG_DIR "${CMAKE_BINARY_DIR}/vcpkg")

# Clone vcpkg if not present
if(NOT EXISTS ${VCPKG_DIR})
    message(STATUS "Cloning vcpkg...")
    execute_process(
        COMMAND git clone https://github.com/microsoft/vcpkg.git ${VCPKG_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

# Bootstrap vcpkg
if(NOT EXISTS ${VCPKG_DIR}/vcpkg)
    if(UNIX)
        execute_process(COMMAND ${VCPKG_DIR}/bootstrap-vcpkg.sh -disableMetrics WORKING_DIRECTORY ${VCPKG_DIR})
    elseif(WIN32)
        execute_process(COMMAND ${VCPKG_DIR}/bootstrap-vcpkg.bat -disableMetrics WORKING_DIRECTORY ${VCPKG_DIR})
    endif()
endif()

# Install dependencies from vcpkg.json
message(STATUS "Installing dependencies from vcpkg.json...")
file(COPY ${CMAKE_SOURCE_DIR}/vcpkg.json DESTINATION ${CMAKE_BINARY_DIR})
execute_process(COMMAND ${VCPKG_DIR}/vcpkg install WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Set vcpkg toolchain file and prefix path based on platform
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

if(WIN32)
    set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/share" CACHE STRING "")
    set(ZLIB_INCLUDE_DIR "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include")
    set(ZLIB_LIBRARY "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/lib/zlib.lib")
    set(PNG_PNG_INCLUDE_DIR "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/include")
    set(PNG_LIBRARY "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/lib/libpng16.lib")

    # Copy DLLs from vcpkg to client and server directories
    file(GLOB VCPKG_DLLS "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/bin/*.dll")
    foreach(DLL ${VCPKG_DLLS})
        file(COPY ${DLL} DESTINATION ${CMAKE_BINARY_DIR}/client)
        file(COPY ${DLL} DESTINATION ${CMAKE_BINARY_DIR}/server)
    endforeach()

    # Add vcpkg bin directory to PATH
    # set(ENV{PATH} ${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/bin;$ENV{PATH})
    # Append vcpkg bin directory to PATH, ensuring proper handling of existing values
    set(VCPKG_BIN_DIR "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-windows/bin")
    if(DEFINED ENV{PATH})
        set(ENV{PATH} "${VCPKG_BIN_DIR};$ENV{PATH}")
    else()
        set(ENV{PATH} "${VCPKG_BIN_DIR}")
    endif()
else()
    set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg_installed/x64-linux/share" CACHE STRING "")
endif()
