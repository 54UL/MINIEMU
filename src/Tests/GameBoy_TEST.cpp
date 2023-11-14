#include <gtest/gtest.h>

// TEST ROOMS EMULATION REFERENCES:
// https://github.com/Hacktix/BullyGB/wiki
// http://blargg.8bitalley.com/parodius/gb-tests/

// #define TEST_ROOM_PATH "../../../ROMS/GameBoy/blargg-ld_r_r.gb"

extern "C"
{
#define GB_DEBUG
#include <minemu.h>
#include <GameBoy.h>
}

// 8-BIT LOAD INSTRUCTIONS TEST to implement...

// Load value 0x34 into register B
const uint8_t loadB[] = {0x06, 0x34};

// Load value 0x56 into register C
const uint8_t loadC[] = {0x0E, 0x56};

// Load value 0x78 into register D
const uint8_t loadD[] = {0x16, 0x78};

// Load value 0x9A into register E
const uint8_t loadE[] = {0x1E, 0x9A};

// Load value 0xBC into register H
const uint8_t loadH[] = {0x26, 0xBC};

// Load value 0xDE into register L
const uint8_t loadL[] = {0x2E, 0xDE};

// Copy value from B to A
const uint8_t copyAToB[] = {0x78};

// Copy value from D to C
const uint8_t copyCToD[] = {0x4A};

// Copy value from H to E
const uint8_t copyEToH[] = {0x5C};

// Copy value from A to L
const uint8_t copyLToA[] = {0x6F};

// Load value at address HL into A
const uint8_t loadAFromHL[] = {0x7E};

// Load value at address DE into B
const uint8_t loadBFromDE[] = {0x1A};

// Store value in B at address HL
const uint8_t storeBAtHL[] = {0x70};

// Store value in C at address DE
const uint8_t storeCAtDE[] = {0x41};

// Load value at address HL+1 into A
const uint8_t loadAFromHLPlus1[] = {0x86, 0x01};

// Load value at address DE-2 into B
const uint8_t loadBFromDEMinus2[] = {0x56, 0xFE};

// Store value in C at address HL+3
const uint8_t storeCAtHLPlus3[] = {0x71, 0x03};

// Store value in D at address DE-4
const uint8_t storeDAtDEMinus4[] = {0x51, 0xFC};

// Store value 0xEF at address HL
const uint8_t storeEFAtHL[] = {0x36, 0xEF};

// Store value 0xCD at address DE
const uint8_t storeCDAtDE[] = {0x12, 0xCD};


bool loadATest(Emulation *emulator, EmulationState *emulationCtx)
{
    // Load value 0x12 into register A -> LD A,r8

    // 
    const uint8_t loadA[] = {0x3E, 0x12};
    const long programSize = sizeof(loadA);

    bool executionStatus = true;

    // From the start of the program, later on it will have to be pc...
    for (int i = 0; i < programSize; i++)
    {
        emulationCtx->memory[i] = loadA[i];
    }

    // Step emulation
    emulator->TickEmulation();

    // Check if processed op code was executed fine
    executionStatus = emulationCtx->registers->INSTRUCTION != GB_INVALID_INSTRUCTION;

    // Check opcode operation was ok...
    executionStatus = emulationCtx->registers->CPU[GB_AF_OFFSET] >> 8 == 0x0012;

    return executionStatus;
}


TEST(GameBoy_CPU, opcodeTest)
{
    Emulation *emulator;
    EmulationState *emulationCtx;
    bool executionStatus = true;

    long instructionsExecuted = 0;

    emulator = &GameBoyEmulator;
    MNE_New(emulationCtx, 1, EmulationState);

    // Initialize the emualtion api
    emulator->SetEmulationContext((void *)emulationCtx);
    emulator->Initialize(NULL, NULL);

    // loadA test
    executionStatus = loadATest(emulator, emulationCtx);

    // Dispose emulation resources here..
    emulator->QuitProgram();

    EXPECT_TRUE(executionStatus);
}