#include "EmulatorShell.h"
#include <SDL2/SDL.h>
#include "Fonts/Default_7x8.h"


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#define MAX_ROMS 128
#define FRAME_WIDTH  300
#define FRAME_HEIGHT 128

static volatile uint8_t s_showMenu = 1;
static const uint32_t s_fontColor = 0X00FF00FF;
static const uint32_t s_backgroundColor = 0X1E1E1E1E;
static char s_files[MAX_ROMS][64]; // supports 128 paths with 32 characters wide path size
static uint16_t s_readedRooms = 0;
static int s_tabsIndex = 0;
static int s_selectionIndex = 0;

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
                strcpy(s_files[fileIndex], entry->d_name);

                size_t lenght = strlen(entry->d_name);
                s_files[fileIndex][lenght] = '\0';

                fileIndex++;
            }
        }

        s_readedRooms = fileIndex;
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
            pixels[((y + bit) % FRAME_HEIGHT) * FRAME_WIDTH + ((x + gylphIndex) % FRAME_WIDTH)] = (BitMapFont[fontStartPos + gylphIndex] >> bit) & 0x01 ? s_fontColor : s_backgroundColor;
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
    // TODO: GET THIS VALUE FROM A CONFIG FILE
    GetFolderContents("../ROMS");
}

int ShellColum(int * yAxis)
{
   return *yAxis += DEFAUL_COL_Y_SPACING;
}

void EmuShell_UpdateFrame(uint32_t *pixels)
{
   // Starting row position...
   int rowYLoc = 1;
   int cursorYPos = 2;
   const uint8_t cursorBounds = (8 * 8);
   const char currentRomStr[128];
   char currentStatusStr[32];

   // Clear rendering buffer
   memset(pixels, s_backgroundColor, FRAME_WIDTH * FRAME_HEIGHT * sizeof(uint32_t));

   EmuShell_DrawString("CC8 V1.0 (CHIP 8 EMULATOR BY XUL)", pixels, 32, ShellColum(&rowYLoc));

   switch (s_selectionIndex)
   {
        case 0:
            strcpy(currentStatusStr, "[START]");
            break;
        case 1:
            strcpy(currentStatusStr, "[RUNNING]");
            break;

        default:
            strcpy(currentStatusStr, "[STOPPED]");
            break;
   }

   sprintf(currentRomStr, "%s %s", currentStatusStr, s_files[s_tabsIndex]);
   EmuShell_DrawString(currentRomStr, pixels, 16, ShellColum(&rowYLoc) + 2);
   
   ShellColum(&rowYLoc);
   cursorYPos = rowYLoc + (2 * DEFAUL_COL_Y_SPACING);

   EmuShell_DrawString("ROMS:", pixels, 8, ShellColum(&rowYLoc));
   for (int i = 0; i < 8; i++)
   {
        int yLoc = ShellColum(&rowYLoc);
        int cursorY =  (cursorYPos + (s_tabsIndex * 8) % cursorBounds);
        EmuShell_DrawString("* ", pixels, 2, cursorY);
        EmuShell_DrawString(s_files[i], pixels, 16, yLoc);
   }
}


// BIG MF TODO: WTFFF I DID NOT WANT THIS...
uint16_t ClampValue(uint16_t value, uint16_t min, uint16_t max){
       if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

// TODO: CHECK IF IS THIS PROCCESSED IN THE EVENT THREAD...
char lastCode;
void EmuShell_KeyPressed(const char code)
{
    if (lastCode == code) 
    {
        SDL_Delay(16);
        return;
    }

    switch (code)
    {
        // MENU
        case SDLK_ESCAPE:
            s_showMenu = !s_showMenu;
            break;

        // UP
        case SDLK_o:
            s_tabsIndex--;
            s_tabsIndex = ClampValue(s_tabsIndex,0, s_readedRooms - 1);
            break;

        // DOWN
        case SDLK_l:
            s_tabsIndex++;
            s_tabsIndex =  ClampValue(s_tabsIndex,0, s_readedRooms - 1);
            break;

        // CANCEL 
        case SDLK_k:
            s_selectionIndex--;
            s_selectionIndex = ClampValue(s_selectionIndex,0, 3);
            break;

        // ACCEPT (MULTIPLE LEVELS)
        case SDLK_SEMICOLON:
            s_selectionIndex++;
            s_selectionIndex = ClampValue(s_selectionIndex,0, 3);
            break;

        default:
            break;
    }

    lastCode = code;
}

uint8_t EmuShell_Shown()
{
    return s_showMenu;
}