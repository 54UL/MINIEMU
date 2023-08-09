#ifndef CC8_EMULATOR_H
#define CC8_EMULATOR_H
#include "CC8_InstructionContext.h"

typedef void (*instructionFnPtr)(const InstructionContext * ctx);

long    CC8_LoadProgram(const char *filePath);
void    CC8_QuitProgram();
void    CC8_TickDelayTimer();
int     CC8_TickEmulation();
void    CC8_SetKeyboardValue(uint8_t key);
void    CC8_SetEmulationContext(const void *context);
void    CC8_PopulateMemory(const uint8_t *buffer, size_t bytesRead);

#endif