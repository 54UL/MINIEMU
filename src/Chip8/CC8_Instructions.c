#include "CC8_Instructions.h"

void CC8_CLS()
{
    for (uint16_t i = 0; i < sizeof(ctx->VRAM); i++)
    {
        ctx->VRAM[i] = 0x00;
    }
}

void CC8_RET()
{
    ctx->PC = ctx->STACK[ctx->SP];
    ctx->SP--;
}

void CC8_JMP(InstructionContext * ctx)
{
    ctx->PC = ctx->nnn - 2;
}

void CC8_CALL(InstructionContext * ctx)
{
    ctx->STACK[++ctx->SP] = ctx->PC;
    ctx->PC = ctx->nnn - 2;
}

void CC8_SE_VX_BYTE(InstructionContext * ctx)
{
    ctx->PC += ctx->V[ctx->x] == ctx->kk ? 2 : 0;
}

void CC8_SNE_VX_BYTE(InstructionContext * ctx)
{
    ctx->PC += ctx->V[ctx->x] != ctx->kk ? 2 : 0;
}

void CC8_SE_VX_VY(InstructionContext * ctx)
{
    ctx->PC += ctx->V[ctx->x] == ctx->V[ctx->y] ? 2 : 0;
}

void CC8_LD_VX_BYTE(InstructionContext * ctx)
{
    ctx->V[ctx->x] = ctx->kk;
}

void CC8_ADD_VX_BYTE(InstructionContext * ctx)
{
    ctx->V[ctx->x] = (ctx->V[ctx->x] + ctx->kk) & 0xFF;
}

void CC8_LD_VX_VY(InstructionContext * ctx)
{
    ctx->V[ctx->x] = ctx->V[ctx->y];
}

void CC8_OR_VX_VY(InstructionContext * ctx)
{
    ctx->V[ctx->x] |= ctx->V[ctx->y];
}

void CC8_AND_VX_VY(InstructionContext * ctx)
{
    ctx->V[ctx->x] &= ctx->V[ctx->y];
}

void CC8_XOR_VX_VY(InstructionContext * ctx)
{
    ctx->V[ctx->x] ^= ctx->V[ctx->y];
}

void CC8_ADD_VX_VY(InstructionContext * ctx)
{
    uint16_t sum = ctx->V[ctx->x] + ctx->V[ctx->y];
    ctx->V[0X0F] = sum > 0xFF; // carry flag
    ctx->V[ctx->x] = sum & 0xFF;
}

void CC8_SUB_VX_VY(InstructionContext * ctx)
{
    ctx->V[0x0F] = ctx->V[ctx->x] > ctx->V[ctx->y];
    ctx->V[ctx->x] -= ctx->V[ctx->y];
}

void CC8_SHR_VX_VY(InstructionContext * ctx)
{
    ctx->V[0x0F] = ctx->V[ctx->x] & 0x01;
    ctx->V[ctx->x] >>= 1;
}

void CC8_SUBN_VX_VY(InstructionContext * ctx)
{
    ctx->V[0x0F] = ctx->V[ctx->y] > ctx->V[ctx->x];
    ctx->V[ctx->x] = ctx->V[ctx->y] - ctx->V[ctx->x];
}

void CC8_SHL_VX_VY(InstructionContext * ctx)
{
    ctx->V[0x0F] = (ctx->V[ctx->x] & 0x80) >> 7;
    ctx->V[ctx->x] <<= 1;
}

void CC8_SNE_VX_VY(InstructionContext * ctx)
{
    ctx->PC += ctx->V[ctx->x] != ctx->V[ctx->y] ? 2 : 0;
}

void CC8_LD_I_ADDR(InstructionContext * ctx)
{
    ctx->I = ctx->nnn & 0xfff;
}

void CC8_JP_V0_ADDR(InstructionContext * ctx)
{
    ctx->PC = ctx->nnn + ctx->V[0];
}

void CC8_RND_VX_BYTE(InstructionContext * ctx)
{
    ctx->V[ctx->x] = (rand() % 0xFF) & ctx->kk;
}

void CC8_DRW_VX_VY_NIBBLE(InstructionContext * ctx)
{
    const uint16_t startAddress = ctx->I;
    ctx->V[0x0F] = 0;

    for (uint8_t byte = 0; byte < n; byte++)
    {
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            uint8_t line = ctx->RAM[startAddress + byte];

            if ((line & (0x80 >> bit)) != 0)
            {
                uint8_t xPos = (ctx->V[ctx->x] + bit) % (CHIP_8_VRAM_WIDTH);
                uint8_t yPos = (ctx->V[ctx->y] + byte) % CHIP_8_VRAM_HEIGHT;
                uint16_t vramIndex = (yPos * CHIP_8_VRAM_WIDTH) + (xPos / 8);
                uint8_t vramBit = (xPos % 8);

                if ((ctx->VRAM[vramIndex] & (1 << vramBit)) != 0)
                {
                    ctx->V[0x0F] = 1;
                }

                ctx->VRAM[vramIndex] ^= (1 << vramBit);
            }
        }
    }
}

void CC8_SKP_VX(InstructionContext * ctx)
{
    ctx->PC += ctx->V[ctx->x] == ctx->KEYBOARD ? 2 : 0;
}

void CC8_SKNP_VX(InstructionContext * ctx)
{
    ctx->PC += ctx->V[ctx->x] != ctx->KEYBOARD ? 2 : 0;
}

void CC8_LD_VX_DT(InstructionContext * ctx)
{
    ctx->V[ctx->x] = ctx->DELAY;
}

void CC8_LD_VX_K(InstructionContext * ctx)
{
    while (ctx->KEYBOARD == 0);
    ctx->V[ctx->x] = ctx->KEYBOARD;
}

void CC8_LD_DT_VX(InstructionContext * ctx)
{
    ctx->DELAY = ctx->V[ctx->x];
}

void CC8_LD_ST_VX(InstructionContext * ctx)
{
    ctx->SOUND = ctx->V[ctx->x];
}

void CC8_ADD_I_VX(InstructionContext * ctx)
{
    ctx->I = (ctx->I + ctx->V[ctx->x]) & 0xFFFF;
}

void CC8_LD_F_VX(InstructionContext * ctx)
{
    ctx->I = ctx->V[ctx->x] * 5;
}

void CC8_LD_B_VX(InstructionContext * ctx)
{
    const uint8_t rawValue = ctx->V[ctx->x];

    const uint8_t hundreds = rawValue / 100;
    const uint8_t tens = (rawValue / 10) % 10;
    const uint8_t units = rawValue % 10;

    const uint16_t currentAddress = ctx->I;

    ctx->RAM[currentAddress] = hundreds;
    ctx->RAM[currentAddress + 1] = tens;
    ctx->RAM[currentAddress + 2] = units;
}

void CC8_LD_I_VX(InstructionContext * ctx)
{
    const uint16_t startAddress = ctx->I;
    const uint16_t endAddress = startAddress + ctx->x;

    for (uint16_t ramIndex = startAddress, vIndex = 0; ramIndex <= endAddress; ramIndex++, vIndex++)
    {
        ctx->RAM[ramIndex] = ctx->V[vIndex];
    }
}

void CC8_LD_VX_I(InstructionContext * ctx)
{
    const uint16_t startAddress = ctx->I;
    const uint16_t endAddress = startAddress + ctx->x;

    for (uint16_t ramIndex = startAddress, vIndex = 0; ramIndex <= endAddress; ramIndex++, vIndex++)
    {
        ctx->V[vIndex] = ctx->RAM[ramIndex];
    }
}

