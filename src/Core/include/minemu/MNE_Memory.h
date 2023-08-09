#ifndef MNE_MEMORY_H
#define MNE_MEMORY_H
#include <stdlib.h>

//TODO: Implement memory leak detection and telemetry
#define MNE_New(buffer, length, type) buffer=(type*) calloc(sizeof(type), length)
#define MNE_Delete(buffer) free(buffer)

#endif