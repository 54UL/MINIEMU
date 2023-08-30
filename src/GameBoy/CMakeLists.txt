project(GameBoy C)
# set(CMAKE_C_COMPILER "gcc")
message("Configuring MINEMU GameBoy")


# List all the source files of the GameBoy library
set(GB_HEADERS
    include/GameBoy.h
    include/CPU/GB_Bus.h
    include/CPU/GB_Instructions.h
    include/CPU/GB_Registers.h
    include/Emulation/GB_Emulation.h
    include/Emulation/GB_Instruction.h
    include/Emulation/GB_SystemContext.h
    include/Memory/GB_MemoryMap.h
)

set(GB_SOURCES
    src/CPU/GB_Instructions.c
    src/CPU/GB_Bus.c
    src/Emulation/GB_Emulation.c
)

# Create the GameBoy_MINEMU shared library
add_library(GameBoy STATIC  ${GB_SOURCES} ${GB_HEADERS})

# Include directories for the proyect itself...
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include directories for GameBoy
target_include_directories(GameBoy PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link any necessary libraries 
target_link_libraries(GameBoy PRIVATE Core)