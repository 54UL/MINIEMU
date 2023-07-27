project(Chip8 C)
set(CMAKE_C_COMPILER "gcc")
message("Configuring MINEMU Chip 8")

# List all the source files of the Chip8 library
set(CHIP8_SOURCES
    include/CC8_Chip8.h
    include/CC8_Memory.h
    include/CC8_Instructions.h
    include/CC8_InstructionContext.h
    include/CC8_Emulator.h
    src/CC8_Emulator.c
    src/CC8_Instructions.c
)
# Create the Chip8_MINEMU shared library
add_library(Chip8 STATIC ${CHIP8_SOURCES})

# Include directories for Chip8
target_include_directories(Chip8 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link any necessary libraries 
target_link_libraries(Chip8 PRIVATE Core)