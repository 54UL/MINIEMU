#ifndef GB_INSTRUCTION_H
#define GB_INSTRUCTION_H
#include "GB_SystemContext.h"

typedef struct {
    uint16_t mask;
    uint16_t opcode;
    uint8_t  cycles;
    instructionFnPtrGb handler;
} GameBoyInstruction;

#endif