#ifndef GBA_Graphics
#define GBA_Graphics

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "GBABase.h"
#include "GBARegisters.h"
#include "GBATypes.h"

#define SCREENHEIGHT    160
#define SCREENWIDTH     240

// Bitmap
void mode3SetPixel(u16 xCoordinate, u16 yCoordinate, u16 colour) // 240x160 1-page 16bit colour
{
    ((unsigned short*)VRAM)[xCoordinate+(yCoordinate)*240] = colour;
}
void mode4SetPixel(u16 xCoordinate, u16 yCoordinate, u8 palette, u8 paletteIndex) // 240x160 2-page 8bit colour
{
    // ! Untested !
    // If bit 3 of REG_DISPCNT is 1, the VRAM location is 0x0600A000, ie page flipping
    // This is done with nonbranching method with boolean math
    ((unsigned short*)VRAM+(read16Bit(REG_DISPCNT,4,1)))[xCoordinate+(SCREENHEIGHT-yCoordinate)*SCREENHEIGHT] = read16Bit(MEM_PAL + palette, paletteIndex, 8);
}
void mode5SetPixel(u16 xCoordinate, u16 yCoordinate, u16 colour) // 160x128 2-page 16bit colour
{
    // ! Untested !
    // If bit 3 of REG_DISPCNT is 1, the VRAM location is 0x0600A000, ie page flipping
    // This is done with nonbranching method with boolean math
    ((unsigned short*)VRAM+(read16Bit(REG_DISPCNT,4,1)))[xCoordinate+((SCREENHEIGHT*(2/3))-yCoordinate)*160] = colour;
}
// This was actually a challenge to create
// Mostly branchless
void mode3DrawLine (u16 x0, u16 y0, u16 x1, u16 y1, u16 colour)
{
    u16 x = x0;
    u16 y = y0;

    if ( abs(x1-x0) >= abs(y1-y0) )
    {
        u16 change = (abs(y1-y0) * 256) / (abs(x1-x0));
        u16 changeP = change;
        while (x != x1)
        {
            mode3SetPixel(x,y,colour);
            x = x - 1 + 2*(x < x1);
            y = y0 + (changeP >> 8);
            changeP += change;
        }
    }
    else
    {
        u16 change = (abs(x1-x0) * 256) / (abs(y1-y0));
        u16 changeP = change;
        while (y != y1)
        {
            mode3SetPixel(x,y,colour);
            y = y - 1 + 2*(y < y1);
            x = x0 + (changeP >> 8);
            changeP += change;
        }
    }
}


// Register Control Start
void setGraphicMode(u8 VideoMode) // Mode 0-5
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 0, 3, VideoMode);
}
bool isGBCGame()
{
    return read16Bit(REG_DISPCNT, 3, 1);
}
void setPage(bool page) // Flip between pages for modes 4 and 5
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 4, 1, page);
}
void setOAM_HBlank(bool enable) // Allow access to OAM in HBlank
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 5, 1, enable);
}
void setObjectMapMode(bool enable) // Tells if the next row of tiles is beneath the prevuous in a matrix
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 6, 1, enable);
}
void setScreenBlank(bool enable) // Forces a screen blank, default is ON
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 7, 1, enable);
}
void setBackground(u8 Backgound, bool enable) // Enables rendering of backgound 0-3
{
    switch (Backgound)
    {
        case 0: REG_DISPCNT = set16Bit(REG_DISPCNT, 8, 1, enable); break;
        case 1: REG_DISPCNT = set16Bit(REG_DISPCNT, 9, 1, enable); break;
        case 2: REG_DISPCNT = set16Bit(REG_DISPCNT, 0xA, 1, enable); break;
        case 3: REG_DISPCNT = set16Bit(REG_DISPCNT, 0xB, 1, enable); break;
    }
}
void setDisplaySprites(bool enable) // Enables display of sprites
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 0xC, 1, enable);
}
void setWindow(bool window) // Enable Window 0-1
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 0xD, 2, window);
}
void setSpriteWindows(bool enable) // Enable use of the Sprite windows
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 0xF, 1, enable);
}

bool getVBlankStatus()
{
    return read16Bit(REG_DISPSTAT, 0, 1);
}
bool getHBlankStatus()
{
    return read16Bit(REG_DISPSTAT, 1, 1);
}
bool getVCountTriggerStatus()
{
    return read16Bit(REG_DISPSTAT, 2, 1);
}
void setVBlankInterrupt(bool enable)
{
    set16Bit(REG_DISPSTAT, 3, 1, enable);
}
void setHBlankInterrupt(bool enable)
{
    set16Bit(REG_DISPSTAT, 4, 1, enable);
}
void setVCountInterrupt(bool enable)
{
    set16Bit(REG_DISPSTAT, 5, 1, enable);
}
void setVCountLineTrigger(bool value)
{
    set16Bit(REG_DISPSTAT, 8, 8, value);
}

u16 getVCount()
{
    return read16Bit(REG_VCOUNT, 8, 8);
}

#endif