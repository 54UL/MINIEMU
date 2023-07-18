#include "CC8_Emulator.h"

#include <stdlib.h>
#include <stdio.h>

static CC8_Machine *s_currentChipCtx = NULL;
static InstructionSet s_currentInstructions;

const uint8_t CC8_DEFAULT_FONT[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // "0"
    0x20, 0x60, 0x20, 0x20, 0x70, // "1"
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // "2"
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // "3"
    0x90, 0x90, 0xF0, 0x10, 0x10, // "4"
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // "5"
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // "6"
    0xF0, 0x10, 0x20, 0x40, 0x40, // "7"
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // "8"
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // "9"
    0xF0, 0x90, 0xF0, 0x90, 0x90, // "A"
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // "B"
    0xF0, 0x80, 0x80, 0x80, 0xF0, // "C"
    0xE0, 0x90, 0x90, 0x90, 0xE0, // "D"
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // "E"
    0xF0, 0x80, 0xF0, 0x80, 0x80  // "F"
};

// TODO:MOVE TO A PROPPER HEADER FILE called utils or such
void HexDump(uint8_t *buffer, size_t size)
{
    // Print header
    printf("Hex dump:\n");
    printf("---------------------------------------------------------------\n");
    printf("Offset |                         Hexadecimal                   \n");
    printf("-------|-------------------------------------------------------\n");

    // Print buffer contents in hexadecimal format with ASCII representation
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i += 16)
    {
        // Print offset
        printf("%06X | ", i);

        // Print hexadecimal values
        for (j = i; j < i + 16 && j < size; j++)
        {
            printf("%02X ", buffer[j]);
        }
        printf("\n");
    }

    // Print footer
    printf("-----------------------------------------------------------------\n");
}

void CC8_DebugMachine(CC8_Machine *machine, uint8_t enable)
{
    if (!enable)
        return;

    printf("| %-10s | %-10s |\n", "Name", "Value");
    printf("|------------|------------|\n");
    printf("| %-10s | %-#10x |\n", "RAM", (unsigned int)machine->RAM);
    printf("| %-10s | %-#10x |\n", "V", (unsigned int)machine->V);
    printf("| %-10s | %-#10x |\n", "SOUND", (unsigned int)machine->SOUND);
    printf("| %-10s | %-#10x |\n", "DELAY", (unsigned int)machine->DELAY);
    printf("| %-10s | %-#10x |\n", "I", (unsigned int)machine->I);
    printf("| %-10s | %-#10x |\n", "PC", (unsigned int)machine->PC);
    printf("| %-10s | %-#10x |\n", "SP", (unsigned int)machine->SP);
    printf("| %-10s | %-#10x |\n", "STACK", (unsigned int)machine->STACK);
    printf("| %-10s | %-#10x |\n", "VRAM", (unsigned int)machine->VRAM);
}

void CC8_BuildInstructionLUT()
{
    s_currentInstructions.Assign(0x00,NULL);
    s_currentInstructions.Assign(0x00,NULL);
}

void CC8_LoadProgram(const char *filePath)
{
    FILE *file = fopen(filePath, "rb");
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filePath);
        return;
    }

    // Get the size of the file
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    // Allocate a buffer for reading the file
    uint8_t *buffer = (uint8_t *)calloc(1, file_size + 1);
    size_t bytes_read = fread(buffer, 1, file_size, file);
    s_currentChipCtx->PROGRAM_SIZE = bytes_read;

    // LOAD PROGRAM AND FONT INTO RAM
    const size_t font_addr_start = 0x000; // The first thing in memory is the font
    const size_t boot_addr_start = 0x200; // 512

    uint16_t addr = 0;
    uint16_t loop_index = 0;

    for (addr = boot_addr_start; (addr < boot_addr_start + bytes_read); addr++)
    {
        s_currentChipCtx->RAM[addr] = buffer[loop_index++];
    }

    s_currentChipCtx->PC = boot_addr_start;

    loop_index = 0;
    printf("Loaded font size: %i\n", sizeof(CC8_DEFAULT_FONT));
    for (addr = font_addr_start; (addr < font_addr_start + sizeof(CC8_DEFAULT_FONT)); addr++)
    {
        s_currentChipCtx->RAM[font_addr_start + addr] = CC8_DEFAULT_FONT[loop_index++];
    }

    // Print the buffer (TODO:addd flag to print this thing)
    // HexDump(buffer, bytes_read);

    // Clean up resources
    free(buffer);
    fclose(file);
}

void CC8_QuitProgram()
{
    if (s_currentChipCtx != NULL)
        free(s_currentChipCtx);
}

void CC8_Step(uint16_t opcode)
{
    InstructionContext ctx;

    // Decode instruction
    ctx->x = (opcode >> 8) & 0x0F;
    ctx->y = (opcode >> 4) & 0x0F;
    ctx->nnn = opcode & 0x0FFF;
    ctx->kk = opcode & 0x00FF;
    ctx->n = opcode & 0x000F;
    
    //Fetch and execute opcode from LUT
    
    // Fetch and execute
    switch (opcode & 0xF000)
    {
    case 0x0000:
        switch (opcode & 0x00FF)
        {
        case 0x00E0:
            printf("CLS\n");
            CC8_CLS();
            break;

        case 0x00EE:
            printf("RET\n");
            CC8_RET();
            break;

        case 0x0000:
            break;

        default:
            printf("Unknow sub-instruction %06X\n", opcode & 0x00FF);
        }
        break;

    case 0x1000:
        printf("JMP 0x%03X\n", nnn);
        CC8_JMP(nnn);
        break;

    case 0x2000:
        printf("CALL 0x%03X\n", nnn);
        CC8_CALL(nnn);
        break;

    case 0x3000:
        printf("SE V%i, 0x%02X\n", x, kk);
        CC8_SE_VX_BYTE(x, kk);
        break;

    case 0x4000:
        printf("SNE V%i, 0x%02X\n", x, kk);
        CC8_SNE_VX_BYTE(x, kk);
        break;

    case 0x5000:
        printf("SE V%i, V%i\n", x, y);
        CC8_SE_VX_VY(x, y);
        break;

    case 0x6000:
        printf("LD_VX_BYTE V%i, %i\n", x, kk);
        CC8_LD_VX_BYTE(x, kk);
        break;

    case 0x7000:
        printf("ADD V%i, %i\n", x, kk);
        CC8_ADD_VX_BYTE(x, kk);
        break;

    case 0x8000:
        switch (opcode & 0x000F)
        {
        case 0x0000:
            printf("LD V%i, V%i\n", x, y);
            CC8_LD_VX_VY(x, y);
            break;

        case 0x0001:
            printf("OR V%i, V%i\n", x, y);
            CC8_OR_VX_VY(x, y);
            break;

        case 0x0002:
            printf("AND V%i, V%i\n", x, y);
            CC8_AND_VX_VY(x, y);
            break;

        case 0x0003:
            printf("XOR V%i, V%i\n", x, y);
            CC8_XOR_VX_VY(x, y);
            break;

        case 0x0004:
            printf("ADD V%i, V%i\n", x, y);
            CC8_ADD_VX_VY(x, y);
            break;

        case 0x0005:
            printf("SUB V%i, V%i\n", x, y);
            CC8_SUB_VX_VY(x, y);
            break;

        case 0x0006:
            printf("SHR V%i, V%i\n", x, y);
            CC8_SHR_VX_VY(x, y);
            break;

        case 0x0007:
            printf("SUBN V%i, V%i\n", x, y);
            CC8_SUBN_VX_VY(x, y);
            break;

        case 0x000E:
            printf("SHL V%i, V%i\n", x, y);
            CC8_SHL_VX_VY(x, y);
            break;

        default:

            printf("Unknow sub-instruction %06X\n", opcode & 0x000F);
        }
        break;

    case 0x9000:
        printf("SNE V%i, V%i\n", x, y);
        CC8_SNE_VX_VY(x, y);
        break;

    case 0xA000:
        printf("LD I, %i\n", nnn);
        CC8_LD_I_ADDR(nnn);
        break;

    case 0xB000:
        printf("JP V0, 0x%03X\n", nnn);
        CC8_JP_V0_ADDR(nnn);
        break;

    case 0xC000:
        printf("RND V%i, 0x%02X\n", x, kk);
        CC8_RND_VX_BYTE(x, kk);
        break;

    case 0xD000:
        printf("DRW v[%i], v[%i], %i\n", s_currentChipCtx->V[x], s_currentChipCtx->V[y], n);
        CC8_DRW_VX_VY_NIBBLE(x, y, n);
        break;

    case 0xE000:
        switch (opcode & 0x00FF)
        {
        case 0x9E:
            printf("SKP V%i\n", x);
            CC8_SKP_VX(x);
            break;

        case 0xA1:
            printf("SKNP V%i\n", x);
            CC8_SKNP_VX(x);
            break;

        default:
            printf("Unknow sub-instruction %06X\n", opcode & 0x00FF);
        }
        break;

    case 0xF000:
        switch (opcode & 0x00FF)
        {
        case 0x07:
            printf("LD V%i, DT\n", x);
            CC8_LD_VX_DT(x);
            break;

        case 0x0A:
            printf("LD V%i, K\n", x);
            CC8_LD_VX_K(x);
            break;

        case 0x15:
            printf("LD DT, V%i\n", x);
            CC8_LD_DT_VX(x);
            break;

        case 0x18:
            printf("LD ST, V%i\n", x);
            CC8_LD_ST_VX(x);
            break;

        case 0x1E:
            printf("ADD I, V%i\n", x);
            CC8_ADD_I_VX(x);
            break;

        case 0x29:
            printf("LD F, V%i\n", x);
            CC8_LD_F_VX(x);
            break;

        case 0x33:
            printf("LD B, V%i\n", x);
            CC8_LD_B_VX(x);
            break;

        case 0x55:
            printf("LD [I], V%i\n", x);
            CC8_LD_I_VX(x);
            break;

        case 0x65:
            printf("LD V%i, [I]\n", x);
            CC8_LD_VX_I(x);
            break;

        default:
            printf("Unknow sub-instruction %06X\n", opcode & 0x00FF);
        }
        break;

    default:
        printf("Unknow instruction opcode: %06X\n", opcode);
    }
}

void CC8_TickDelayTimer()
{
    if (s_currentChipCtx->DELAY != 0)
        s_currentChipCtx->DELAY--;
}

int CC8_TickEmulation()
{
    // CC8_DebugMachine(s_currentChipCtx, 1);
    // CC8_TickDelayTimer(); // TODO: FIX TIMING ISSUE (PUT THIS IN A SEPARATE THREAD)

    uint8_t higherByte = s_currentChipCtx->RAM[s_currentChipCtx->PC];
    uint8_t lowerByte = s_currentChipCtx->RAM[s_currentChipCtx->PC + 1];
    uint16_t value16 = (higherByte << 8) | lowerByte;

    CC8_Step(value16);

    s_currentChipCtx->PC += 2;
    return 1;
}

void CC8_SetKeyboardValue(uint8_t key)
{
    s_currentChipCtx->KEYBOARD = key;
}

void CC8_SetEmulationContext(CC8_Machine *context)
{
    s_currentChipCtx = context;
}