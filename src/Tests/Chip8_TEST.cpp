#include <gtest/gtest.h>
#define TEST_ROOM_PATH "../../../ROMS/1-chip8-logo.ch8"

extern "C" 
{
    #include <minemu.h>
    #include <CC8_Chip8.h>
    #include <CC8_Instructions.h>
}

Emulation *emulator;
CC8_Memory *context;

TEST(Chip8InstructionsCheck, RomTest)
{
    long programSize = 0;
    long executionCount = 0;
    emulator = &Chip8Emulator;
    context = (CC8_Memory*) calloc(1, sizeof(CC8_Memory));

    emulator->SetEmulationContext((void *) context);
    programSize = emulator->LoadProgram(TEST_ROOM_PATH);

    for (; executionCount < programSize; executionCount++)
    {
        emulator->TickEmulation();
        emulator->TickDelayTimer();
    }

    emulator->QuitProgram();
    printf("Relative pc:%i\n", executionCount);
    EXPECT_TRUE(programSize >= 0x100);
    EXPECT_TRUE(executionCount >= 0x100);
}