#include <Emulation/GB_Emulation.h>
#include <Emulation/GB_Instruction.h>

#include <CPU/GB_Instructions.h>

static const GameBoyInstruction s_gb_instruction_set[GB_INSTRUCTION_SET_LENGHT] =
    {
        // MASK, OPCODE, CYCLES, HANDLER
        {0XFFFF, 0X00E0, 0X0004, (instructionFnPtrGb)GB_LD_R_R}
    };

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
}
void GB_SetEmulationContext(const void *context)
{
}
void GB_PopulateMemory(const uint8_t *buffer, size_t bytesRead)
{
}
