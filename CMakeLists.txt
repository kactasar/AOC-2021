cmake_minimum_required(VERSION 3.10)
project(aoc2021 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All executables go into build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Collect all puzzle source files automatically
file(GLOB DAY_SOURCES "${CMAKE_SOURCE_DIR}/src/day*.cpp")

# Iterate over each puzzle source file
foreach(DAY_SOURCE ${DAY_SOURCES})
    # Extract just the filename without extension, e.g., "day01"
    get_filename_component(DAY_NAME ${DAY_SOURCE} NAME_WE)

    # Define the executable and link shared utilities
    add_executable(${DAY_NAME}
        ${DAY_SOURCE}
        "${CMAKE_SOURCE_DIR}/src/utils.cpp"
    )

    # Define the input and output data file paths
    set(INPUT_FILE "${CMAKE_SOURCE_DIR}/data/${DAY_NAME}_input.txt")
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/data")

    # Create bin/data directory if it doesn't exist
    file(MAKE_DIRECTORY "${OUTPUT_DIR}")

    # If the input file exists, copy it to bin/data after build
    if(EXISTS "${INPUT_FILE}")
        add_custom_command(
            TARGET ${DAY_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${INPUT_FILE}"
                    "${OUTPUT_DIR}/"
            COMMENT "Copying ${DAY_NAME}_input.txt to bin/data/"
        )
    else()
        message(WARNING "Input file not found for ${DAY_NAME}: ${INPUT_FILE}")
    endif()
endforeach()