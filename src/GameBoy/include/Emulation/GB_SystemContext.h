#ifndef GB_SYSTEM_CONTEXT_H
#define GB_SYSTEM_CONTEXT_H
#include <stdint.h>

#include <CPU/GB_Registers.h>
#define GB_MEMORY_SIZE 0xFFFF

typedef struct
{
    uint8_t memory[GB_MEMORY_SIZE];
    uint8_t bios[0xFF];
    GB_Registers * registers;
} SystemContext;

typedef void (*instructionFnPtrGb)(const SystemContext * ctx);

#endif