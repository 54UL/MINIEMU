#ifndef GB_HEADER_H
#define GB_HEADER_H

#include <stdint.h>

#define ROM_HEADER_SIZE 0x014F

typedef struct {
    // Entry Point
    uint16_t entry_point;

    // Nintendo Logo (48 bytes)
    uint8_t nintendo_logo[48];

    // Game Title (16 bytes)
    char title[16];

    // Game Boy Color Flag (0x80 for GBC, 0x00 otherwise)
    uint8_t gbc_flag;

    // Manufacturer Code (4 bytes)
    char manufacturer_code[4];

    // CGB Flag (0x80 for CGB, 0x00 otherwise)
    uint8_t cgb_flag;

    // New Licensee Code (2 bytes)
    char new_licensee_code[2];

    // SGB Flag (0x03 for SGB, 0x00 otherwise)
    uint8_t sgb_flag;

    // Cartridge Type
    uint8_t cartridge_type;

    // ROM Size
    uint8_t rom_size;

    // RAM Size
    uint8_t ram_size;

    // Destination Code
    uint8_t destination_code;

    // Old Licensee Code
    uint8_t old_licensee_code;

    // Mask ROM Version Number
    uint8_t mask_rom_version;

    // Header Checksum
    uint8_t header_checksum;

    // Global Checksum (usually calculated and stored here)
    uint16_t global_checksum;
} GB_Header;

#endif