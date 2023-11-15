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

bool LoadTests8B(const Emulation *emulator, const EmulationState *emulationCtx);
bool RunProgram(const Emulation *emulator, const EmulationState *emulationCtx, const uint8_t *programArray, const uint16_t programLength);

bool LoadTests8B(const Emulation *emulator, const EmulationState *emulationCtx)
{
    bool executionStatus = true;
    constexpr uint8_t testValue = 0x12;
    const uint8_t loadA[] = {0x3E, testValue};
    const uint8_t loadB[] = {0x06, testValue};
    const uint8_t loadC[] = {0x0E, testValue};
    const uint8_t loadD[] = {0x16, testValue};
    const uint8_t loadE[] = {0x1E, testValue};

    // Run the program 
    executionStatus = RunProgram(emulator, emulationCtx, loadA, sizeof(loadA));

    // Check the program result
    executionStatus = emulationCtx->registers->CPU[GB_AF_OFFSET] >> 8 == 0x0012;

    return executionStatus;
}

bool RunProgram(const Emulation *emulator, const EmulationState *emulationCtx, const uint8_t *programArray, const uint16_t programLength)
{
    bool executionStatus = true;

    // From the start of the program, later on it will have to be pc...
    const uint16_t pos = emulationCtx->registers->PC;

    // Copy program into current pc position (just for testing...)
    for (int i = pos; i < (pos + programLength); i++)
    {
        emulationCtx->memory[i] = programArray[i];
    }

    // Process instructions...
    for (int i = 0; i < programLength; i++)
    {
        // Step emulation
        emulator->TickEmulation();

         // Check if processed op code was executed fine
        executionStatus = emulationCtx->registers->INSTRUCTION != GB_INVALID_INSTRUCTION;

        if (executionStatus) break;
    }

    return executionStatus;
}

TEST(GameBoy_CPU, opcodeTest)
{
    const Emulation *emulator = &GameBoyEmulator;;
    const EmulationState *emulationCtx;
    bool executionStatus = false;
    long instructionsExecuted = 0;

    MNE_New(emulationCtx, 1, EmulationState);

    // Initialize the emualtion api
    emulator->SetEmulationContext((void *)emulationCtx);
    emulator->Initialize(NULL, NULL);

    // 8 Bit load instructions
    executionStatus = LoadTests8B(emulator, emulationCtx);

    // Dispose emulation resources here..
    emulator->QuitProgram();

    EXPECT_TRUE(executionStatus);
}