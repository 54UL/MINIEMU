#ifndef CC8_INSTRUCTION_CONTEXT_H
#define CC8_INSTRUCTION_CONTEXT_H

#include "CC8_Memory.h"
#include <minemu.h>

typedef struct {
    uint8_t x;
    uint8_t y;
    uint16_t nnn;
    uint8_t kk;
    uint8_t n;
    CC8_Memory * memory;
} InstructionContext;

#endif