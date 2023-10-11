#ifndef CC8_EMULATOR_H
#define CC8_EMULATOR_H
#include "CC8_InstructionContext.h"

typedef void (*instructionFnPtr)(const InstructionContext * ctx);

EmulationInfo CC8_GetInfo();
long          CC8_LoadProgram(const char *filePath);
void          CC8_QuitProgram();
void          CC8_TickDelayTimer();
int           CC8_TickEmulation();
void          CC8_SetKeyboardValue(uint8_t key);
void          CC8_SetEmulationContext(const void *context);
void          CC8_PopulateMemory(const uint8_t *buffer, size_t bytesRead);
void          CC8_OnInput(const char code);
void          CC8_OnRender(uint32_t* pixels, const int64_t w, const int64_t h);
void          CC8_Loop(uint32_t currentTime, uint32_t deltaTime);

#endif