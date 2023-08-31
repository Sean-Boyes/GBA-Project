#ifndef GBA_VIDEO_H
#define GBA_VIDEO_H

#include "../include/GBABase.h"
#include "../include/GBATypes.h"

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  160

//---Display register---

#define REG_DISPCNT *((vu16*)(REG_BASE + 0x00)) // 0x04000000 not sure if *((vu16*)(REG_BASE + 0x0000)) 

    // Mode | Bits 0-2
    #define DCNT_MODE0          0x0000      // 0000:0000:0000:0000 | Tile mode with four tiled backgrounds
    #define DCNT_MODE1          0x0001      // 0000:0000:0000:0001 | Tile mode with three tiled backgrounds with one that can be rotated and scaled
    #define DCNT_MODE2          0x0002      // 0000:0000:0000:0010 | Tile mode with two tiled backgrounds with both able to be rotated and scaled
    #define DCNT_MODE3          0x0003      // 0000:0000:0000:0011 | Bitmap mode with resolution 240x160px 16bit colour
    #define DCNT_MODE4          0x0004      // 0000:0000:0000:0100 | Bitmap mode with resolution 240x160px 8bit colour double buffered
    #define DCNT_MODE5          0x0005      // 0000:0000:0000:0101 | Bitmap mode with resolution 160x128px 16bit colour double buffered

    // GB | Bit 3 | Read Only
    #define DCNT_GB             0x0008      // 0000:0000:0000:1000 | Is GBC game, read-only

    // PS | Bit 4
    #define DCNT_PAGE           0x0010      // 0000:0000:0001:0000 | Page select, Modes 4 and 5 can use flipping for smoother animation

    // HB | Bit 5
    #define DNCT_OAM_HBL        0x0020      // 0000:0000:0010:0000 | Allow access to OAM in an HBlank. OAM is normally locked in VDraw, reduces amount of spreite pixels rendered per line

    // OM | Bit 6
    #define DCNT_OBJ_1D         0x0040      // 0000:0000:0100:0000 | Object mapping mode, tells wif the next row of tiles lies beneath the previous in a matrix

    // FB | Bit 7
    #define DCNT_BLANK          0x0080      // 0000:0000:1000:0000 | Forces a screen blank

    // BG0-BG3, Obj | Bits 8-C
    #define DCNT_BG0            0x0100      // 0000:0001:0000:0000 | Enables rendering of the background 0
    #define DCNT_BG1            0x0200      // 0000:0010:0000:0000 | Enables rendering of the background 1
    #define DCNT_BG2            0x0400      // 0000:0100:0000:0000 | Enables rendering of the background 2
    #define DCNT_BG3            0x0800      // 0000:1000:0000:0000 | Enables rendering of the background 3
    #define DCNT_OBJ            0x1000      // 0001:0000:0000:0000 | Enables rendering of the sprites

    // W0-OW | Bits D-F
    #define DCMT_WIN0           0x2000      // 0010:0000:0000:0000 | Enables use of window 0
    #define DCMT_WIN1           0x4000      // 0100:0000:0000:0000 | Enables use of window 1
    #define DCMT_WINOBJ         0x8000      // 1000:0000:0000:0000 | Enables use of object window

#define REG_DISPSTAT            0400:0004h

    // Vbs | Bit 0 | Read Only
    #define DSTAT_IN_VBL        0x0001      // 0000:0000:0000:0001 | VBlank status, set inside VBlank, clear in VDraw

    // HBS | Bit 1 | Read Only
    #define DSTAT_IN_HBL        0x0002      // 0000:0000:0000:0010 | HBlank status, set inside HBlank

    // Vcs | Bit 2 | Read Only
    #define DSTAT_IN_VCT        0x0004      // 0000:0000:0000:0100 | VCount trigger status, set if current scacnline matches the scanline trigger (REG_VCOUNT == REG_DISPSTAT{8-F})

    // VbI | Bit 3 
    #define DSTAT_VBL_IRQ       0x0008      // 0000:0000:0000:1000 | VBlank interrupt request. If set, an interrupt is fired at VBlank

    // HbI | Bit 4
    #define DSTAT_HBL_IRQ       0x0010      // 0000:0000:0001:0000 | HBlank interrupt request. If set, an interrupt is fired at HBlank

    // VcI | Bit 5
    #define DSTAT_VCT_IRQ       0x0020      // 0000:0000:0010:0000 | VCount interrup request. If set, an iterrupt is fired at VCount if current scanline matches the trigger value

    // VcT | Bits 8-F
    #define DSTAT_VCT8          0x0100      // 0000:0001:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCT9          0x0200      // 0000:0010:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCTA          0x0400      // 0000:0100:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCTB          0x0800      // 0000:1000:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCTC          0x1000      // 0001:0000:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCTD          0x2000      // 0010:0000:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCTE          0x4000      // 0100:0000:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set
    #define DSTAT_VCTF          0x8000      // 1000:0000:0000:0000 | VCount trigger value, if current scanline is at this value, bit 2 is set

#define REG_VCOUNT              0400:0006h  // Vertical count | Range [0,227] | Read only

#endif