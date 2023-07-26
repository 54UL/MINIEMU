#include <stdio.h>
#include <SDL2/SDL.h>

#include "src/App/AppImpl.h"
#include "src/Chip8/CC8_Api.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64

App *app;
CC8_Core *emulator;
CC8_Machine *context;

// App
void OnRender(unsigned int *pixels);
void OnInputAction(const char code);

// Shell
void StartEmulation(void * data);
void StopEmulation(void * data);
void QuitEmulation(void * data);

int main(int argc, char **argv)
{
    Uint32 last_update_time;
    Uint32 last_update_time_timers;

    app = &TinySDLApp;
    emulator = &Chip8Emulator;

    // Configure emulator shell actions (if available)
    EmulatorUI.ShellAction(Start, StartEmulation);
    EmulatorUI.ShellAction(Stop, StopEmulation);
    EmulatorUI.ShellAction(Quit, QuitEmulation);

    // App and emulator initialization
    app->Init(SCREEN_WIDTH, SCREEN_HEIGHT, OnInputAction, &EmulatorUI);
    uint8_t status = 1 ;

    // Main loop (render pass)
    while (status)
    {
        uint32_t current_time = SDL_GetTicks();
        uint32_t delta_time = current_time - last_update_time;
        uint32_t delta_time_timers = current_time - last_update_time_timers;

        if (delta_time >= 2 ) // CPU FREQ
        {
            status = app->Render(OnRender);

            if (EmulatorUI.GetState() == Running)
            {
                emulator->TickEmulation();

                if (delta_time_timers > 16) // TIMERS FREQ
                {
                    emulator->TickDelayTimer();
                    last_update_time_timers = current_time;
                }
            }
            last_update_time = current_time;
        }
    }

    emulator->QuitProgram();
    app->Exit();
}

void OnRender(unsigned int *pixels)
{
    if (context == NULL) return;
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

void OnInputAction(const char code)
{
    if (context == NULL) return;
    context->KEYBOARD = code;
}

void StartEmulation(void * data)
{
    printf("StartEmulation: %s\n", (const char *) data);

    const ShellState sate = EmulatorUI.GetState();
    switch (sate)
    {
        case Running:
            EmulatorUI.SetState(Starting);
            emulator->QuitProgram();
            break;

        default:
            break;
    }
    
    context = calloc(1, sizeof(CC8_Machine));
    emulator->SetEmulationContext(context);

    if (emulator->LoadProgram((const char*) data))
    {
        EmulatorUI.SetState(Running);
    }
    else
    {
        EmulatorUI.SetState(Exception);
    }
}

void StopEmulation(void * data)
{
    printf("StopEmulation\n");
}

void QuitEmulation(void * data)
{
    printf("QuitEmulation\n");
}