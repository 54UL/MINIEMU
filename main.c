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

    app = &TinySDLApp;
    emulator = &Chip8Emulator;

    // Configure emulator shell actions (if available)
    EmulatorUI.ShellAction(ShellAction::Start, StartEmulation);
    EmulatorUI.ShellAction(ShellAction::Stop, StopEmulation);
    EmulatorUI.ShellAction(ShellAction::Quit, QuitEmulation);

    // App and emulator initialization
    emulator->SetEmulationContext(context);
    app->Init(SCREEN_WIDTH, SCREEN_HEIGHT, OnInputAction, &EmulatorUI);

    // Main loop (render pass)
    while (app->Render(OnRender) && EmulatorUI.GetState() == ShellState::Running)
    {
        uint32_t current_time = SDL_GetTicks();
        uint32_t delta_time = current_time - last_update_time;

        // TODO: FIX TIMING ISSUES
        // Emulator loop (cpu step)
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

void OnRender(unsigned int *pixels)
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

void OnInputAction(const char code)
{
    context->KEYBOARD = code;
}

void StartEmulation(void * data)
{
    printf("StartEmulation: %s\n", (const char *) data);

    const ShellState sate = EmulatorUI.GetState();
    switch (sate)
    {
        case ShellState::Running:
            EmulatorUI.SetState(ShellState::Starting);
            emulator->QuitProgram();
            break;
        default:
            break;
    }

    if (emulator->LoadProgram((const char*) data))
    {
        EmulatorUI.SetState(ShellState::Running);
    }
    else
    {
        EmulatorUI.SetState(ShellState::Exception);
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