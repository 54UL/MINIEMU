cmake_minimum_required(VERSION 3.1)
message("Configuring MINEMU Core")
project(Core C)
set(CMAKE_C_COMPILER "gcc")

# List all the source files of the Core library
set(CORE_SOURCES
    include/minemu.h
    include/minemu.c
    include/3rd/khash.h
)

# Create the Core static library
add_library(Core STATIC ${CORE_SOURCES})

# Include directories for Core
target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)