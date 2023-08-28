#ifndef MNE_GAMEBOY_H
#define MNE_GAMEBOY_H

#include <minemu.h>
#include <Emulation/GB_Emulation.h>
#include <Emulation/GB_SystemContext.h>

//App implementation
Emulation GameBoyEmulator = 
{
    .Initialize = GB_Initialize,
    .LoadProgram = GB_LoadProgram,
    .QuitProgram = GB_QuitProgram,
    .TickEmulation = GB_TickEmulation,
    .TickTimers = GB_TickTimers,
    .SetEmulationContext = GB_SetEmulationContext
};

#endif 