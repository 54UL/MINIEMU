#ifndef CC8_MACHINE_H
#define CC8_MACHINE_H

#include <stdint.h>

#define CHIP_8_MAX_RAM 0xFFF
#define CHIP_8_V_REGISTERS_COUNT 0X0F
#define CHIP_8_VERTICAL_BIT_PAGE_SIZE 8
#define CHIP_8_VRAM_WIDTH 64
#define CHIP_8_VRAM_HEIGHT 32
#define CHIP_8_VRAM_SIZE CHIP_8_VRAM_WIDTH * CHIP_8_VRAM_HEIGHT
#define CHIP_8_FOREGROUND_DISPLAY_COLOR 0xFF00FF00
#define CHIP_8_BACKGROUND_DISPLAY_COLOR 0XFFFFFF00

#define CC8_INSTRUCTION_SET_LENGHT 35

typedef struct 
{
    uint8_t  RAM[CHIP_8_MAX_RAM];
    uint8_t  V[CHIP_8_V_REGISTERS_COUNT];
    uint8_t  SOUND;
    uint8_t  DELAY;
    uint16_t I;
    uint16_t PC;
    uint8_t  SP;
    uint16_t STACK[16];
    uint8_t  VRAM[CHIP_8_VRAM_WIDTH * CHIP_8_VRAM_HEIGHT];
    uint8_t  KEYBOARD;
    uint16_t PROGRAM_SIZE;
} CC8_Machine;

typedef struct {
    uint8_t x;
    uint8_t y;
    uint16_t nnn;
    uint8_t kk;
    uint8_t n;
    CC8_Machine * registers;
} InstructionContext;

typedef void (*instructionFnPtr)(const InstructionContext * ctx);

#endif