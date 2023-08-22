#include <CPU/GB_Instructions.h>
#include <CPU/GB_Bus.h>
#include <CPU/GB_Registers.h>

#define xxx 0x38
#define yyy 0x07

// 8-BIT LOAD INSTRUCTIONS
void GB_LD_R_R(const SystemContext *ctx)
{
    // encoding: b01xxxyyy/various
    const uint8_t r1 = (ctx->registers->INSTRUCTION & xxx) >> 3;
    const uint8_t r2 = (ctx->registers->INSTRUCTION & yyy);

    GB_SetReg8(ctx->registers, r1, GB_GetReg8(ctx->registers, r2));
}

void GB_LD_R_N(const SystemContext *ctx)
{
    // encoding: 0b00xxx110/various + n
    const uint8_t r = (ctx->registers->INSTRUCTION & xxx) >> 3;

    ctx->registers->CPU[r] = GB_BusRead(ctx->memory, ctx->registers->PC++);
}

void GB_LD_R_HL(const SystemContext *ctx)
{
    // encoding: 0b01xxx110/various
    const uint8_t r = (ctx->registers->INSTRUCTION & xxx) >> 3;

    ctx->registers->CPU[r] = GB_BusRead(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET]);
}

void GB_LD_HL_R(const SystemContext *ctx)
{
    // encoding: 0b01110xxx
    const uint8_t r = ctx->registers->INSTRUCTION & yyy;

    GB_SetReg8(ctx->registers, r, GB_BusRead(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET]));
}

void GB_LD_HL_N(const SystemContext *ctx)
{
    // 0b00110110/0x36 + n
    /*
    opcode = read(PC++)
    if opcode == 0x36:
        n = read(PC++)
        write(HL, n)
    */
    const uint8_t n = GB_BusRead(ctx->memory, ctx->registers->PC++);

    GB_BusWrite(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET], n);
}

void GB_LD_A_BC(const SystemContext *ctx)
{
    /*
    opcode = read(PC++)
    if opcode == 0x0A:
        A = read(BC)
    */
    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx->memory, ctx->registers->CPU[GB_BC_OFFSET]);
}

void GB_LD_A_DE(const SystemContext *ctx)
{
    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx->memory, ctx->registers->CPU[GB_DE_OFFSET]);
}

void GB_LD_A_NN(const SystemContext *ctx)
{
    /*
    opcode = read(PC++)
    if opcode == 0xFA:
        nn = unsigned_16(lsb=read(PC++), msb=read(PC++))
        A = read(nn)
    */
    const uint8_t lsb = GB_BusRead(ctx->memory, ctx->registers->PC++);
    const uint8_t msb = GB_BusRead(ctx->memory, ctx->registers->PC++);
    const uint16_t nn = (uint16_t)(lsb | (msb << 8));

    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx->memory, nn);
}

void GB_LD_BC_A(const SystemContext *ctx)
{
    GB_BusWrite(ctx->memory, ctx->registers->CPU[GB_BC_OFFSET], GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

void GB_LD_DE_A(const SystemContext *ctx)
{
    GB_BusWrite(ctx->memory, ctx->registers->CPU[GB_DE_OFFSET], GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

void GB_LD_NN_A(const SystemContext *ctx)
{
    const uint8_t lsb = GB_BusRead(ctx->memory, ctx->registers->PC++);
    const uint8_t msb = GB_BusRead(ctx->memory, ctx->registers->PC++);
    const uint16_t nn = (uint16_t)(lsb | (msb << 8));

    GB_BusWrite(ctx->memory, nn, ctx->registers->CPU[GB_A_OFFSET]);
}

void GB_LDH_A_N(const SystemContext *ctx)
{
    /*
    n = read(PC++)
    A = read(unsigned_16(lsb=n, msb=0xFF))
    */

    const uint8_t n = GB_BusRead(ctx->memory, ctx->registers->PC++);
    const uint16_t u16 = (uint16_t)(n | (0xFF << 8));

    ctx->registers->CPU[GB_A_OFFSET] = GB_BusRead(ctx->memory, u16);
}

void GB_LDH_N_A(const SystemContext *ctx)
{
    /*
    n = read(PC++)
    write(unsigned_16(lsb=n, msb=0xFF), A)
    */
    const uint8_t n = GB_BusRead(ctx->memory, ctx->registers->PC++);
    const uint16_t u16 = (uint16_t)(n | (0xFF << 8));

    GB_BusWrite(ctx->memory, u16, ctx->registers->CPU[GB_A_OFFSET]);
}

void GB_LDH_A_C(const SystemContext *ctx)
{
    //A = read(unsigned_16(lsb=C, msb=0xFF))
    const uint16_t u16 = (uint16_t)(GB_GetReg8(ctx->registers, GB_C_OFFSET) | (0xFF << 8));
    GB_SetReg8(ctx->registers, GB_A_OFFSET, GB_BusRead(ctx->memory, u16));
}

void GB_LDH_C_A(const SystemContext *ctx)
{
    //write(unsigned_16(lsb=C, msb=0xFF), A)
    const uint16_t u16 = (uint16_t)(GB_GetReg8(ctx->registers, GB_C_OFFSET) | (0xFF << 8));
    GB_BusWrite(ctx->memory, u16,ctx->registers->CPU[GB_A_OFFSET]);
}

void GB_LDI_HL_A(const SystemContext *ctx)
{
    //write(HL++, A)
    GB_BusWrite(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET]++, GB_GetReg8(ctx->registers, GB_A_OFFSET));
}

void GB_LDI_A_HL(const SystemContext *ctx)
{
    //A = read(HL++)
    GB_SetReg8(ctx->registers, GB_A_OFFSET, GB_BusRead(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET]++));
}

void GB_LDD_HL_A(const SystemContext *ctx)
{
    //write(HL--, A)
    GB_BusWrite(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET]--, GB_GetReg8(ctx->registers, GB_A_OFFSET));

}

void GB_LDD_A_HL(const SystemContext *ctx)
{
    //A = read(HL--)
    GB_SetReg8(ctx->registers, GB_A_OFFSET, GB_BusRead(ctx->memory, ctx->registers->CPU[GB_HL_OFFSET]--));
}

// 16 BIT LOAD INSTRUCTIONS
void GB_LD_RR_NN(const SystemContext *ctx)
{
}
void GB_LD_NN_SP(const SystemContext *ctx)
{
}
void GB_LD_SP_HL(const SystemContext *ctx)
{
}
void GB_PUSH_RR(const SystemContext *ctx)
{
}
void GB_POP_RR(const SystemContext *ctx)
{
}
// 8 BIT ALU INSTRUCTIONS
void GB_ADD_A_R(const SystemContext *ctx)
{
}
void GB_ADD_A_N(const SystemContext *ctx)
{
}
void GB_ADD_A_HL(const SystemContext *ctx)
{
}
void GB_ADC_A_R(const SystemContext *ctx)
{
}
void GB_ADC_A_N(const SystemContext *ctx)
{
}
void GB_ADC_A_HL(const SystemContext *ctx)
{
}
void GB_SUB_R(const SystemContext *ctx)
{
}
void GB_SUB_N(const SystemContext *ctx)
{
}
void GB_SUB_HL(const SystemContext *ctx)
{
}
void GB_SBC_A_R(const SystemContext *ctx)
{
}
void GB_SBC_A_N(const SystemContext *ctx)
{
}
void GB_SBC_A_HL(const SystemContext *ctx) {}

void GB_AND_R(const SystemContext *ctx)
{
}
void GB_AND_N(const SystemContext *ctx)
{
}
void GB_AND_HL(const SystemContext *ctx)
{
}
void GB_XOR_R(const SystemContext *ctx)
{
}
void GB_XOR_N(const SystemContext *ctx)
{
}
void GB_XOR_HL(const SystemContext *ctx)
{
}
void GB_OR_R(const SystemContext *ctx)
{
}
void GB_OR_N(const SystemContext *ctx)
{
}
void GB_OR_HL(const SystemContext *ctx)
{
}
void GB_CP_R(const SystemContext *ctx)
{
}
void GB_CP_N(const SystemContext *ctx)
{
}
void GB_CP_HL(const SystemContext *ctx)
{
}
void GB_INC_R(const SystemContext *ctx)
{
}
void GB_INC_HL(const SystemContext *ctx)
{
}
void GB_DEC_R(const SystemContext *ctx)
{
}
void GB_DEC_HL(const SystemContext *ctx)
{
}
void GB_DAA(const SystemContext *ctx)
{
}
void GB_CPL(const SystemContext *ctx)
{
}
// 16 BIT ALU INSTRUCTIONS
void GB_ADD_HL_RR(const SystemContext *ctx)
{
}
void GB_INC_RR(const SystemContext *ctx)
{
}
void GB_DEC_RR(const SystemContext *ctx)
{
}
void GB_ADD_SP_DD(const SystemContext *ctx)
{
}
void GB_LD_HL_SP_PLUS_DD(const SystemContext *ctx)
{
}
// ROTATE AND SHIFT INSTRUCTIONS
void GB_RLCA(const SystemContext *ctx)
{
}
void GB_RLA(const SystemContext *ctx)
{
}
void GB_RRCA(const SystemContext *ctx)
{
}
void GB_RRA(const SystemContext *ctx)
{
}
void GB_RLC_R(const SystemContext *ctx)
{
}
void GB_RLC_HL(const SystemContext *ctx)
{
}
void GB_RL_R(const SystemContext *ctx)
{
}
void GB_RL_HL(const SystemContext *ctx)
{
}
void GB_RRC_R(const SystemContext *ctx)
{
}
void GB_RRC_HL(const SystemContext *ctx)
{
}
void GB_RR_R(const SystemContext *ctx)
{
}
void GB_RR_HL(const SystemContext *ctx)
{
}
void GB_SLA_R(const SystemContext *ctx)
{
}
void GB_SLA_HL(const SystemContext *ctx)
{
}
void GB_SWAP_R(const SystemContext *ctx)
{
}
void GB_SWAP_HL(const SystemContext *ctx)
{
}
void GB_SRA_R(const SystemContext *ctx)
{
}
void GB_SRA_HL(const SystemContext *ctx)
{
}
void GB_SRL_R(const SystemContext *ctx)
{
}
void GB_SRL_HL(const SystemContext *ctx)
{
}
// SINGLE BIT OPERATIONS
void GB_BIT_N_R(const SystemContext *ctx)
{
}
void GB_BIT_N_HL(const SystemContext *ctx)
{
}
void GB_SET_N_R(const SystemContext *ctx)
{
}
void GB_SET_N_HL(const SystemContext *ctx)
{
}
void GB_RES_N_R(const SystemContext *ctx)
{
}
void GB_RES_N_HL(const SystemContext *ctx)
{
}
// CPU CONTROL INSTRUCTIONS
void GB_CCF(const SystemContext *ctx)
{
}
void GB_SCF(const SystemContext *ctx)
{
}
void GB_NOP(const SystemContext *ctx)
{
}
void GB_HALT(const SystemContext *ctx)
{
}
void GB_STOP(const SystemContext *ctx)
{
}
void GB_DI(const SystemContext *ctx)
{
}
void GB_EI(const SystemContext *ctx)
{
}
// JUMP INSTRUCTIONS
void GB_JP_NN(const SystemContext *ctx)
{
}
void GB_JP_HL(const SystemContext *ctx)
{
}
void GB_JP_F_NN(const SystemContext *ctx)
{
}
void GB_JR_PC_PLUS_DD(const SystemContext *ctx)
{
}
void GB_JR_F_PC_PLUS_DD(const SystemContext *ctx)
{
}
void GB_CALL_NN(const SystemContext *ctx)
{
}
void GB_CALL_F_NN(const SystemContext *ctx)
{
}
void GB_RET(const SystemContext *ctx)
{
}
void GB_RET_F(const SystemContext *ctx)
{
}
void GB_RETI(const SystemContext *ctx)
{
}
void GB_RST_N(const SystemContext *ctx)
{
}