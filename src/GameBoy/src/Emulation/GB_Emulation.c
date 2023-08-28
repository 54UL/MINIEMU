#include <Emulation/GB_Emulation.h>
#include <Emulation/GB_Instruction.h>

#include <CPU/GB_Instructions.h>
#include <string.h>
#include <minemu.h>

static SystemContext * s_systemContext;

static GameBoyInstruction s_gb_instruction_set[GB_INSTRUCTION_SET_LENGHT] =
{
    //-------------MASK----OPCODE-CYCLES-HANDLER
    GB_INSTRUCTION(0x00FF, 0x0040, 0X04, GB_LD_R_R),
    GB_INSTRUCTION(0x000F, 0x0006, 0X08, GB_LD_R_N)
};

uint8_t GB_Initialize(int argc, const char ** argv)
{
    MNE_New(s_systemContext->registers, 1, GB_Registers);
    MNE_New(s_systemContext->flags, 1, GB_FlagsReg);
    MNE_New(s_systemContext->memory, GB_MEMORY_SIZE, uint8_t);
}

long GB_LoadProgram(const char *filePath)
{
    return MNE_ReadFile(filePath, 0, GB_PopulateMemory);
}

void GB_PopulateMemory(const uint8_t *buffer, size_t bytesRead)
{
    //Initialize memory (CHECK IF IS POSIBLE TO MOVE THIS MEMORY MANAGEMENT OUT THIS FILE)
  

    //For development program is stored at 0x0000, when using the boot rom (bios) program should start at  0x1000
    uint16_t ramIndex = 0;// replace with 0x1000...
    uint16_t bufferIndex = 0;

    // TODO: add memory offset cond: (ramindex + 0x1000) < bytesRead
    for (; ramIndex < bytesRead; ramIndex++, bufferIndex++)
    {
        s_systemContext->memory[ramIndex] = buffer[bufferIndex];
    }

}

void GB_QuitProgram()
{
    MNE_Delete(s_systemContext->flags);
    MNE_Delete(s_systemContext->registers);
    MNE_Delete(s_systemContext->memory);
}

void GB_TickTimers()
{

}

int GB_TickEmulation()
{
    //TODO: Implement CPU step function that take into account prefetch cycle (before executing an instruction fetch another one then execute both in order)
    
    if (s_systemContext == NULL) return 0;

    // Fetch
    const uint8_t instr = s_systemContext->memory[s_systemContext->registers->PC++];
    GameBoyInstruction* fetchedInstruction = GB_FetchInstruction(instr);
    
    // Instruction execution
    if (fetchedInstruction != NULL)
    {
#ifdef GB_DEBUG
        MNE_Log(fetchedInstruction->handlerName, instr);
#endif
        s_systemContext->registers->INSTRUCTION = instr; // Stores executed opcode to check later if was running fine
        fetchedInstruction->handler(s_systemContext);
        //TODO: ADD BELOW DELTA TIME DELAY TO IMPLEMENT CLOCK CYCLES TIMING
    }
    else
    {
        s_systemContext->registers->INSTRUCTION = GB_INVALID_INSTRUCTION; // Invalidate last instruction entry
        MNE_Log("[INVALID INSTR]: %04X]\n", instr);
    }
}

GameBoyInstruction* GB_FetchInstruction(const uint8_t opcode)
{
    // Implement hashing!!!
    for (int  i = 0; i < 0XFF ; i++)
    {
        uint16_t opmask = (opcode & s_gb_instruction_set[i].mask);

        if ((opmask == s_gb_instruction_set[i].opcode))
        {
            return &s_gb_instruction_set[i];
        }
    }
    return NULL;
}

void GB_SetEmulationContext(const void *context)
{
    s_systemContext = (SystemContext*) context;
}
