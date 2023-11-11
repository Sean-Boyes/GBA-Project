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

// Mode 3
void mode3SetPixel(u16 xCoordinate, u16 yCoordinate, u16 colour) // 240x160 1-page 16bit colour
{
    ((unsigned short*)VRAM)[xCoordinate+yCoordinate*240] = colour;
}

// Mostly branchless
void mode3DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 colour)
{
    u16 x = x0;
    u16 y = y0;

    if ( abs(x1-x0) >= abs(y1-y0) )
    {
        u16 change = (abs(y1-y0) * 256) / (abs(x1-x0));
        u16 changeP = change + 128;
        while (x != x1)
        {
            mode3SetPixel(x,y,colour);
            x = x - 1 + 2*(x0 < x1);
            y = y0 + (2*(y0 < y1)-1)*(changeP >> 8);
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
            y = y - 1 + 2*(y0 < y1);
            x = x0 + (2*(x0 < x1)-1)*(changeP >> 8);
            changeP += change;
        }
    }
    mode3SetPixel(x1,y1,colour);
}
//mode 4

u8 add_palette_color(u8 r, u8 g, u8 b, u8 index) {
    unsigned short color = b << 10;
    color += g << 5;
    color += r;

    /* add the color to the palette */
    // MEM_PAL[next_palette_index] = color;
    set16Bit(MEM_PAL + (2 * index), 0, 16, color);

    /* return index of color just added */
    return index;
}

void mode4SetPixel(u16 buffer, u16 col, u16 row, u16 colour)
{
    u16 offset = (row * SCREENWIDTH + col) - (col & 1);
    u16 page = (0xA000 * buffer);
    u16* REG_PTR = (u16*) (VRAM + page + offset);
    u16 REG_DATA = *REG_PTR;
    // Create Mask
    u16 mask = 0xff00 >> (8 * (col & 1));
    //mask = ~mask;
    // Insert data
    REG_DATA &= mask;
    colour <<= (8 * (col & 1));
    REG_DATA |= colour;

    *REG_PTR = REG_DATA;
}
void mode4DrawLine(u16 buffer, u16 x0, u16 y0, u16 x1, u16 y1, u16 colour)
{
    u16 x = x0;
    u16 y = y0;

    if ( abs(x1-x0) >= abs(y1-y0) )
    {
        u16 change = (abs(y1-y0) * 256) / (abs(x1-x0));
        u16 changeP = change + 128;
        while (x != x1)
        {
            mode4SetPixel(buffer, x, y,colour);
            x = x - 1 + 2*(x0 < x1);
            y = y0 + (2*(y0 < y1)-1)*(changeP >> 8);
            changeP += change;
        }
    }
    else
    {
        u16 change = (abs(x1-x0) * 256) / (abs(y1-y0));
        u16 changeP = change;
        while (y != y1)
        {
            mode4SetPixel(buffer, x, y,colour);
            y = y - 1 + 2*(y0 < y1);
            x = x0 + (2*(x0 < x1)-1)*(changeP >> 8);
            changeP += change;
        }
    }
    mode4SetPixel(buffer, x1, y1,colour);
}
// void mode4PaintScreen(u16 buffer, u16 colour) {
//     /* set each pixel black */
//     u16 page = (buffer * 0xA000);
//     colour = colour | (colour << 8);
//     u32 screen = (SCREENWIDTH * SCREENWIDTH) >> 2;
//     for (u16 i = 0; i < screen; i++) {
//         ((unsigned short*)(VRAM + page))[i] = colour;
//         // mode4SetPixel(buffer, i, 0, colour);
//     }
// }

// mode 5
void mode5SetPixel(u16 buffer, u16 xCoordinate, u16 yCoordinate, u16 colour)
{
    ((unsigned short*)(VRAM + (buffer * 0xA000)))[xCoordinate+yCoordinate*160] = colour;
}
void mode5DrawLine(u16 buffer, s16 x0, s16 y0, s16 x1, s16 y1, u16 colour)
{
    s16 x = x0;
    s16 y = y0;

    // flatten
    // if (x1 < 0) {x1 = 0;}
    // if (y1 < 0) {y1 = 0;}
    // if (x1 > SCREENWIDTH/2) {x1 = SCREENWIDTH/2;}
    // if (y1 > SCREENHEIGHT/2) {y1 = SCREENHEIGHT/2;}

    // if (x0 < 0) {x0 = 0;}
    // if (y0 < 0) {y0 = 0;}
    // if (x0 > SCREENWIDTH/2) {x0 = SCREENWIDTH/2;}
    // if (y0 > SCREENHEIGHT/2) {y0 = SCREENHEIGHT/2;}

    if ( abs(x1-x0) >= abs(y1-y0) )
    {
        u16 change = (abs(y1-y0) * 256) / (abs(x1-x0));
        u16 changeP = change + 128;
        while (x != x1)
        {
            if (x > 0 && y > 0 && x < SCREENWIDTH && y < SCREENHEIGHT) mode5SetPixel(buffer, x, y, colour);
            x = x - 1 + 2*(x0 < x1);
            y = y0 + (2*(y0 < y1)-1)*(changeP >> 8);
            changeP += change;
        }
    }
    else
    {
        u16 change = (abs(x1-x0) * 256) / (abs(y1-y0));
        u16 changeP = change;
        while (y != y1)
        {
            if (x > 0 && y > 0 && x < SCREENWIDTH && y < SCREENHEIGHT) mode5SetPixel(buffer, x, y, colour);
            y = y - 1 + 2*(y0 < y1);
            x = x0 + (2*(x0 < x1)-1)*(changeP >> 8);
            changeP += change;
        }
    }
    mode5SetPixel(buffer, x1, y1, colour);
}

// Graphics Hardware Registers

void setGraphicMode(u8 VideoMode) // Mode 0-5
{
    set16Bit(REG_DISPCNT, 0, 3, VideoMode);
}
bool isGBCGame()
{
    return read16Bit(REG_DISPCNT, 3, 1);
}
u8 flip_buffers(vu16 buffer) {
    if(buffer == 0) {
        set16Bit(REG_DISPCNT, 4, 1, 0);
        return 1;
    }else {
        set16Bit(REG_DISPCNT, 4, 1, 1);
        return 0;
    }
}
void setOAM_HBlank(bool enable) // Allow access to OAM in HBlank
{
    set16Bit(REG_DISPCNT, 5, 1, enable);
}
void setObjectMapMode(bool enable) // Tells if the next row of tiles is beneath the prevuous in a matrix
{
    set16Bit(REG_DISPCNT, 6, 1, enable);
}
void setScreenBlank(bool enable) // Forces a screen blank, default is ON
{
    set16Bit(REG_DISPCNT, 7, 1, enable);
}
void setBackground(u8 Backgound, bool enable) // Enables rendering of backgound 0-3
{
    switch (Backgound)
    {
        case 0: set16Bit(REG_DISPCNT, 8, 1, enable); break;
        case 1: set16Bit(REG_DISPCNT, 9, 1, enable); break;
        case 2: set16Bit(REG_DISPCNT, 0xA, 1, enable); break;
        case 3: set16Bit(REG_DISPCNT, 0xB, 1, enable); break;
    }
}
void setDisplaySprites(bool enable) // Enables display of sprites
{
    set16Bit(REG_DISPCNT, 0xC, 1, enable);
}
void setWindow(bool window) // Enable Window 0-1
{
    set16Bit(REG_DISPCNT, 0xD, 2, window);
}
void setSpriteWindows(bool enable) // Enable use of the Sprite windows
{
    set16Bit(REG_DISPCNT, 0xF, 1, enable);
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
    return read16Bit(REG_VCOUNT, 0, 8);
}

// Background Registers

void setPriority(u8 background, u8 priority)
{
    switch (background)
    {
        case 1: set16Bit(REG_BG0CNT, 0, 2, priority); break;
        case 2: set16Bit(REG_BG1CNT, 0, 2, priority); break;
        case 3: set16Bit(REG_BG2CNT, 0, 2, priority); break;
        case 4: set16Bit(REG_BG3CNT, 0, 2, priority); break;
    }
}
//Starting address of character tile data | Address = 0x06000000 + S * 0x4000
void setCharacterTileDataAddress(u8 background, u8 startAddr)
{
    switch (background)
    {
        case 1: set16Bit(REG_BG0CNT, 2, 2, startAddr); break;
        case 2: set16Bit(REG_BG1CNT, 2, 2, startAddr); break;
        case 3: set16Bit(REG_BG2CNT, 2, 2, startAddr); break;
        case 4: set16Bit(REG_BG3CNT, 2, 2, startAddr); break;
    }
}

void setMosiacEffect(u8 background, bool toggle)
{
    switch (background)
    {
        case 1: set16Bit(REG_BG0CNT, 2, 2, toggle); break;
        case 2: set16Bit(REG_BG1CNT, 2, 2, toggle); break;
        case 3: set16Bit(REG_BG2CNT, 2, 2, toggle); break;
        case 4: set16Bit(REG_BG3CNT, 2, 2, toggle); break;
    }
}
// 1 - standard 256 color pallete | 0 - each tile uses one of 16 different 16 color palettes
void setColourPaletteType(u8 background, bool toggle)
{
    switch (background)
    {
        case 1: set16Bit(REG_BG0CNT, 2, 2, toggle); break;
        case 2: set16Bit(REG_BG1CNT, 2, 2, toggle); break;
        case 3: set16Bit(REG_BG2CNT, 2, 2, toggle); break;
        case 4: set16Bit(REG_BG3CNT, 2, 2, toggle); break;
    }
}
// Starting address of character tile map Address = 0x06000000 + M * 0x800
void setCharacterTileMapAddress(u8 background, u8 startAddr)
{
    switch (background)
    {
        case 1: set16Bit(REG_BG0CNT, 8, 4, startAddr); break;
        case 2: set16Bit(REG_BG1CNT, 8, 4, startAddr); break;
        case 3: set16Bit(REG_BG2CNT, 8, 4, startAddr); break;
        case 4: set16Bit(REG_BG3CNT, 8, 4, startAddr); break;
    }
}
/*
 *  Used to determine whether rotational backgrounds get tiled repeatedly 
 *  This is forced to 0 (read only) for backgrounds 0 and 1 (only)
*/
void setScreenOver(u8 background, bool toggle)
{
    switch (background)
    {
        case 1: set16Bit(REG_BG0CNT, 0xD, 1, toggle); break;
        case 2: set16Bit(REG_BG1CNT, 0xD, 1, toggle); break;
        case 3: set16Bit(REG_BG2CNT, 0xD, 1, toggle); break;
        case 4: set16Bit(REG_BG3CNT, 0xD, 1, toggle); break;
    }
}
/*
    Size of tile map

    For "text" backgrounds:

    00 = 256x256 (32x32 tiles)
    01 = 512x256 (64x32 tiles)
    10 = 256x512 (32x64 tiles)
    11 = 512x512 (64x64 tiles)

    For rotational backgrounds:

    00 = 128x128 (16x16 tiles)
    01 = 256x256 (32x32 tiles)
    10 = 512x512 (64x64 tiles)
    11 = 1024x1024 (128x128 tiles)
*/
void setTileMapSize(u8 background, u8 size)
{
        switch (background)
    {
        case 0: set16Bit(REG_BG0CNT, 0xE, 2, size); break;
        case 1: set16Bit(REG_BG1CNT, 0xE, 2, size); break;
        case 2: set16Bit(REG_BG2CNT, 0xE, 2, size); break;
        case 3: set16Bit(REG_BG3CNT, 0xE, 2, size); break;
    }
}

void setBackgroundScroll(u8 background, u16 xCoordinate, u16 yCoordinate)
{
    switch (background)
    {
        case 0: set16Bit(REG_BG0HOFS, 0, 10, xCoordinate); break;
        case 1: set16Bit(REG_BG1HOFS, 0, 10, xCoordinate); break;
        case 2: set16Bit(REG_BG2HOFS, 0, 10, xCoordinate); break;
        case 3: set16Bit(REG_BG3HOFS, 0, 10, xCoordinate); break;
    }
    switch (background)
    {
        case 0: set16Bit(REG_BG0VOFS, 0, 10, yCoordinate); break;
        case 1: set16Bit(REG_BG1VOFS, 0, 10, yCoordinate); break;
        case 2: set16Bit(REG_BG2VOFS, 0, 10, yCoordinate); break;
        case 3: set16Bit(REG_BG3VOFS, 0, 10, yCoordinate); break;
    }
}
/*
 *  The effect of these registers is to scale the background
 *  (relative to the upper left corner) in the x/y direction 
 *  by an amount equal to 1/(register value).
*/
void setBackgroundScale(u8 background, u16 xScale, u16 yScale)
{
    switch (background)
    {
        case 2: set16Bit(REG_BG2PA, 0, 16, xScale); break;
        case 3: set16Bit(REG_BG3PA, 0, 16, xScale); break;
    }
    switch (background)
    {
        case 2: set16Bit(REG_BG2PD, 0, 16, yScale); break;
        case 3: set16Bit(REG_BG3PD, 0, 16, yScale); break;
    }
}
/*
 * The effect of these registers is to shear the x/y coordinates
 * of the background over y, relative to the upper left corner.
*/
void setBackgroundShear(u8 background, u16 xScale, u16 yScale)
{
    switch (background)
    {
        case 2: set16Bit(REG_BG2PB, 0, 10, xScale); break;
        case 3: set16Bit(REG_BG3PB, 0, 10, xScale); break;
    }
    switch (background)
    {
        case 2: set16Bit(REG_BG2PC, 0, 10, yScale); break;
        case 3: set16Bit(REG_BG3PC, 0, 10, yScale); break;
    }
}
// Redefines where (0,0) is somehow, see registers
void setBackgroundRotation(u8 background, u32 xValue, u32 yValue)
{
    switch (background)
    {
        case 2: set32Bit(REG_BG2PX, 0, 10, xValue); break;
        case 3: set32Bit(REG_BG3PX, 0, 10, xValue); break;
    }
    switch (background)
    {
        case 2: set32Bit(REG_BG2PY, 0, 10, yValue); break;
        case 3: set32Bit(REG_BG3PY, 0, 10, yValue); break;
    }   
}

/*
 *  ~Windowing Registers~
*/
/*
 * TODO: Optimize later with *(vu16*)(REG) = value
*/
void setWindowPosition(u8 window, u16 xStart, u16 xEnd, u16 yStart, u16 yEnd)
{
    switch (window)
    {
        case 0: 
            set16Bit(REG_WIN0H, 0, 16, (xStart << 8) | xEnd); 
            set16Bit(REG_WIN0V, 0, 16, (yStart << 8) | yEnd);
            break;
        case 1: 
            set16Bit(REG_WIN1H, 0, 16, (xStart << 8) | xEnd); 
            set16Bit(REG_WIN1V, 0, 16, (yStart << 8) | yEnd);
            break;
    }
}

/*
 *  TODO: Optimize please
*/
void setInsideWindowSettings(bool window, bool bg0, bool bg1, bool bg2, bool bg3, bool sprites, bool blends)
{
    switch (window)
    {
        case 0:
            set16Bit(REG_WININ, 0, 6, (bg0) | (bg1 << 1) | (bg2 << 2) | (bg3 << 3) | (sprites << 4) | (blends << 5)); break;
        case 1:
            set16Bit(REG_WININ, 8, 6, (bg0 << 8) | (bg1 << 9) | (bg2 << 0xA) | (bg3 << 0xB) | (sprites << 0xC) | (blends << 0xD)); break;
    }
}

void setOutsideWindowSettings(bool window, bool bg0, bool bg1, bool bg2, bool bg3, bool sprites, bool blends)
{
    switch (window)
    {
        case 0:
            set16Bit(REG_WINOUT, 0, 6, (bg0) | (bg1 << 1) | (bg2 << 2) | (bg3 << 3) | (sprites << 4) | (blends << 5)); break;
        case 1:
            set16Bit(REG_WINOUT, 8, 6, (bg0 << 8) | (bg1 << 9) | (bg2 << 0xA) | (bg3 << 0xB) | (sprites << 0xC) | (blends << 0xD)); break;
    }
}


#endif