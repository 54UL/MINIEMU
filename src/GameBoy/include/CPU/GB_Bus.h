#ifndef GB_BUS_H
#define GB_BUS_H
#include <Emulation/GB_SystemContext.h>

typedef enum {Start, Stop, Reset, Quit} ShellAction;

uint8_t GB_BusRead(SystemContext *ctx, uint16_t address)
{
    //based on address value fetch the mapped memory
    return 0xFF;
}

void GB_BusWrite(SystemContext *ctx, uint16_t address, uint8_t value)
{

}

#endif