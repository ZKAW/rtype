# FlatbuffersSetup.cmake - Manages FlatBuffers setup

# Define FlatBuffers directories
set(FLATBUFFERS_DIR "${CMAKE_SOURCE_DIR}/packets")
set(FLATBUFFERS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/packets/compiled_packets")

# Platform-specific flatc URL and binary path
if(WIN32)
    set(FLATC_BINARY "flatc.exe")
    set(FLATC_URL "https://github.com/google/flatbuffers/releases/download/v24.3.25/Windows.flatc.binary.zip")
else()
    set(FLATC_BINARY "flatc")
    set(FLATC_URL "https://github.com/google/flatbuffers/releases/download/v24.3.25/Linux.flatc.binary.g++-13.zip")
endif()

# Check for flatc and download if not found
if(NOT EXISTS "${CMAKE_BINARY_DIR}/flatc_temp/${FLATC_BINARY}")
    message(STATUS "Downloading flatc from ${FLATC_URL}...")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/flatc_temp")
    file(DOWNLOAD ${FLATC_URL} "${CMAKE_BINARY_DIR}/flatc_temp/flatc.zip")

    # Extract flatc binary
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E tar xf "${CMAKE_BINARY_DIR}/flatc_temp/flatc.zip"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/flatc_temp"
    )
endif()

# Generate FlatBuffers files
file(GLOB FLATBUFFERS_FILES "${FLATBUFFERS_DIR}/*.fbs")
file(MAKE_DIRECTORY "${FLATBUFFERS_OUTPUT_DIR}")
foreach(FBS_FILE ${FLATBUFFERS_FILES})
    get_filename_component(FBS_NAME ${FBS_FILE} NAME_WE)
    add_custom_command(
        OUTPUT "${FLATBUFFERS_OUTPUT_DIR}/${FBS_NAME}_generated.h"
        COMMAND ${CMAKE_BINARY_DIR}/flatc_temp/${FLATC_BINARY} --cpp -o "${FLATBUFFERS_OUTPUT_DIR}" "${FBS_FILE}"
        DEPENDS "${FBS_FILE}"
        COMMENT "Generating FlatBuffer files from ${FBS_FILE}"
    )
    list(APPEND FLATBUFFERS_GENERATED_FILES "${FLATBUFFERS_OUTPUT_DIR}/${FBS_NAME}_generated.h")
endforeach()

# Add FlatBuffers target
add_custom_target(Flatbuffers ALL DEPENDS ${FLATBUFFERS_GENERATED_FILES})
include_directories("${FLATBUFFERS_OUTPUT_DIR}")
