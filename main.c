#include <stdio.h>
#include <SDL2/SDL.h>

#include "src/App/AppImpl.h"
#include "src/Chip8/CC8_Api.h"

#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH  32
#define PROGRAM_PATH  "/home/dev/repos/chip-8-binaries/1-chip8-logo.ch8" //PUT YOUR EXECUTABLE PATH HERE...

CC8_Machine * context;

//5x8 bitmap font
const uint8_t font_bitmap[] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,  // "0"
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
	0xF0, 0x80, 0xF0, 0x80, 0x80   // "F"
	};


void DrawCC8BitMapFont(uint8_t index, unsigned int* pixels, int x, int y){
    uint8_t gylphIndex = 0;
    uint8_t byteCount = 0;

    //5 wide bytes fonts
    for (gylphIndex = index * 5,byteCount = 0 ; gylphIndex < (index * 5)+5; gylphIndex++, byteCount++)
    {
        for (int bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            //This renders propperly the font !!:) 
            //formula: (y + x_offset) * SCREEN_HEIGHT + (y_offset + x)
            pixels[ (y + byteCount) * SCREEN_HEIGHT + (bitIndex + x)] = ((font_bitmap[gylphIndex] << bitIndex) & 0x80) == 0x80 ? 0xFFFFFFFF : 0X00000000;
        }    
    }
}

void BitmapTest(unsigned int* pixels)
{
    //This renders propperly the font !!:)
    for (int j = 0, charIndex = 0; j < 2; j++)
    {
        for (int i = 0; i < 8; i++)
            DrawCC8BitMapFont(charIndex++, pixels, i * 6, j * 8);
    }
}

void OnStep(unsigned int* pixels)
{
    //TODO Fix code below to render the contents of the vram
    //BitmapTest(pixels) //WORKING RENDERING REFERENCE!!!
    //TODO: Test this code below
    for (int i = 0; i < SCREEN_HEIGHT; i++) 
    {
        for (int j = 0; j < SCREEN_WIDTH; j++) 
        {
            //formula: (y + x_offset) * SCREEN_HEIGHT + (y_offset + x)
            for (int bitIndex = 0; bitIndex < 8; bitIndex++)
            {
                uint8_t vramLocation = context->VRAM[(i / CHIP_8_VERTICAL_BIT_PAGE_SIZE) * CHIP_8_VRAM_WIDTH + j];
                unsigned int pixel = (( vramLocation << bitIndex) & 0x80) == 0x80 ? CHIP_8_FOREGROUND_DISPLAY_COLOR : CHIP_8_BACKGROUND_DISPLAY_COLOR;
                pixels[i * SCREEN_HEIGHT + (j + bitIndex)] = pixel;
            }
        }
    }
}

void OnInputAction(const char code)
{
    printf("Key pressed %c\n", code);
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
    }
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
        context->KEYBOARD = 0;//todo: check if the reset of the keyboard state is needed
    }

    emulator->QuitProgram();
    chip8App->Exit(); 
}