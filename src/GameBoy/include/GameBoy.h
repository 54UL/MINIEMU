#ifndef MNE_GAMEBOY_H
#define MNE_GAMEBOY_H
#include <minemu.h>
#include <Emulation/GB_Emulation.h>

//App implementation
Emulation GameBoyEmulator = 
{
    .LoadProgram = GB_LoadProgram,
    .QuitProgram = GB_QuitProgram,
    .TickEmulation = GB_TickEmulation,
    .TickDelayTimer = GB_TickTimers,
    .SetEmulationContext = GB_SetEmulationContext
};

#endif 