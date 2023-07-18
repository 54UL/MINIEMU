#include <stdio.h>
#include <SDL2/SDL.h>

#include "src/App/AppImpl.h"
#include "src/Chip8/CC8_Api.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

App *app;
CC8_Core *emulator;
CC8_Machine *context;

void OnStep(unsigned int *pixels)
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            int byteIndex = (i * SCREEN_WIDTH + (j / 8));
            int bitIndex = j % 8;
            uint8_t vramByte = context->VRAM[byteIndex];
            uint8_t vramBit = (vramByte >> bitIndex) & 0x1;

            pixels[i * SCREEN_WIDTH + j] = vramBit ? CHIP_8_FOREGROUND_DISPLAY_COLOR : CHIP_8_BACKGROUND_DISPLAY_COLOR;
        }
    }
}

char lastCode;
void OnInputAction(const char code)
{
    switch (code)
    {
    // 1 2 3 C
    case SDLK_1:
        context->KEYBOARD = 0x01;
        break;
    case SDLK_2:
        context->KEYBOARD = 0x02;
        break;
    case SDLK_3:
        context->KEYBOARD = 0x03;
        break;
    case SDLK_4:
        context->KEYBOARD = 0x0C;
        break;
    // 4 5 6 D
    case SDLK_q:
        context->KEYBOARD = 0x04;
        break;
    case SDLK_w:
        context->KEYBOARD = 0x05;
        break;
    case SDLK_e:
        context->KEYBOARD = 0x06;
        break;
    case SDLK_r:
        context->KEYBOARD = 0x0D;
        break;
    // 7 8 9 E
    case SDLK_a:
        context->KEYBOARD = 0x07;
        break;
    case SDLK_s:
        context->KEYBOARD = 0x08;
        break;
    case SDLK_d:
        context->KEYBOARD = 0x09;
        break;
    case SDLK_f:
        context->KEYBOARD = 0x0E;
        break;
    // A 0 B F
    case SDLK_z:
        context->KEYBOARD = 0x0A;
        break;
    case SDLK_x:
        context->KEYBOARD = 0x00;
        break;
    case SDLK_c:
        context->KEYBOARD = 0x0B;
        break;
    case SDLK_v:
        context->KEYBOARD = 0x0F;
        break;
    case -100:
        context->KEYBOARD = 0xFF;
        break;
    }
    lastCode = code;
}

int main(int argc, char **argv)
{
    Uint32 last_update_time;

    app = &TinySDLApp;
    emulator = &Chip8Emulator;
    context = calloc(1, sizeof(CC8_Machine)); // Initialize machine state

    app->Init(SCREEN_WIDTH, SCREEN_HEIGHT, OnInputAction, &EmulatorUI);
    emulator->SetEmulationContext(context);

    while (app->Render(OnStep))
    {
        Uint32 current_time = SDL_GetTicks();
        Uint32 delta_time = current_time - last_update_time;

        //TODO: FIX TIMING ISSUES
        if (delta_time >= 1)
        {
            emulator->TickDelayTimer();
            emulator->TickEmulation();

            last_update_time = current_time;
        }
    }

    emulator->QuitProgram();
    app->Exit();
}