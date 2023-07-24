#ifndef CC8_EMULATOR_H
#define CC8_EMULATOR_H

#include "CC8_Machine.h"

const uint8_t CC8_FONT[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // "0"
    0x20, 0x60, 0x20, 0x20, 0x70, // "1"
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // "2"
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // "3"
    0x90, 0x90, 0xF0, 0x10, 0x10, // "4"
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // "5"
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // "6"
    0xF0, 0x10, 0x20, 0x40, 0x40, // "7"
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // "8"
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // "9"
    0xF0, 0x90, 0xF0, 0x90, 0x90, // "A"
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // "B"
    0xF0, 0x80, 0x80, 0x80, 0xF0, // "C"
    0xE0, 0x90, 0x90, 0x90, 0xE0, // "D"
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // "E"
    0xF0, 0x80, 0xF0, 0x80, 0x80  // "F"
};

uint8_t CC8_LoadProgram(const char *filePath);
void CC8_QuitProgram();
void CC8_TickDelayTimer();
int  CC8_TickEmulation();
void CC8_SetKeyboardValue(uint8_t key);
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
void CC8_SHR_VX_VY(uint8_t x, uint8_t y);
void CC8_SUBN_VX_VY(uint8_t x, uint8_t y);
void CC8_SHL_VX_VY(uint8_t x, uint8_t y);
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