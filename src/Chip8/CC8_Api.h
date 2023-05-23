#ifndef CC8_API_H
#define CC8_API_H
#include <stdio.h>


#include "CC8_Machine.h"
#include "CC8_Emulator.h"

typedef struct 
{
    void            (*LoadProgram)(const char * filePath);
    void            (*QuitProgram)();
    void            (*TickEmulation)();
    void            (*SetEmulationContext)(CC8_Machine * context);
} CC8_Core;

//App implementation
CC8_Core Chip8Emulator = 
{
    .LoadProgram = CC8_LoadProgram,
    .QuitProgram = CC8_QuitProgram,
    .TickEmulation = CC8_TickEmulation,
    .SetEmulationContext = CC8_SetEmulationContext
};

#endif