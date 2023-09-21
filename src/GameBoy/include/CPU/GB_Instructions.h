#ifndef GB_INSTRUCTIONS_H
#define GB_INSTRUCTIONS_H
#include <Emulation/GB_SystemContext.h>

#define GB_INSTRUCTION_SET_LENGHT 0xFF

// 8-BIT LOAD INSTRUCTIONS
uint8_t GB_LD_R_R(SystemContext *ctx);
uint8_t GB_LD_R_N(SystemContext *ctx);
uint8_t GB_LD_R_HL(SystemContext *ctx);
uint8_t GB_LD_HL_R(SystemContext *ctx);
uint8_t GB_LD_HL_N(SystemContext *ctx);
uint8_t GB_LD_A_BC(SystemContext *ctx);
uint8_t GB_LD_A_DE(SystemContext *ctx);
uint8_t GB_LD_A_NN(SystemContext *ctx);
uint8_t GB_LD_BC_A(SystemContext *ctx);
uint8_t GB_LD_DE_A(SystemContext *ctx);
uint8_t GB_LD_NN_A(SystemContext *ctx);
uint8_t GB_LDH_A_N(SystemContext *ctx);
uint8_t GB_LDH_N_A(SystemContext *ctx);
uint8_t GB_LDH_A_C(SystemContext *ctx);
uint8_t GB_LDH_C_A(SystemContext *ctx);
uint8_t GB_LDI_HL_A(SystemContext *ctx);
uint8_t GB_LDI_A_HL(SystemContext *ctx);
uint8_t GB_LDD_HL_A(SystemContext *ctx);
uint8_t GB_LDD_A_HL(SystemContext *ctx);

// 16 BIT LOAD INSTRUCTIONS
uint8_t GB_LD_RR_NN(SystemContext *ctx);
uint8_t GB_LD_NN_SP(SystemContext *ctx);
uint8_t GB_LD_SP_HL(SystemContext *ctx);
uint8_t GB_PUSH_RR(SystemContext *ctx);
uint8_t GB_POP_RR(SystemContext *ctx);

// 8 BIT ALU INSTRUCTIONS
uint8_t GB_ADD_A_R(SystemContext *ctx);
uint8_t GB_ADD_A_N(SystemContext *ctx);
uint8_t GB_ADD_A_HL(SystemContext *ctx);
uint8_t GB_ADC_A_R(SystemContext *ctx);
uint8_t GB_ADC_A_N(SystemContext *ctx);
uint8_t GB_ADC_A_HL(SystemContext *ctx);
uint8_t GB_SUB_R(SystemContext *ctx);
uint8_t GB_SUB_N(SystemContext *ctx);
uint8_t GB_SUB_HL(SystemContext *ctx);
uint8_t GB_SBC_A_R(SystemContext *ctx);
uint8_t GB_SBC_A_N(SystemContext *ctx);
uint8_t GB_SBC_A_HL(SystemContext *ctx);
uint8_t GB_AND_R(SystemContext *ctx);
uint8_t GB_AND_N(SystemContext *ctx);
uint8_t GB_AND_HL(SystemContext *ctx);
uint8_t GB_XOR_R(SystemContext *ctx);
uint8_t GB_XOR_N(SystemContext *ctx);
uint8_t GB_XOR_HL(SystemContext *ctx);
uint8_t GB_OR_R(SystemContext *ctx);
uint8_t GB_OR_N(SystemContext *ctx);
uint8_t GB_OR_HL(SystemContext *ctx);
uint8_t GB_CP_R(SystemContext *ctx);
uint8_t GB_CP_N(SystemContext *ctx);
uint8_t GB_CP_HL(SystemContext *ctx);
uint8_t GB_INC_R(SystemContext *ctx);
uint8_t GB_INC_HL(SystemContext *ctx);
uint8_t GB_DEC_R(SystemContext *ctx);
uint8_t GB_DEC_HL(SystemContext *ctx);
uint8_t GB_DAA(SystemContext *ctx);
uint8_t GB_CPL(SystemContext *ctx);

// 16 BIT ALU INSTRUCTIONS
uint8_t GB_ADD_HL_RR(SystemContext *ctx);
uint8_t GB_INC_RR(SystemContext *ctx);
uint8_t GB_DEC_RR(SystemContext *ctx);
uint8_t GB_ADD_SP_DD(SystemContext *ctx);
uint8_t GB_LD_HL_SP_PLUS_DD(SystemContext *ctx);

// ROTATE AND SHIFT INSTRUCTIONS
uint8_t GB_RLCA(SystemContext *ctx);
uint8_t GB_RLA(SystemContext *ctx);
uint8_t GB_RRCA(SystemContext *ctx);
uint8_t GB_RRA(SystemContext *ctx);
uint8_t GB_RLC_R(SystemContext *ctx);
uint8_t GB_RLC_HL(SystemContext *ctx);
uint8_t GB_RL_R(SystemContext *ctx);
uint8_t GB_RL_HL(SystemContext *ctx);
uint8_t GB_RRC_R(SystemContext *ctx);
uint8_t GB_RRC_HL(SystemContext *ctx);
uint8_t GB_RR_R(SystemContext *ctx);
uint8_t GB_RR_HL(SystemContext *ctx);
uint8_t GB_SLA_R(SystemContext *ctx);
uint8_t GB_SLA_HL(SystemContext *ctx);
uint8_t GB_SWAP_R(SystemContext *ctx);
uint8_t GB_SWAP_HL(SystemContext *ctx);
uint8_t GB_SRA_R(SystemContext *ctx);
uint8_t GB_SRA_HL(SystemContext *ctx);
uint8_t GB_SRL_R(SystemContext *ctx);
uint8_t GB_SRL_HL(SystemContext *ctx);

// CPU CONTROL INSTRUCTIONS
uint8_t GB_CCF(SystemContext *ctx);
uint8_t GB_SCF(SystemContext *ctx);
uint8_t GB_NOP(SystemContext *ctx);
uint8_t GB_HALT(SystemContext *ctx);
uint8_t GB_STOP(SystemContext *ctx);
uint8_t GB_DI(SystemContext *ctx);
uint8_t GB_EI(SystemContext *ctx);

// JUMP INSTRUCTIONS
uint8_t GB_JP_NN(SystemContext *ctx);
uint8_t GB_JP_HL(SystemContext *ctx);
uint8_t GB_JP_F_NN(SystemContext *ctx);
uint8_t GB_JR_PC_PLUS_DD(SystemContext *ctx);
uint8_t GB_JR_F_PC_PLUS_DD(SystemContext *ctx);
uint8_t GB_CALL_NN(SystemContext *ctx);
uint8_t GB_CALL_F_NN(SystemContext *ctx);
uint8_t GB_RET(SystemContext *ctx);
uint8_t GB_RET_F(SystemContext *ctx);
uint8_t GB_RETI(SystemContext *ctx);
uint8_t GB_RST_N(SystemContext *ctx);

// SINGLE BIT OPERATIONS (CB PREFIX)
uint8_t GB_CB_BIT_N_R(SystemContext *ctx);   
uint8_t GB_CB_BIT_N_HL(SystemContext *ctx);
uint8_t GB_CB_SET_N_R(SystemContext *ctx);   
uint8_t GB_CB_SET_N_HL(SystemContext *ctx);
uint8_t GB_CB_RES_N_R(SystemContext *ctx);   
uint8_t GB_CB_RES_N_HL(SystemContext *ctx);

#endif