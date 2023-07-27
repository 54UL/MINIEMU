#ifndef CC8_EMULATOR_H
#define CC8_EMULATOR_H
#include "CC8_InstructionContext.h"

typedef void (*instructionFnPtr)(const InstructionContext * ctx);

void    CC8_BuildInstructionsLUT();
uint8_t CC8_LoadProgram(const char *filePath);
void    CC8_QuitProgram();
void    CC8_TickDelayTimer();
int     CC8_TickEmulation();
void    CC8_SetKeyboardValue(uint8_t key);
void    CC8_SetEmulationContext(const void *context);

#endif