#include <CPU/GB_Registers.h>

void setReg8(GB_Registers *registers, uint8_t rr, uint8_t value)
{
    registers->CPU[rr] = value;
}

uint8_t getReg8(const GB_Registers * registers, uint8_t rr)
{
    return registers->CPU[rr];
}
