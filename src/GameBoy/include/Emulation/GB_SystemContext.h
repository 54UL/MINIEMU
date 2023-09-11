#ifndef GB_SYSTEM_CONTEXT_H
#define GB_SYSTEM_CONTEXT_H

#include <stdint.h>
#include <CPU/GB_Registers.h>
#include <Memory/GB_Header.h>

#define GB_MEMORY_SIZE 0xFFFF

typedef struct
{
    // CPU STATE
    uint8_t  IE;
    uint8_t HALT;
   
    // OVERALL SYSTEM CONTEXT (TODO:IMPROVE MEMORY MANGEMENT)
    uint8_t *memory;
    GB_Registers *registers;
    GB_Header *header;
} SystemContext;

typedef uint8_t (*instructionFnPtrGb)(SystemContext * ctx);

#endif