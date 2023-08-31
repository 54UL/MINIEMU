#ifndef GB_BUS_H
#define GB_BUS_H
#include <Emulation/GB_SystemContext.h>


uint8_t GB_BusRead(SystemContext *ctx, uint16_t address);
void    GB_BusWrite(SystemContext *ctx, uint16_t address, uint8_t value);

void    GB_SetReg8(SystemContext *ctx, uint8_t r, uint8_t value);
uint8_t GB_GetReg8(SystemContext *ctx, uint8_t r);

void     GB_SetReg16(SystemContext *ctx, uint8_t r, uint16_t value);
uint16_t GB_GetReg16(SystemContext *ctx, uint8_t r);

#endif