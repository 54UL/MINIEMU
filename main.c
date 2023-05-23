#include <stdio.h>
#include <SDL2/SDL.h>

#include "src/App/AppImpl.h"
#include "src/Chip8/CC8_Api.h"

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH  32
#define PROGRAM_PATH  "/home/dev/repos/chip-8-binaries/1-chip8-logo.ch8"

CC8_Machine * context;

const uint8_t CC8_DEFAULT_FONT[] = {0xF0, 0x90, 0x90, 0x90, 0xF0,  // "0"
									0x20, 0x60, 0x20, 0x20, 0x70,  // "1"
									0xF0, 0x10, 0xF0, 0x80, 0xF0,  // "2"
									0xF0, 0x10, 0xF0, 0x10, 0xF0,  // "3"
									0x90, 0x90, 0xF0, 0x10, 0x10,  // "4"
									0xF0, 0x80, 0xF0, 0x10, 0xF0,  // "5"
									0xF0, 0x80, 0xF0, 0x90, 0xF0,  // "6"
									0xF0, 0x10, 0x20, 0x40, 0x40,  // "7"
									0xF0, 0x90, 0xF0, 0x90, 0xF0,  // "8"
									0xF0, 0x90, 0xF0, 0x10, 0xF0,  // "9"
									0xF0, 0x90, 0xF0, 0x90, 0x90,  // "A"
									0xE0, 0x90, 0xE0, 0x90, 0xE0,  // "B"
									0xF0, 0x80, 0x80, 0x80, 0xF0,  // "C"
									0xE0, 0x90, 0x90, 0x90, 0xE0,  // "D"
									0xF0, 0x80, 0xF0, 0x80, 0xF0,  // "E"
									0xF0, 0x80, 0xF0, 0x80, 0x80}; // "F"

uint8_t  VRAM[SCREEN_WIDTH][SCREEN_HEIGHT];

void OnStep(unsigned int* pixels)
{
    // int i, j, index = 0;
    // // Iterate over the rows and columns of the 2D array
    // for (i = 0; i < SCREEN_HEIGHT; i++) {
    //     for (j = 0; j < SCREEN_WIDTH; j++) {
    //         // Copy the current element to the 1D array
    //         pixels[index] = context->VRAM[i][j] == 0xFF ? 0xFF0ff0ffF : 0x000000ff0;
    //         index++;
    //     }
    // }
    // pixels = 0xFF0ff0ffF;
    // drawTinyText("########!!!!!!!!!!!!!!!!!!!",10,10, pixels, 1);
     //testbed
    int width = 0;
    int heigth = 0;

    for (width = 0; width < SCREEN_WIDTH; width++)
    {
        for (heigth = 0; heigth < SCREEN_HEIGHT; heigth++)
        {
            
        }
    }
    //end testbed
}

void OnInputAction(const char code)
{
    printf("Key pressed %c\n", code);

    // switch (event.key.keysym.sym) 
    // {
    //     case SDLK_q:
    //         // Handle key A
    //         break;
    //     case SDLK_w:
    //         // Handle key B
    //         break;
    //     case SDLK_e:
    //         // Handle key C
    //         break;
    //     case SDLK_a:
    //         // Handle key P
    //         break;
    //     case SDLK_s:
    //         // Handle key Q
    //         break;
    //     case SDLK_d:
    //         // Handle key R
    //         break;
    // }
}



int main(int argc, char** argv)
{
   
    App * chip8App = &TinySDLApp;
    CC8_Core * emulator = &Chip8Emulator;
    context = calloc(1, sizeof(CC8_Machine)); //Initialize machine state

    chip8App->Init(SCREEN_HEIGHT, SCREEN_WIDTH);

    emulator->SetEmulationContext(context);
    emulator->LoadProgram(PROGRAM_PATH);

    while(chip8App->Step(OnStep, OnInputAction))
    {
        emulator->TickEmulation();
        SDL_Delay(200);
    }

    emulator->QuitProgram();
    chip8App->Exit(); 
}