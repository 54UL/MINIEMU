
#ifndef APP_IMPL_H
#define APP_IMPL_H

#include "App.h"
#include "SDL_TinyAppImpl/SDL_TinyApp.h"
#include "UI/EmulatorShell.h"

//App implementation
App TinySDLApp = {
    .Init = Init_App,
    .Render = Step_SDL,
    .Reset = Reset_SDL,
    .Exit = Exit_SDL_App
};

EmulatorShell EmulatorUI = 
{
    .Init = EmuShell_Init,
    .UpdateFrame = EmuShell_UpdateFrame,
    .Shown = EmuShell_Shown,
    .OnInput = EmuShell_KeyPressed,
    .ShellAction = EmuShell_ShellAction
};

#endif