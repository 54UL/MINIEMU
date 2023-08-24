#ifndef GB_SYSTEM_CONTEXT_H
#define GB_SYSTEM_CONTEXT_H
#include <stdint.h>

#include <CPU/GB_Registers.h>
#define GB_MEMORY_SIZE 0xFFFF

// Not the best implementation...
typedef struct
{
    uint8_t Z;
    uint8_t N;
    uint8_t H;
    uint8_t C;
} GB_FlagsReg;

typedef struct
{
    // CPU STATE
    uint8_t  IE;
    
    // this should not be here...
    uint8_t*      memory;
    GB_Registers* registers;
    GB_FlagsReg*  flags;
} SystemContext;

typedef void (*instructionFnPtrGb)(const SystemContext * ctx);

#endif