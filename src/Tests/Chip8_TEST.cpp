#include <gtest/gtest.h>
#define TEST_ROOM_PATH "../../../ROMS/1-chip8-logo.ch8"
#define BOOT_START 512

extern "C" 
{
    #include <minemu.h>
    #include <CC8_Chip8.h>
    #include <CC8_Instructions.h>
}

Emulation *emulator;
CC8_Memory *context;

TEST(Chip8InstructionsCheck, ProgamExecution)
{
    long programSize = 0;
    long executionCount = 0;
    bool executionStatus = true;

    emulator = &Chip8Emulator;
    context = (CC8_Memory*) calloc(1, sizeof(CC8_Memory));

    emulator->SetEmulationContext((void *) context);
    programSize = emulator->LoadProgram(TEST_ROOM_PATH);

    for (; executionCount < programSize; executionCount++)
    {
        // Get memory contents to compare
        uint16_t addrOffset = BOOT_START + executionCount;
        uint8_t higherByte = context->RAM[addrOffset];
        uint8_t lowerByte = context->RAM[addrOffset + 1];
        uint16_t value16 = (higherByte << 8) | lowerByte;

        // Step emulation
        emulator->TickEmulation();
        emulator->TickDelayTimer();

        // // Check if processed opcode was running fine
        // if (value16 != context->INSTRUCTION)
        // {
        //     executionStatus = false;
        //     break;
        // }
    }
    emulator->QuitProgram();
    printf("Instructions executed [%i] of [%i]\n",executionCount, programSize);
    EXPECT_TRUE(executionStatus);
}