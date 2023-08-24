#ifndef GB_INSTRUCTIONS_H
#define GB_INSTRUCTIONS_H
#include <Emulation/GB_SystemContext.h>

#define GB_INSTRUCTION_SET_LENGHT 0xFF

// 8-BIT LOAD INSTRUCTIONS
void GB_LD_R_R(SystemContext *ctx);
void GB_LD_R_N(SystemContext *ctx);
void GB_LD_R_HL(SystemContext *ctx);
void GB_LD_HL_R(SystemContext *ctx);
void GB_LD_HL_N(SystemContext *ctx);
void GB_LD_A_BC(SystemContext *ctx);
void GB_LD_A_DE(SystemContext *ctx);
void GB_LD_A_NN(SystemContext *ctx);
void GB_LD_BC_A(SystemContext *ctx);
void GB_LD_DE_A(SystemContext *ctx);
void GB_LD_NN_A(SystemContext *ctx);
void GB_LDH_A_N(SystemContext *ctx);
void GB_LDH_N_A(SystemContext *ctx);
void GB_LDH_A_C(SystemContext *ctx);
void GB_LDH_C_A(SystemContext *ctx);
void GB_LDI_HL_A(SystemContext *ctx);
void GB_LDI_A_HL(SystemContext *ctx);
void GB_LDD_HL_A(SystemContext *ctx);
void GB_LDD_A_HL(SystemContext *ctx);

// 16 BIT LOAD INSTRUCTIONS
void GB_LD_RR_NN(SystemContext *ctx);
void GB_LD_NN_SP(SystemContext *ctx);
void GB_LD_SP_HL(SystemContext *ctx);
void GB_PUSH_RR(SystemContext *ctx);
void GB_POP_RR(SystemContext *ctx);

// 8 BIT ALU INSTRUCTIONS
void GB_ADD_A_R(SystemContext *ctx);
void GB_ADD_A_N(SystemContext *ctx);
void GB_ADD_A_HL(SystemContext *ctx);
void GB_ADC_A_R(SystemContext *ctx);
void GB_ADC_A_N(SystemContext *ctx);
void GB_ADC_A_HL(SystemContext *ctx);
void GB_SUB_R(SystemContext *ctx);
void GB_SUB_N(SystemContext *ctx);
void GB_SUB_HL(SystemContext *ctx);
void GB_SBC_A_R(SystemContext *ctx);
void GB_SBC_A_N(SystemContext *ctx);
void GB_SBC_A_HL(SystemContext *ctx);
void GB_AND_R(SystemContext *ctx);
void GB_AND_N(SystemContext *ctx);
void GB_AND_HL(SystemContext *ctx);
void GB_XOR_R(SystemContext *ctx);
void GB_XOR_N(SystemContext *ctx);
void GB_XOR_HL(SystemContext *ctx);
void GB_OR_R(SystemContext *ctx);
void GB_OR_N(SystemContext *ctx);
void GB_OR_HL(SystemContext *ctx);
void GB_CP_R(SystemContext *ctx);
void GB_CP_N(SystemContext *ctx);
void GB_CP_HL(SystemContext *ctx);
void GB_INC_R(SystemContext *ctx);
void GB_INC_HL(SystemContext *ctx);
void GB_DEC_R(SystemContext *ctx);
void GB_DEC_HL(SystemContext *ctx);
void GB_DAA(SystemContext *ctx);
void GB_CPL(SystemContext *ctx);

// 16 BIT ALU INSTRUCTIONS
void GB_ADD_HL_RR(SystemContext *ctx);
void GB_INC_RR(SystemContext *ctx);
void GB_DEC_RR(SystemContext *ctx);
void GB_ADD_SP_DD(SystemContext *ctx);
void GB_LD_HL_SP_PLUS_DD(SystemContext *ctx);

// ROTATE AND SHIFT INSTRUCTIONS
void GB_RLCA(SystemContext *ctx);
void GB_RLA(SystemContext *ctx);
void GB_RRCA(SystemContext *ctx);
void GB_RRA(SystemContext *ctx);
void GB_RLC_R(SystemContext *ctx);
void GB_RLC_HL(SystemContext *ctx);
void GB_RL_R(SystemContext *ctx);
void GB_RL_HL(SystemContext *ctx);
void GB_RRC_R(SystemContext *ctx);
void GB_RRC_HL(SystemContext *ctx);
void GB_RR_R(SystemContext *ctx);
void GB_RR_HL(SystemContext *ctx);
void GB_SLA_R(SystemContext *ctx);
void GB_SLA_HL(SystemContext *ctx);
void GB_SWAP_R(SystemContext *ctx);
void GB_SWAP_HL(SystemContext *ctx);
void GB_SRA_R(SystemContext *ctx);
void GB_SRA_HL(SystemContext *ctx);
void GB_SRL_R(SystemContext *ctx);
void GB_SRL_HL(SystemContext *ctx);

// SINGLE BIT OPERATIONS
void GB_BIT_N_R(SystemContext *ctx);
void GB_BIT_N_HL(SystemContext *ctx);
void GB_SET_N_R(SystemContext *ctx);
void GB_SET_N_HL(SystemContext *ctx);
void GB_RES_N_R(SystemContext *ctx);
void GB_RES_N_HL(SystemContext *ctx);

// CPU CONTROL INSTRUCTIONS
void GB_CCF(SystemContext *ctx);
void GB_SCF(SystemContext *ctx);
void GB_NOP(SystemContext *ctx);
void GB_HALT(SystemContext *ctx);
void GB_STOP(SystemContext *ctx);
void GB_DI(SystemContext *ctx);
void GB_EI(SystemContext *ctx);

// JUMP INSTRUCTIONS
void GB_JP_NN(SystemContext *ctx);
void GB_JP_HL(SystemContext *ctx);
void GB_JP_F_NN(SystemContext *ctx);
void GB_JR_PC_PLUS_DD(SystemContext *ctx);
void GB_JR_F_PC_PLUS_DD(SystemContext *ctx);
void GB_CALL_NN(SystemContext *ctx);
void GB_CALL_F_NN(SystemContext *ctx);
void GB_RET(SystemContext *ctx);
void GB_RET_F(SystemContext *ctx);
void GB_RETI(SystemContext *ctx);
void GB_RST_N(SystemContext *ctx);

#endif