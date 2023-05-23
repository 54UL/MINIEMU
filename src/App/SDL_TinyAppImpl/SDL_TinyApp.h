#ifndef SDL_TINY_APP_H
#define SDL_TINY_APP_H

#include "../App.h"

//Function definitions
void    Init_SDL(uint16_t w, uint16_t h);
uint8_t Step_SDL(StepCallBack renderCallback, ActionCallback actionsCallback);
void    Reset_SDL(void);
void    Exit_SDL_App(void);

#endif 