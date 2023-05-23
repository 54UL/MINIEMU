#include "CC8_Emulator.h"

#include <stdlib.h>
#include <stdio.h>

static CC8_Machine *s_currentChipCtx = NULL;

#define CC8_FILE_PROGRAM_BUFFER_SIZE 4096

const uint8_t CC8_DEFAULT_FONT[] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,  // "0"
	0x20, 0x60, 0x20, 0x20, 0x70,  // "1"
	0xF0, 0x10, 0xF0, 0x80, 0xF0,  // "2"
	0xF0, 0x10, 0xF0, 0x10, 0xF0,  // "3"
	0x90, 0x90, 0xF0, 0x10, 0x10,  // "4"
	0xF0, 0x80, 0xF0, 0x10, 0xF0,  // "5"
	0xF0, 0x80, 0xF0, 0x90, 0xF0,  // "6"
	0xF0, 0x10, 0x20, 0x40, 0x40,  // "7"
	0xF0, 0x90, 0xF0, 0x90, 0xF0,  // "8"
	0xF0, 0x90, 0xF0, 0x10, 0xF0,  // "9"
	0xF0, 0x90, 0xF0, 0x90, 0x90,  // "A"
	0xE0, 0x90, 0xE0, 0x90, 0xE0,  // "B"
	0xF0, 0x80, 0x80, 0x80, 0xF0,  // "C"
	0xE0, 0x90, 0x90, 0x90, 0xE0,  // "D"
	0xF0, 0x80, 0xF0, 0x80, 0xF0,  // "E"
	0xF0, 0x80, 0xF0, 0x80, 0x80   // "F"
	};

// TODO:MOVE TO A PROPPER HEADER FILE called utils or such
void HexDump(uint8_t * buffer, size_t size)
{
	// Print header
	printf("Hex dump:\n");
	printf("-----------------------------------------------------------------\n");
	printf("Offset |                         Hexadecimal                    | ASCII\n");
	printf("-------|--------------------------------------------------------|------\n");

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
			printf("%02X ", (unsigned char) buffer[j]);
		}

		// Print spaces to align columns
		for (j = 0; j < 3 * (16 - (size - i)); j++)
		{
			printf(" ");
		}
		printf("\n");
	}

	// Print footer
	printf("-----------------------------------------------------------------\n");
}

void CC8_DebugMachine(CC8_Machine *machine) 
{
    printf("| %-10s | %-10s |\n", "Name", "Value");
    printf("|------------|------------|\n");
    printf("| %-10s | %-#10x |\n", "RAM", (unsigned int) machine->RAM);
    printf("| %-10s | %-#10x |\n", "V", (unsigned int) machine->V);
    printf("| %-10s | %-#10x |\n", "SOUND", (unsigned int) machine->SOUND);
    printf("| %-10s | %-#10x |\n", "DELAY", (unsigned int) machine->DELAY);
    printf("| %-10s | %-#10x |\n", "I", (unsigned int) machine->I);
    printf("| %-10s | %-#10x |\n", "PC", (unsigned int) machine->PC);
    printf("| %-10s | %-#10x |\n", "SP", (unsigned int) machine->SP);
    printf("| %-10s | %-#10x |\n", "STACK", (unsigned int) machine->STACK);
    printf("| %-10s | %-#10x |\n", "VRAM", (unsigned int) machine->VRAM);
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
	uint8_t *buffer = (uint8_t *)calloc(1, CC8_FILE_PROGRAM_BUFFER_SIZE);
	size_t bytes_read = fread(buffer, 1, file_size, file);

	// LOAD PROGRAM AND FONT INTO RAM
	const size_t boot_addr_start = 0x200; // 512
	const size_t font_addr_start = 0x000; // 512

	uint16_t addr = 0;
	uint16_t loop_index = 0;

	for (addr = boot_addr_start; (addr < boot_addr_start + CHIP_8_MAX_RAM); addr++)
	{
		s_currentChipCtx->RAM[boot_addr_start + addr] = buffer[loop_index++];
	}

	loop_index = 0;
	printf("Loaded font size: %i", sizeof(CC8_DEFAULT_FONT));
	for (addr = font_addr_start; (addr < font_addr_start + sizeof(CC8_DEFAULT_FONT)); addr++)
	{
		s_currentChipCtx->RAM[font_addr_start + addr] = CC8_DEFAULT_FONT[loop_index++];
	}
	
	// Print the buffer (TODO:addd flag to print this thing)
	//HexDump(buffer, bytes_read);
	// Clean up resources
	free(buffer);
	fclose(file);
}

void CC8_QuitProgram()
{
	if (s_currentChipCtx != NULL)
		free(s_currentChipCtx);
}

void CC8_Execute(uint16_t opcode)
{
	int x = (opcode >> 8) & 0x0F;
	int y = (opcode >> 4) & 0x0F;
	int nnn = opcode & 0x0FFF;
	int kk = opcode & 0x00FF;
	int n = opcode & 0x000F;

	switch (opcode & 0xF000)
	{
	case 0x0000:
		switch (opcode & 0x00FF)
		{
		case 0x00E0:
			CC8_CLS();
			break;
		case 0x00EE:
			CC8_RET();
			break;
		default:
			// Unknown instruction
			break;
		}
		break;
	case 0x1000:
		CC8_JMP(nnn);
		break;
	case 0x2000:
		CC8_CALL(nnn);
		break;
	case 0x3000:
		CC8_SE_VX_BYTE(x, kk);
		break;
	case 0x4000:
		CC8_SNE_VX_BYTE(x, kk);
		break;
	case 0x5000:
		CC8_SE_VX_VY(x, y);
		break;
	case 0x6000:
		CC8_LD_VX_BYTE(x, kk);
		break;
	case 0x7000:
		CC8_ADD_VX_BYTE(x, kk);
		break;
	case 0x8000:
		switch (opcode & 0x000F)
		{
		case 0x0000:
			CC8_LD_VX_VY(x, y);
			break;
		case 0x0001:
			CC8_OR_VX_VY(x, y);
			break;
			break;
		}
		break;

	case 0x9000:
		break;

	case 0xA000:
		break;

	case 0xB000:
		break;

	case 0xC000:
		break;

	case 0xD000:
		break;

	case 0xE000:
		break;

	case 0xF000:
		break;
	}
}

void CC8_TickEmulation()
{
	CC8_DebugMachine(s_currentChipCtx);


	uint8_t lowerByte = s_currentChipCtx->RAM[s_currentChipCtx->PC];
	uint8_t higherByte = s_currentChipCtx->RAM[s_currentChipCtx->PC + 1];
	uint16_t value16 = ((uint16_t)higherByte << 8) | lowerByte;
	CC8_Execute(value16);
	s_currentChipCtx->PC++;
}

void CC8_SetEmulationContext(CC8_Machine *context)
{
	s_currentChipCtx = context;
}

// ########## CHIP 8 INSTRUCTION SET IMPLEMENTATION
void CC8_CLS()
{
}
void CC8_RET()
{
}
void CC8_JMP(uint16_t addr)
{
}
void CC8_CALL(uint16_t addr)
{
}
void CC8_SE_VX_BYTE(uint8_t x, uint8_t kk)
{
}
void CC8_SNE_VX_BYTE(uint8_t x, uint8_t kk) 
{
	
}
void CC8_SE_VX_VY(uint8_t x, uint8_t y) {}
void CC8_LD_VX_BYTE(uint8_t x, uint8_t kk) {}
void CC8_ADD_VX_BYTE(uint8_t x, uint8_t kk) {}
void CC8_LD_VX_VY(uint8_t x, uint8_t y) {}
void CC8_OR_VX_VY(uint8_t x, uint8_t y) {}
void CC8_AND_VX_VY(uint8_t x, uint8_t y) {}
void CC8_XOR_VX_VY(uint8_t x, uint8_t y) {}
void CC8_ADD_VX_VY(uint8_t x, uint8_t y) {}
void CC8_SUB_VX_VY(uint8_t x, uint8_t y) {}
void CC8_SHR_VX(uint8_t x) {}
void CC8_SUBN_VX_VY(uint8_t x, uint8_t y) {}
void CC8_SHL_VX(uint8_t x) {}
void CC8_SNE_VX_VY(uint8_t x, uint8_t y) {}
void CC8_LD_I_ADDR(uint16_t addr) {}
void CC8_JP_V0_ADDR(uint16_t addr) {}
void CC8_RND_VX_BYTE(uint8_t x, uint8_t kk) {}
void CC8_DRW_VX_VY_NIBBLE(uint8_t x, uint8_t y, uint8_t n) {}
void CC8_SKP_VX(uint8_t x) {}
void CC8_SKNP_VX(uint8_t x) {}
void CC8_LD_VX_DT(uint8_t x) {}
void CC8_LD_VX_K(uint8_t x) {}
void CC8_LD_DT_VX(uint8_t x) {}
void CC8_LD_ST_VX(uint8_t x) {}
void CC8_ADD_I_VX(uint8_t x) {}
void CC8_LD_F_VX(uint8_t x) {}
void CC8_LD_B_VX(uint8_t x) {}
void CC8_LD_I_VX(uint8_t x) {}
void CC8_LD_VX_I(uint8_t x) {}
