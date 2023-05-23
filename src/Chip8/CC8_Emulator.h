#ifndef CC8_EMULATOR_H
#define CC8_EMULATOR_H

#include "CC8_Machine.h"

void CC8_LoadProgram(const char *filePath);
void CC8_QuitProgram();
void CC8_TickEmulation();
void CC8_SetEmulationContext(CC8_Machine *context);

//CHIP 8 IMPL
void CC8_CLS();
void CC8_RET();
void CC8_JMP(uint16_t addr);
void CC8_CALL(uint16_t addr);
void CC8_SE_VX_BYTE(uint8_t x, uint8_t kk);
void CC8_SNE_VX_BYTE(uint8_t x, uint8_t kk);
void CC8_SE_VX_VY(uint8_t x, uint8_t y);
void CC8_LD_VX_BYTE(uint8_t x, uint8_t kk);
void CC8_ADD_VX_BYTE(uint8_t x, uint8_t kk);
void CC8_LD_VX_VY(uint8_t x, uint8_t y);
void CC8_OR_VX_VY(uint8_t x, uint8_t y);
void CC8_AND_VX_VY(uint8_t x, uint8_t y);
void CC8_XOR_VX_VY(uint8_t x, uint8_t y);
void CC8_ADD_VX_VY(uint8_t x, uint8_t y);
void CC8_SUB_VX_VY(uint8_t x, uint8_t y);
void CC8_SHR_VX(uint8_t x);
void CC8_SUBN_VX_VY(uint8_t x, uint8_t y);
void CC8_SHL_VX(uint8_t x);
void CC8_SNE_VX_VY(uint8_t x, uint8_t y);
void CC8_LD_I_ADDR(uint16_t addr);
void CC8_JP_V0_ADDR(uint16_t addr);
void CC8_RND_VX_BYTE(uint8_t x, uint8_t kk);
void CC8_DRW_VX_VY_NIBBLE(uint8_t x, uint8_t y, uint8_t n);
void CC8_SKP_VX(uint8_t x);
void CC8_SKNP_VX(uint8_t x);
void CC8_LD_VX_DT(uint8_t x);
void CC8_LD_VX_K(uint8_t x);
void CC8_LD_DT_VX(uint8_t x);
void CC8_LD_ST_VX(uint8_t x);
void CC8_ADD_I_VX(uint8_t x);
void CC8_LD_F_VX(uint8_t x);
void CC8_LD_B_VX(uint8_t x);
void CC8_LD_I_VX(uint8_t x);
void CC8_LD_VX_I(uint8_t x);

#endif