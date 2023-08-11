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
    uint16_t SP;
    uint16_t PC;
} GB_Registers;

#endif