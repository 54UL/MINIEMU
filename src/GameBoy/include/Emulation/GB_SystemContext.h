#ifndef GB_SYSTEM_CONTEXT_H
#define GB_SYSTEM_CONTEXT_H
#include "../include/CPU/GB_Registers.h"

typedef struct{
    //INSERT HERE DECODED INSTRUCTION PARTS
    GB_Registers * registers;
} InstructionContext;

typedef void (*instructionFnPtr)(const InstructionContext * ctx);



#endif