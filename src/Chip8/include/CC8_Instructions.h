#ifndef CC8_INSTRUCTIONS_H
#define CC8_INSTRUCTIONS_H
#include <CC8_InstructionContext.h>
#include <stdint.h>

//CHIP 8 IMPL
void CC8_SYS_ADDR(InstructionContext * ctx);
void CC8_CLS(InstructionContext * ctx);
void CC8_RET(InstructionContext * ctx);
void CC8_JMP(InstructionContext * ctx);
void CC8_CALL(InstructionContext * ctx);
void CC8_SE_VX_BYTE(InstructionContext * ctx);
void CC8_SNE_VX_BYTE(InstructionContext * ctx);
void CC8_SE_VX_VY(InstructionContext * ctx);
void CC8_LD_VX_BYTE(InstructionContext * ctx);
void CC8_ADD_VX_BYTE(InstructionContext * ctx);
void CC8_LD_VX_VY(InstructionContext * ctx);
void CC8_OR_VX_VY(InstructionContext * ctx);
void CC8_AND_VX_VY(InstructionContext * ctx);
void CC8_XOR_VX_VY(InstructionContext * ctx);
void CC8_ADD_VX_VY(InstructionContext * ctx);
void CC8_SUB_VX_VY(InstructionContext * ctx);
void CC8_SHR_VX_VY(InstructionContext * ctx);
void CC8_SUBN_VX_VY(InstructionContext * ctx);
void CC8_SHL_VX_VY(InstructionContext * ctx);
void CC8_SNE_VX_VY(InstructionContext * ctx);
void CC8_LD_I_ADDR(InstructionContext * ctx);
void CC8_JP_V0_ADDR(InstructionContext * ctx);
void CC8_RND_VX_BYTE(InstructionContext * ctx);
void CC8_DRW_VX_VY_NIBBLE(InstructionContext * ctx);
void CC8_SKP_VX(InstructionContext * ctx);
void CC8_SKNP_VX(InstructionContext * ctx);
void CC8_LD_VX_DT(InstructionContext * ctx);
void CC8_LD_VX_K(InstructionContext * ctx);
void CC8_LD_DT_VX(InstructionContext * ctx);
void CC8_LD_ST_VX(InstructionContext * ctx);
void CC8_ADD_I_VX(InstructionContext * ctx);
void CC8_LD_F_VX(InstructionContext * ctx);
void CC8_LD_B_VX(InstructionContext * ctx);
void CC8_LD_I_VX(InstructionContext * ctx);
void CC8_LD_VX_I(InstructionContext * ctx);

#endif