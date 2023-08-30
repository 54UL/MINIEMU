
#include <CPU/GB_Bus.h>

static uint8_t * s_memory;

static void GB_SetMemoryContext(uint8_t * memory)
{
    s_memory = memory;
}

uint8_t GB_BusRead(SystemContext *ctx, uint16_t address)
{
    // based on address value fetch the mapped memory
    return 0xFF;
}

void GB_BusWrite(SystemContext *ctx, uint16_t address, uint8_t value)
{
}

void GB_SetReg8(SystemContext *ctx, uint8_t r, uint8_t value)
{
#ifdef GB_DEBUG
    MNE_Log("GB_SetReg8(R:%04X,V:%04X)", r, value);
#endif

    uint8_t *halfregs = ((uint8_t *)ctx->registers->CPU);

    if (r == GB_HL_INSTR) //idk if this has to be 0x06 or 0x07??
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
    return halfregs[r];
}
