#include <CPU/GB_Instructions.h>
#include <CPU/GB_Bus.h>

// 8-BIT LOAD INSTRUCTIONS
void GB_LD_R_R(const SystemContext *ctx)
{
    //encoding: b01xxxyyy/various
    uint8_t r1 = (ctx->registers->INSTRUCTION & 0x38) >> 3;
    uint8_t r2 = (ctx->registers->INSTRUCTION & 0x07);
    ctx->registers->CPU[r1] = ctx->registers->CPU[r2];
}

void GB_LD_R_N(const SystemContext *ctx)
{
    //encoding: 0b00xxx110/various + n
    uint8_t r1 = (ctx->registers->INSTRUCTION & 0x38) >> 3;
    ctx->registers->CPU[r1] = GB_BusRead(ctx->memory, ctx->registers->PC + 1);
}

void GB_LD_R_HL(const SystemContext *ctx)
{
}
void GB_LD_HL_R(const SystemContext *ctx)
{
}
void GB_LD_HL_N(const SystemContext *ctx)
{
}
void GB_LD_A_BC(const SystemContext *ctx)
{
}
void GB_LD_A_DE(const SystemContext *ctx)
{
}
void GB_LD_A_NN(const SystemContext *ctx)
{
}
void GB_LD_BC_A(const SystemContext *ctx)
{
}
void GB_LD_DE_A(const SystemContext *ctx)
{
}
void GB_LD_NN_A(const SystemContext *ctx)
{
}
void GB_LD_A_FF00_PLUS_N(const SystemContext *ctx)
{
}
void GB_LD_FF00_PLUS_N_A(const SystemContext *ctx)
{
}
void GB_LD_A_FF00_PLUS_C(const SystemContext *ctx)
{
}
void GB_LD_FF00_PLUS_C_A(const SystemContext *ctx)
{
}
void GB_LDI_HL_A(const SystemContext *ctx)
{
}
void GB_LDI_A_HL(const SystemContext *ctx)
{
}
void GB_LDD_HL_A(const SystemContext *ctx)
{
}
void GB_LDD_A_HL(const SystemContext *ctx)
{
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
void GB_ADC_A_HL(const SystemContext *ctx) {}

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