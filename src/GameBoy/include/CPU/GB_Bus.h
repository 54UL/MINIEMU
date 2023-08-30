#ifndef GB_BUS_H
#define GB_BUS_H
#include <Emulation/GB_SystemContext.h>

// static void GB_SetMemoryContext(uint8_t * memory);
uint8_t GB_BusRead(SystemContext *ctx, uint16_t address);
void GB_BusWrite(SystemContext *ctx, uint16_t address, uint8_t value);
void GB_SetReg8(SystemContext *ctx, uint8_t r, uint8_t value);
uint8_t GB_GetReg8(SystemContext *ctx, uint8_t r);

#endif