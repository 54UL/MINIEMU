#include <CPU/GB_Registers.h>

void GB_SetReg8(GB_Registers *registers, uint8_t r, uint8_t value)
{
    uint8_t * halfregs = ((uint8_t * )registers->CPU); 
    halfregs[r] = value;
}

uint8_t GB_GetReg8(const GB_Registers * registers, uint8_t r)
{
    const uint8_t * halfregs = ((uint8_t * )registers->CPU); 
    return halfregs[r];
}
