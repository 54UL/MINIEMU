#ifndef GB_REGISTERS_H
#define GB_REGISTERS_H

#include <stdint.h>

/*
    posible structure for registers, put this inside of a structure:
    union {
        struct {
            u16 AF, BC, DE, HL;
        } reg16;
        struct {
            u8 F, A, C, B, E, D, L, H;
        } reg8;
    };
*/

// 16 bit registers instruction encoding offests
#define GB_BC_OFFSET 0
#define GB_DE_OFFSET 1
#define GB_HL_OFFSET 2
#define GB_AF_OFFSET 3
#define GB_SP_OFFSET 3

//REGISTERS OFFSETS
// LSB MSB ARE FLIPPED THAT'S WHY B = 1 AND C = 0 AND 
#define GB_B_OFFSET  1
#define GB_C_OFFSET  0
#define GB_D_OFFSET  3
#define GB_E_OFFSET  2
#define GB_H_OFFSET  5
#define GB_L_OFFSET  4
#define GB_A_OFFSET  7
#define GB_F_OFFSET  6

//FLAGS
#define GB_ZERO_FLAG    7
#define GB_N_FLAG       6
#define GB_H_FLAG       5
#define GB_C_FLAG       4

//BRIEF: This is used for checking decoded 'r' value is an HL indirect addressing mode (NOT THE SAME AS THE GB_HL_OFFSET)
#define GB_HL_R_INDIRECT_OFFSET 0x06

//TODO: WHEN WIDELY USED CHECK PERFORMANCE REPLACING FOR A FUNCTION...
#define GB_U8_TO_U16(LSB, MSB) (uint16_t)(lsb | (msb << 8))
#define GB_F_OR_AF(CTX, F) ((CTX->registers->CPU[GB_AF_OFFSET] | F) & 0xFF)
#define GB_A_OR_AF(CTX, A) ((CTX->registers->CPU[GB_AF_OFFSET] | A) << 8)
#define GB_TMP_F() uint8_t tmpRegF = 0x00
#define GB_SET_F(FLAG, VALUE) tmpRegF | ((FLAG) << (VALUE))
#define GB_TEST_F(CTX, FLAG) (((CTX->registers->CPU[GB_AF_OFFSET] & 0xFF) >> FLAG) & 0X01)

typedef struct 
{
    uint16_t CPU[4];
    uint16_t SP;
    uint16_t PC;
    uint16_t INSTRUCTION;
} GB_Registers;

#endif