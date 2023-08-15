#ifndef GB_INSTRUCTIONS_H
#define GB_INSTRUCTIONS_H

#include "../Emulation/GB_SystemContext.h"

// 8-BIT LOAD INSTRUCTIONS
void GB_LD_R_R(const InstructionContext *ctx);
void GB_LD_R_N(const InstructionContext *ctx);
void GB_LD_R_HL(const InstructionContext *ctx);
void GB_LD_HL_R(const InstructionContext *ctx);
void GB_LD_HL_N(const InstructionContext *ctx);
void GB_LD_A_BC(const InstructionContext *ctx);
void GB_LD_A_DE(const InstructionContext *ctx);
void GB_LD_A_NN(const InstructionContext *ctx);
void GB_LD_BC_A(const InstructionContext *ctx);
void GB_LD_DE_A(const InstructionContext *ctx);
void GB_LD_NN_A(const InstructionContext *ctx);
void GB_LD_A_FF00_PLUS_N(const InstructionContext *ctx);
void GB_LD_FF00_PLUS_N_A(const InstructionContext *ctx);
void GB_LD_A_FF00_PLUS_C(const InstructionContext *ctx);
void GB_LD_FF00_PLUS_C_A(const InstructionContext *ctx);
void GB_LDI_HL_A(const InstructionContext *ctx);
void GB_LDI_A_HL(const InstructionContext *ctx);
void GB_LDD_HL_A(const InstructionContext *ctx);
void GB_LDD_A_HL(const InstructionContext *ctx);
//16 BIT LOAD INSTRUCTIONS
void GB_LD_RR_NN(const InstructionContext *ctx);      
void GB_LD_NN_SP(const InstructionContext *ctx);    
void GB_LD_SP_HL(const InstructionContext *ctx);      
void GB_PUSH_RR(const InstructionContext *ctx);         
void GB_POP_RR(const InstructionContext *ctx);  
// 8 BIT ALU INSTRUCTIONS
void GB_ADD_A_R(const InstructionContext *ctx);        
void GB_ADD_A_N(const InstructionContext *ctx);        
void GB_ADD_A_HL(const InstructionContext *ctx);     
void GB_ADC_A_R(const InstructionContext *ctx);        
void GB_ADC_A_N(const InstructionContext *ctx);        
void GB_ADC_A_HL(const InstructionContext *ctx);    
void GB_SUB_R(const InstructionContext *ctx);          
void GB_SUB_N(const InstructionContext *ctx);          
void GB_SUB_HL(const InstructionContext *ctx);      
void GB_SBC_A_R(const InstructionContext *ctx);        
void GB_SBC_A_N(const InstructionContext *ctx);        
void GB_SBC_A_HL(const InstructionContext *ctx);     
void GB_AND_R(const InstructionContext *ctx);          
void GB_AND_N(const InstructionContext *ctx);          
void GB_AND_HL(const InstructionContext *ctx);       
void GB_XOR_R(const InstructionContext *ctx);          
void GB_XOR_N(const InstructionContext *ctx);          
void GB_XOR_HL(const InstructionContext *ctx);       
void GB_OR_R(const InstructionContext *ctx);          
void GB_OR_N(const InstructionContext *ctx);          
void GB_OR_HL(const InstructionContext *ctx);       
void GB_CP_R(const InstructionContext *ctx);          
void GB_CP_N(const InstructionContext *ctx);          
void GB_CP_HL(const InstructionContext *ctx);       
void GB_INC_R(const InstructionContext *ctx);           
void GB_INC_HL(const InstructionContext *ctx);        
void GB_DEC_R(const InstructionContext *ctx);           
void GB_DEC_HL(const InstructionContext *ctx);        
void GB_DAA(const InstructionContext *ctx);              
void GB_CPL(const InstructionContext *ctx);  
// 16 BIT ALU INSTRUCTIONS
void GB_ADD_HL_RR(const InstructionContext *ctx);
void GB_INC_RR(const InstructionContext *ctx);
void GB_DEC_RR(const InstructionContext *ctx);
void GB_ADD_SP_DD(const InstructionContext *ctx);
void GB_LD_HL_SP_PLUS_DD(const InstructionContext *ctx);
// ROTATE AND SHIFT INSTRUCTIONS

#endif