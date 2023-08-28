#ifndef CC8_API_H
#define CC8_API_H
#include <stdio.h>
#include <CC8_Emulator.h>

//App implementation
Emulation Chip8Emulator = 
{
    .LoadProgram = CC8_LoadProgram,
    .QuitProgram = CC8_QuitProgram,
    .TickEmulation = CC8_TickEmulation,
    .TickTimers = CC8_TickDelayTimer,
    .SetEmulationContext = CC8_SetEmulationContext
};

#endif