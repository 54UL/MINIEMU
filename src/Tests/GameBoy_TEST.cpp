#include <gtest/gtest.h>
#define TEST_ROOM_PATH "../../../ROMS/GameBoy/opode_test.gb"

extern "C" 
{
    #include <minemu.h>
    #include <GameBoy.h>
}

TEST(GameBoy_CPU, opcodeTest)
{
    Emulation *emulator;
    GB_Registers *registers;

    long programSize = 0;
    long executionCount = 0;
    bool executionStatus = true;

    emulator = &GameBoyEmulator;
    MNE_New(registers, 1, GB_Registers);
    emulator->SetEmulationContext((void *) registers);
    programSize = emulator->LoadProgram(TEST_ROOM_PATH);
    executionStatus = programSize > 0;
    
    // Program size is just an reference for max execution limit (thus due to data in the code...)
    for (; executionCount < programSize; executionCount++)
    {
        // Step emulation
        emulator->TickEmulation();
        emulator->TickDelayTimer();
        
        // Check if processed op code was executed right testing against invalid opcode and nop (not expecting any of those)
        if (registers->INSTRUCTION == GB_INVALID_INSTRUCTION || registers->INSTRUCTION == 0)
        {
            executionStatus = false;
            break;
        }
    }

    emulator->QuitProgram();
    MNE_Log("Instructions executed [%li] of [%li]\n", executionCount, programSize);
    EXPECT_TRUE(executionStatus);
}