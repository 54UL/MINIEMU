#ifndef GB_BUS_H
#define GB_BUS_H

typedef enum {Start, Stop, Reset, Quit} ShellAction;

uint8_t GB_BusRead(uint16_t * memory, uint16_t address)
{
    //based on address value fetch the mapped memory
    return 0xFF;
}

void GB_BusWrite(uint16_t * memory,uint16_t address,uint8_t value)
{

}

#endif