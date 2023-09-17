#ifndef GBA_Graphics
#define GBA_Graphics

#include <stdbool.h>

#include "GBABase.h"
#include "GBARegisters.h"
#include "GBATypes.h"

int set16Bit(int REG, u16 bitStart, u16 bitSize, int data)
{
    vu16 mask = 0b1;
    // Create Mask
    mask <<= bitSize;
    mask -= 1;
    mask <<= bitStart;
    mask = ~mask;
    // Insert data
    REG &= mask;
    data <<= bitStart;
    REG |= data;

    return REG;
}
vu32 set32Bit(vu32 REG, u16 bitStart, u16 bitSize, vu32 data)
{
    vu16 mask = 0b1;
    // Create Mask
    mask <<= bitSize;
    mask -= 1;
    mask <<= bitStart;
    mask = ~mask;
    // Insert data
    REG &= mask;
    data <<= bitStart;
    REG |= data;

    return REG;
}

void setGraphicMode(u8 VideoMode) // Mode 0-5
{
    REG_DISPCNT = set16Bit(REG_DISPCNT, 0, 3, VideoMode);
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

#endif