#ifndef GBA_Graphics
#define GBA_Graphics

#include <stdbool.h>

#include "GBABase.h"
#include "GBARegisters.h"
#include "GBATypes.h"

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