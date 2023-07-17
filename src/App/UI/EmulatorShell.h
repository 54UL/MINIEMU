
#ifndef EMULATOR_SHELL_H
#define EMULATOR_SHELL_H

#include <stdint.h>

void EmuShell_Init();
void EmuShell_UpdateFrame(uint32_t * pixels);
void EmuShell_Invoke(const char* cmd, void * payload);
void EmuShell_KeyPressed(const char code);
uint8_t EmuShell_Shown();

#endif
