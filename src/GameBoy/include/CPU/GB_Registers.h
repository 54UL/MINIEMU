#ifndef GB_REGISTERS_H
#define GB_REGISTERS_H

#include <stdint.h>

#define GB_BC_OFFSET 0
#define GB_B_OFFSET  GB_BC_OFFSET
#define GB_C_OFFSET  1
#define GB_DE_OFFSET 2
#define GB_D_OFFSET  GB_DE_OFFSET
#define GB_E_OFFSET  3
#define GB_HL_OFFSET 4
#define GB_H_OFFSET  GB_HL_OFFSET
#define GB_L_OFFSET  5
#define GB_AF_OFFSET  7
#define GB_A_OFFSET  GB_AF_OFFSET
#define GB_F_OFFSET  8

#define GB_ZERO_FLAG    7
#define GB_N_FLAG       6
#define GB_H_FLAG       5
#define GB_C_FLAG       4

//BRIEF: This is used for checking decoded 'r' value is an HL indirect addressing mode (NOT THE SAME AS THE GB_HL_OFFSET)
#define GB_HL_R_INDIRECT_OFFSET 0X06

//BRIEF: 16 bit offsets to decode 'rr' values on instructions...
#define GB_BC_INSTR_OFFSET 0
#define GB_DE_INSTR_OFFSET 1
#define GB_HL_INSTR_OFFSET 2
#define GB_AF_INSTR_OFFSET 3

//TODO: WHEN WIDELY USED CHECK PERFORMANCE REPLACING A FUNCTION...

#define GB_U8_TO_U16(LSB, MSB) (uint16_t)(lsb | (msb << 8))
#define GB_F_OR_AF(CTX, F) CTX->registers->CPU[GB_AF_OFFSET] | (F << 8)

#define GB_SET_F(F, FLAG, VALUE) F | ((FLAG) << (VALUE))
#define GB_TEST_F(CTX, FLAG) (((CTX->registers->CPU[GB_AF_OFFSET] >> 8) >> FLAG) & 0X01)

typedef struct 
{
    uint16_t CPU[4];
    uint16_t SP;
    uint16_t PC;
    uint16_t INSTRUCTION;
} GB_Registers;

#endif