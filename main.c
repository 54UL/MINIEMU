#include <stdio.h>
#include <SDL2/SDL.h>

#include "src/App/AppImpl.h"
#include "src/Chip8/CC8_Api.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH  64

#define PROGRAM_PATH  "/home/dev/repos/chip8-roms/games/Space Invaders [David Winter].ch8" //PUT YOUR EXECUTABLE PATH HERE...

CC8_Machine * context;

void OnStep(unsigned int* pixels)
{
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            int byteIndex = (i * SCREEN_WIDTH + (j / 8));
            int bitIndex = j % 8;
            uint8_t vramByte = context->VRAM[byteIndex];
            uint8_t vramBit = (vramByte >>  bitIndex) & 0x1;

            pixels[i * SCREEN_WIDTH + j] = vramBit ? CHIP_8_FOREGROUND_DISPLAY_COLOR : CHIP_8_BACKGROUND_DISPLAY_COLOR;
        }
    }
}

void OnInputAction(const char code)
{
    // printf("Key pressed %c\n", code);

    switch (code) 
    {
        //1 2 3 C
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
        //4 5 6 D
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
        //7 8 9 E
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
        //A 0 B F
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
    // SDL_Delay(32);
}

int main(int argc, char** argv)
{
    App * chip8App = &TinySDLApp;
    CC8_Core * emulator = &Chip8Emulator;
    context = calloc(1, sizeof(CC8_Machine)); //Initialize machine state

    chip8App->Init(SCREEN_WIDTH, SCREEN_HEIGHT, OnInputAction);

    emulator->SetEmulationContext(context);
    emulator->LoadProgram(PROGRAM_PATH);

    while(chip8App->Step(OnStep) && emulator->TickEmulation())
    {
        // SDL_Delay(1);// 16 ms

    }

    emulator->QuitProgram();
    chip8App->Exit(); 
}