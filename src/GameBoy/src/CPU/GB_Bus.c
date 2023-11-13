#include <CPU/GB_Bus.h>


/* GB_Bus.c TODOS
- IMPLEMENT HARDWARE REGISTER HASH LIST TO CHECK ACCESS POLICY (R, R/W,TRIGGER ON W, ETC)
- MEMORY ACCESS SHOULD NOT BE MULTI THREADED...
 
*/

uint8_t GB_BusRead(EmulationState *ctx, uint16_t address)
{
    return 0;
}

void GB_BusWrite(EmulationState *ctx, uint16_t address, uint8_t value)
{
}

// Normal register file accesing functions (indexed as B,E,D,E,H,L,A,F)
void GB_SetReg8(EmulationState *ctx, uint8_t r, uint8_t value, uint8_t mode)
{
    uint8_t *halfregs = ((uint8_t *)ctx->registers->CPU);

#ifdef GB_DEBUG
    MNE_Log("GB_SetReg8(R:%04X,V:%04X)", r, value);
#endif

    if (mode && r == GB_HL_R_INDIRECT_OFFSET)
    {
        GB_BusWrite(ctx, ctx->registers->CPU[GB_HL_OFFSET], value);
        return;
    }

    halfregs[r] = value;
}

uint8_t GB_GetReg8(EmulationState *ctx, uint8_t r, uint8_t mode)
{
    const uint8_t *halfregs = ((uint8_t *)ctx->registers->CPU);

#ifdef GB_DEBUG
    MNE_Log("GB_GetReg8(R:%04X):%0X4", r, halfregs[r]);
#endif

    if (mode && r == GB_HL_R_INDIRECT_OFFSET)
    {
        return GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
    }

    return halfregs[r];
}

void GB_SetReg16(EmulationState *ctx, uint8_t r, uint16_t value, uint8_t mode)
{

}

uint16_t GB_GetReg16(EmulationState *ctx, uint8_t r, uint8_t mode)
{

}