#ifndef MNE_LOG_H
#define MNE_LOG_H

#include <stdio.h>
#include <stdint.h>

//TODO: IMPLEMENT A REAL ONE OR USE SPDLG...
#define MNE_Log(msg...) printf(msg)

void MNE_HexDump(uint8_t *buffer, const size_t size);

#endif