#ifndef CC8_MEMORY_H
#define CC8_MEMORY_H
#include <stdint.h>

// MEMORY
#define CHIP_8_MAX_RAM 0xFFF
#define CHIP_8_V_REGISTERS_COUNT 0X0F
// DISPLAY
#define CHIP_8_VERTICAL_BIT_PAGE_SIZE 8
#define CHIP_8_VRAM_WIDTH 64
#define CHIP_8_VRAM_HEIGHT 32
#define CHIP_8_VRAM_SIZE CHIP_8_VRAM_WIDTH * CHIP_8_VRAM_HEIGHT
#define CHIP_8_FOREGROUND_DISPLAY_COLOR 0xFF00FF00
#define CHIP_8_BACKGROUND_DISPLAY_COLOR 0XFFFFFF00
// INSTRUCTION SET
#define CC8_INSTRUCTION_SET_LENGHT 35
#define CC8_INSTRUCTION_HASH_LENGHT 33
#define CC8_INVALID_INSTRUCTION 0XFFFF
// MEMORY MAPING
#define CC8_FONT_ADDR_START 0x000
#define CC8_BOOT_ADDR_START 0x200
#define CC8_FILE_PROGRAM_BUFFER_SIZE 4096

static const uint8_t CC8_FONT[] = {
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
    uint16_t INSTRUCTION; // Only used for Unit testing
} CC8_Memory;

#endif