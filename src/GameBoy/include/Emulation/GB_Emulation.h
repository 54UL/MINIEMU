#ifndef GB_EMULATION_H
#define GB_EMULATION_H

#include <Emulation/GB_SystemContext.h>
#include <stdint.h>
#include <stdlib.h>
#define GB_INVALID_INSTRUCTION 0xAEAE

long    GB_LoadProgram(const char *filePath);
void    GB_QuitProgram();
void    GB_TickTimers();
int     GB_TickEmulation();
void    GB_SetEmulationContext(const void *context);
void    GB_PopulateMemory(const uint8_t *buffer, size_t bytesRead);

#endif