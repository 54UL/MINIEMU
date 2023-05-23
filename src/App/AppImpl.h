
#ifndef APP_IMPL_H
#define APP_IMPL_H


#include "App.h"
#include "SDL_TinyAppImpl/SDL_TinyApp.h"

//App implementation
App TinySDLApp = {
    .Init = Init_SDL,
    .Step = Step_SDL,
    .Reset = Reset_SDL,
    .Exit = Exit_SDL_App
};


#endif