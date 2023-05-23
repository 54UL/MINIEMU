cmake_minimum_required(VERSION 3.1)


project(CC8 C)
set(CMAKE_C_COMPILER "gcc")

file(GLOB_RECURSE CC8_ENTRY_POINT "main.c")

# Find SDL2 library
find_package(SDL2 REQUIRED)

# Add all .h and .c files to the project
file(GLOB SOURCES "*.h" "*.c")

# uDisplay library sources
file(GLOB_RECURSE CC8_SOURCE "src/*.c")
file(GLOB_RECURSE CC8_HEADERS "src/*.h")

message(${CC8_SOURCE})
message("headers")
message(${CC8_HEADERS})

# Add the source files to the project
add_executable(CC8 ${CC8_HEADERS} ${CC8_SOURCE} ${CC8_ENTRY_POINT})

# Create executable
target_compile_options(CC8 PUBLIC -std=c11 -Wall -Wextra)

# Link with SDL2 library
target_link_libraries(CC8 SDL2)