#include <gtest/gtest.h>
//TEST ROOMS EMULATION REFERENCES:
//https://github.com/Hacktix/BullyGB/wiki
//http://blargg.8bitalley.com/parodius/gb-tests/

// #define TEST_ROOM_PATH "../../../ROMS/GameBoy/bully.gb"
#define TEST_ROOM_PATH "../../../ROMS/GameBoy/blargg-ld_r_r.gb"

extern "C" 
{
    #include <minemu.h>
    #include <GameBoy.h>
}

TEST(GameBoy_CPU, opcodeTest)
{
    Emulation *emulator;
    SystemContext *emulationCtx;

    long programSize = 0;
    long executionCount = 0;
    bool executionStatus = true;

    emulator = &GameBoyEmulator;
    MNE_New(emulationCtx, 1, SystemContext);

    // Initialize the emualtion api
    emulator->SetEmulationContext((void *) emulationCtx);
    emulator->Initialize(NULL, NULL);

    // Load ROM into memory starting from (0x0000)
    programSize = emulator->LoadProgram(TEST_ROOM_PATH);
    executionStatus = programSize > 0;
    
    // Program size is just an reference for max execution limit (thus due to data in the code...)
    for (; executionCount < programSize; executionCount++)
    {
        // Step emulation
        emulator->TickEmulation();

        //This should be in a different thread but for testing is fine... (right?)
        emulator->TickTimers();
        
        // Check if processed op code was executed fine
        if (emulationCtx->registers->INSTRUCTION == GB_INVALID_INSTRUCTION)
        {
            executionStatus = false;
            break;
        }
    }

    // Dispose emulation resources here..
    emulator->QuitProgram();

    MNE_Log("Instructions executed [%li] of [%li]\n", executionCount, programSize);
    EXPECT_TRUE(executionStatus);
}