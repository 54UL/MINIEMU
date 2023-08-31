#include <CPU/GB_Bus.h>

uint8_t GB_BusRead(SystemContext *ctx, uint16_t address)
{
    //TODO: IMPLEMENT HARDWARE REGISTER HASH LIST TO CHECK ACCESS POLICY (R, R/W,TRIGGER ON W, ETC)
    //TODO: MEMORY ACCESS SHOULD NOT BE MULTI THREADED...

    return 0xFF;
}

void GB_BusWrite(SystemContext *ctx, uint16_t address, uint8_t value)
{

}

void GB_SetReg8(SystemContext *ctx, uint8_t r, uint8_t value)
{
    uint8_t *halfregs = ((uint8_t *)ctx->registers->CPU);

#ifdef GB_DEBUG
    MNE_Log("GB_SetReg8(R:%04X,V:%04X)", r, value);
#endif

    if (r == GB_HL_R_INDIRECT_OFFSET) //idk if this has to be 0x06 or 0x07??
    {
        return GB_BusWrite(ctx, ctx->registers->CPU[GB_HL_OFFSET], value);
    }

    halfregs[r] = value;
}

uint8_t GB_GetReg8(SystemContext *ctx, uint8_t r)
{
    const uint8_t *halfregs = ((uint8_t *)ctx->registers->CPU);
    
#ifdef GB_DEBUG
    MNE_Log("GB_GetReg8(R:%04X):%0X4", r, halfregs[r]);
#endif

    if (r == GB_HL_R_INDIRECT_OFFSET) //idk if this has to be 0x06 or 0x07??
    {
        return GB_BusRead(ctx, ctx->registers->CPU[GB_HL_OFFSET]);
    }

    return halfregs[r];
}



void GB_SetReg16(SystemContext *ctx, uint8_t r, uint16_t value)
{

}

uint16_t GB_GetReg16(SystemContext *ctx, uint8_t r){

}