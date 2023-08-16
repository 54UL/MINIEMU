#include <gtest/gtest.h>
#define TEST_ROOM_PATH "../../../ROMS/test_opcode.ch8"
#define BOOT_START 512

extern "C" 
{
    #include <minemu.h>
    #include <CC8_Chip8.h>
    #include <CC8_Instructions.h>
}

Emulation *emulator;
CC8_Memory *context;

TEST(Chip8InstructionsCheck, opcodeTest)
{
    long programSize = 0;
    long executionCount = 0;
    bool executionStatus = true;

    emulator = &Chip8Emulator;
    MNE_New(context, 1, CC8_Memory);
    emulator->SetEmulationContext((void *) context);
    programSize = emulator->LoadProgram(TEST_ROOM_PATH);
    executionStatus = programSize > 0;
    
    // Program size is just an reference for max execution limit (thus due to data in the code...)
    for (; executionCount < programSize; executionCount++)
    {
        // Step emulation
        emulator->TickEmulation();
        emulator->TickDelayTimer();
        
        // Check if processed op code was executed right testing against invalid opcode and nop (not expecting any of those)
        if (context->INSTRUCTION == CC8_INVALID_INSTRUCTION || context->INSTRUCTION == 0)
        {
            executionStatus = false;
            break;
        }
    }

    emulator->QuitProgram();
    MNE_Log("Instructions executed [%li] of [%li]\n", executionCount, programSize);
    EXPECT_TRUE(executionStatus);
}