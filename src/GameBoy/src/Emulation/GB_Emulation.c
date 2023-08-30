#include <Emulation/GB_Emulation.h>
#include <Emulation/GB_Instruction.h>

#include <CPU/GB_Instructions.h>
#include <string.h>
#include <minemu.h>

static SystemContext * s_systemContext;

static GameBoyInstruction s_gb_instruction_set[GB_INSTRUCTION_SET_LENGHT] =
{
    //-------------MASK----OPCODE-HANDLER
    GB_INSTRUCTION(0x00FF, 0x0040, GB_LD_R_R),
    GB_INSTRUCTION(0x000F, 0x0006, GB_LD_R_N)
};

uint8_t GB_Initialize(int argc, const char ** argv)
{
    MNE_New(s_systemContext->registers, 1, GB_Registers);
    MNE_New(s_systemContext->memory, GB_MEMORY_SIZE, uint8_t);
}

long GB_LoadProgram(const char *filePath)
{
    return MNE_ReadFile(filePath, 0, GB_PopulateMemory);
}

void GB_PopulateMemory(const uint8_t *buffer, size_t bytesRead)
{
    //For development program is stored at 0x0000, when using the boot rom (bios) program should start at  0x1000
    uint16_t ramIndex = 0;// replace with 0x1000...
    uint16_t bufferIndex = 0;

    // TODO: add memory offset cond: (ramindex + 0x1000) < bytesRead
    for (; ramIndex < bytesRead; ramIndex++, bufferIndex++)
    {
        s_systemContext->memory[ramIndex] = buffer[bufferIndex];
    }
    //TODO: ADD RETURN TO CHECK 
}

void GB_QuitProgram()
{
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
    const uint8_t instr = s_systemContext->memory[s_systemContext->registers->PC++]; //TODO: CHANGE THIS FOR A BUS READ!!!
    
    GameBoyInstruction* fetchedInstruction = GB_FetchInstruction(instr);
    uint8_t clockCycles = 0;

    // Instruction execution
    if (fetchedInstruction != NULL)
    {

        if (fetchedInstruction->opcode != 0) // If opcode is 0 then is an NOP... 
        {
#ifdef GB_DEBUG
            MNE_Log(fetchedInstruction->handlerName, instr, s_systemContext->registers->PC);
#endif
            s_systemContext->registers->INSTRUCTION = instr; // Stores executed opcode to check later if was running fine
            clockCycles = fetchedInstruction->handler(s_systemContext);
           
            return 1; //TODO: returning 1 means no fucking nops executed...
        }
            //TODO: ADD BELOW DELTA TIME DELAY TO IMPLEMENT CLOCK CYCLES TIMING

         return 0;
    }
    else
    {
        s_systemContext->registers->INSTRUCTION = GB_INVALID_INSTRUCTION; // Invalidate last instruction entry
        MNE_Log("[INVALID INSTR]: %04X]\n", instr);
        return 0;
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
