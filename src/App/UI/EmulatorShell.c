#include "EmulatorShell.h"
#include <SDL2/SDL.h>
#include "Fonts/Default_7x8.h"


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_ROMS 128

static volatile uint8_t showMenu = 1;
static const uint32_t fontColor = 0X00FF00FF;
static const uint32_t backgroundColor = 0X1E1E1E1E;
static char files[MAX_ROMS][64]; // supports 128 paths with 32 characters wide path size
static uint16_t readedRooms = 0;

void GetFolderContents(const char *folderPath)
{
    struct dirent *entry;
    DIR *directory = opendir(folderPath);
    uint8_t fileIndex = 0;

    if (directory)
    {
        while ((entry = readdir(directory)) != NULL && (fileIndex < MAX_ROMS))
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                strcpy(files[fileIndex], entry->d_name);

                size_t lenght = strlen(entry->d_name);
                files[fileIndex][lenght] = '\0';

                fileIndex++;
            }
        }

        readedRooms = fileIndex;
        closedir(directory);
    }
}

void EmuShell_DrawChar(unsigned char character, uint32_t *pixels, const int x, const int y)
{
    const uint16_t fontStartPos = (((uint8_t) character - 32) * 6);

    //TODO: OPTIMIZE THIS USING ONLY SEND DATA FUNCTION (REMOVE OVERHEAD LOOPS)
    for (uint8_t gylphIndex = 0; gylphIndex < 6; gylphIndex++)
    {
        //TODO: IMPLEMENT MULTI ARCH REMOVING AVR INTRINSICTS
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            pixels[(y+bit) * 300 + (x+gylphIndex)] = (BitMapFont[fontStartPos + gylphIndex] >> bit) & 0x01 ? fontColor : backgroundColor;
        }
    }
}

void EmuShell_DrawString(const char *string, uint32_t * pixels, int x, int y)
{
  uint8_t index = 0;

  while (string[index])
  {
    EmuShell_DrawChar(string[index++], pixels, x + (index * 6), y);
  }
}

void DrawString()
{

}

void EmuShell_Init()
{
    GetFolderContents("/home/dev/repos/chip8-roms/games");
}

void EmuShell_UpdateFrame(uint32_t * pixels)
{
   EmuShell_DrawString("Chip 8 emulator (CC8 V1.0 BY XUL)", pixels, 32, 0);

   EmuShell_DrawString("[PC:0XFFFF][PRG_SZ: 0XFFF] CURRENT ROM:", pixels, 0, 19);
   EmuShell_DrawString("[Sierpinski [Sergey Naydenov, 2010].ch8]", pixels, 0, 29);

   EmuShell_DrawString("ROMS Folder:", pixels, 8, 42);

   for (int i = 0; i < 8; i++)
   {
        int yLoc = (9 * i) + 52;
        EmuShell_DrawString("* ", pixels, 2, yLoc);
        EmuShell_DrawString(files[i], pixels, 16, yLoc);
   }
}

void EmuShell_Invoke(const char* cmd, void * payload)
{

}

void EmuShell_KeyPressed(const char code)
{
    if (SDLK_ESCAPE == code)
    {
        showMenu = !showMenu;
    }
}

uint8_t EmuShell_Shown()
{
    return showMenu;
}