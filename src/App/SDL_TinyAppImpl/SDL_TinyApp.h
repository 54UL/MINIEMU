#ifndef SDL_TINY_APP_H
#define SDL_TINY_APP_H

#include "../App.h"

//Function definitions
void       Init_App(uint16_t w, uint16_t h, ActionCallback actionsCallback, EmulatorShell * shell);
uint8_t    Step_SDL(StepCallback renderCallback);
void       Reset_SDL(void);
void       Exit_SDL_App(void);
const char DesktopKeyMapping(const char code);
#endif 