#ifndef GB_REGISTERS_H
#define GB_REGISTERS_H

#include <stdint.h>

/*
## Registers
16-bit |Hi |Lo | Name/Function
-------|---|---|--------------
   AF  | A | - | Accumulator & Flags
   BC  | B | C | BC
   DE  | D | E | DE
   HL  | H | L | HL
   SP  | - | - | Stack Pointer
   PC  | - | - | Program Counter/Pointer
*/

/*
r byte encoding
B:0
C:1
D:2
E:3
H:4
L:5
HL:6
A:7

rr byte encoding
*/

#define GB_BC_OFFSET 0
#define GB_B_OFFSET  0
#define GB_C_OFFSET  1
#define GB_DE_OFFSET 2
#define GB_D_OFFSET  2
#define GB_E_OFFSET  3
#define GB_HL_OFFSET 4
#define GB_H_OFFSET  4
#define GB_L_OFFSET  5
#define GB_AF_OFFSET 7
#define GB_A_OFFSET  7

#define GB_ZERO_FLAG_BIT        7
#define GB_SUBTRACTION_FLAG_BIT 6
#define GB_HALF_CARRY_FLAG_BIT  5
#define GB_CARRY_FLAG_BIT       4

typedef struct 
{
    uint16_t CPU[4];
    uint16_t SP;
    uint16_t PC;
    uint16_t INSTRUCTION;
} GB_Registers;

void GB_SetReg8(GB_Registers *registers, uint8_t r, uint8_t value);
uint8_t GB_GetReg8(const GB_Registers * registers, uint8_t r);

void GB_SetFlag(GB_Registers *registers, uint8_t flag, uint8_t value);
uint8_t GB_GetFlag(GB_Registers *registers, uint8_t flag);

#endif