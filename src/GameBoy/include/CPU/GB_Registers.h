#ifndef GB_REGISTERS_H
#define GB_REGISTERS_H

#include <stdint.h>

typedef struct 
{
    // Acumulator and flags
    union {
        uint16_t AF;
        uint8_t  A:8;
        uint8_t  F;
    };
    // BC
    union {
        uint16_t BC;
        uint8_t  B:8;
        uint8_t  C;
    };
    // DE
    union {
        uint16_t DE;
        uint8_t  D:8;
        uint8_t  E;
    };
    // HL
    union {
        uint16_t HL;
        uint8_t  H:8;
        uint8_t  L;
    };
    uint8_t  CPU[8];
    uint16_t SP;
    uint16_t PC;
    uint16_t INSTRUCTION;
} GB_Registers;

void setReg8(GB_Registers * registers, uint8_t rr, uint8_t value);
uint8_t getReg8(const GB_Registers * registers, uint8_t rr);

#endif