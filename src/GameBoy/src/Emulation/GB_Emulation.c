#include <Emulation/GB_Emulation.h>
#include <Emulation/GB_Instruction.h>

#include <CPU/GB_Instructions.h>
#include <string.h>

static const GameBoyInstruction s_gb_instruction_set[GB_INSTRUCTION_SET_LENGHT] =
{
    //-------------MASK----OPCODE-CYCLES-HANDLER
    GB_INSTRUCTION(0x00FF, 0x0040, 0X04, GB_LD_R_R),
    GB_INSTRUCTION(0x000F, 0x0006, 0X08, GB_LD_R_N)
};

uint8_t GB_Initialize(int argc, const char ** argv)
{

}

long GB_LoadProgram(const char *filePath)
{

}

void GB_QuitProgram()
{
}

void GB_TickTimers()
{

}

int GB_TickEmulation()
{
    // Implement CPU step function that take into account prefetch cycle (before executing an instruction fetch another one then execute both in order)
}

void GB_SetEmulationContext(const void *context)
{
}

void GB_PopulateMemory(const uint8_t *buffer, size_t bytesRead)
{

}
