#ifndef GB_INSTRUCTION_H
#define GB_INSTRUCTION_H
#include "GB_SystemContext.h"
#define GB_DEBUG

typedef struct {
    uint16_t mask;
    uint16_t opcode;
    uint8_t  cycles;
    instructionFnPtrGb handler;
#ifdef GB_DEBUG
    const char * handlerName;
#endif

} GameBoyInstruction;

#ifdef GB_DEBUG
#define GB_INSTRUCTION(mask, opcode, cycles, handler)  {mask, opcode, cycles, (instructionFnPtrGb)handler, ""#handler"[C:"#cycles"] [MASK:"#mask"] [CODE:"#opcode"] [CURRENT:%04X\n"}
#else
#define GB_INSTRUCTION(mask, opcode, cycles, handler)  {mask, opcode, cycles, (instructionFnPtrGb)handler}
#endif

#endif