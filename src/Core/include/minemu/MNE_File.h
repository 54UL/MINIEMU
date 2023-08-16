#ifndef MNE_FILE_H
#define MNE_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


long MNE_ReadFile(const char *filePath, const uint8_t flags, void (*callback)(const uint8_t *buffer,size_t bytesRead));


#endif