#ifndef GBA_REG_H
#define GBA_REG_H

#include "../include/GBABase.h"
#include "../include/GBATypes.h"

//---Graphics Hardware Registers

#define REG_DISPCNT             *((vu16*)(REG_BASE + 0x0000)) // 0x04000000
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
    #define DCNT_WIN0           0x2000      // 0010:0000:0000:0000 | Enables use of window 0
    #define DCNT_WIN1           0x4000      // 0100:0000:0000:0000 | Enables use of window 1
    #define DCNT_WINOBJ         0x8000      // 1000:0000:0000:0000 | Enables use of object window

#define REG_DISPSTAT            *((vu16*)(REG_BASE + 0x0002))
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

#define REG_VCOUNT              *((vu16*)(REG_BASE + 0x0006))  // Vertical count | Range [0,227] | Read only

//---Background Registers---

#define REG_BG0CNT              *((vu16*)(REG_BASE + 0x008))  // Background 0 Registers
#define REG_BG1CNT              *((vu16*)(REG_BASE + 0x00A))  // Background 1 Registers
#define REG_BG2CNT              *((vu16*)(REG_BASE + 0x00C))  // Background 2 Registers
#define REG_BG3CNT              *((vu16*)(REG_BASE + 0x00E))  // Background 3 Registers
    // BPI | Bits 0-1
    #define DBG_P0             0x0000      // 0000:0000:0000:0000 | Background priority index 0
    #define DBG_P1             0x0001      // 0000:0000:0000:0001 | Background priority index 1
    #define DBG_P2             0x0002      // 0000:0000:0000:0010 | Background priority index 2
    #define DBG_P3             0x0003      // 0000:0000:0000:0011 | Background priority index 3

    // SATD | Bits 2-3
    #define DBG_S1             0x0004      // 0000:0000:0000:0100 | Starting address of character tile data, Address = 0x06000000 + S * 0x4000
    #define DBG_S2             0x0008      // 0000:0000:0000:0100 | Starting address of character tile data, Address = 0x06000000 + S * 0x4000
    
    // ME | Bit 6
    #define DBG_ME             0x0040      // 0000:0000:0100:0000 | Mosiac effect

    // CPT | Bit 7 
    #define DBG_CPT            0x0080      // 0000:0000:1000:0000 | 1: Standard Color palette, 0: each tile uses 1 of 16 different 16 color palettes

    // SATM | Bits 8-C
    #define DBG_SATM           0x0100      // 0000:0001:0000:0000 | Starting address of character tile map, Address = 0x06000000 + M * 0x800
    #define DBG_SATM           0x0200      // 0000:0010:0000:0000 | Starting address of character tile map, Address = 0x06000000 + M * 0x800
    #define DBG_SATM           0x0400      // 0000:0100:0000:0000 | Starting address of character tile map, Address = 0x06000000 + M * 0x800
    #define DBG_SATM           0x0800      // 0000:1000:0000:0000 | Starting address of character tile map, Address = 0x06000000 + M * 0x800
    #define DBG_SATM           0x1000      // 0001:0000:0000:0000 | Starting address of character tile map, Address = 0x06000000 + M * 0x800

    // SO | Bit D | Read Only for BG0 and BG1
    #define DBG1_SO             0x2000      // 0010:0000:0000:0000 | Screen Over, rotational backgrounds get tiled repeatedly at edges or a single tile

    // SOTM | Bits E-F
    #define DBG_SOTM1          0x0000      // 0000:0000:0000:0000 | For "text" backgrounds: 32x32 tiles, For rotational backgrounds: 16x16 tiles
    #define DBG_SOTM1          0x4000      // 0100:0000:0000:0000 | For "text" backgrounds: 64x32 tiles, For rotational backgrounds: 32x32 tiles
    #define DBG_SOTM1          0x8000      // 1000:0000:0000:0000 | For "text" backgrounds: 32x64 tiles, For rotational backgrounds: 64x64 tiles
    #define DBG_SOTM1          0xC000      // 1100:0000:0000:0000 | For "text" backgrounds: 64x64 tiles, For rotational backgrounds: 128x128 tiles

//---Background Rotation / Scaling Registers---

// F E D C B A 9 8 7 6 5 4 3 2 1 0
// X X X X X X I I I I I I I I I I
#define REG_BG0HOFS            *((vu16*)(REG_BASE + 0x010))  // Horizontal scroll co-ordinate for BG0 (Write Only)
#define REG_BG0BOFS            *((vu16*)(REG_BASE + 0x012))  // Vertical scroll co-ordinate for BG0 (Write Only)
#define REG_BG1HOFS            *((vu16*)(REG_BASE + 0x014))  // Horizontal scroll co-ordinate for BG1 (Write Only)
#define REG_BG1VOFS            *((vu16*)(REG_BASE + 0x016))  // Vertical scroll co-ordinate for BG1 (Write Only)
#define REG_BG2HOFS            *((vu16*)(REG_BASE + 0x018))  // Horizontal scroll co-ordinate for BG2 (Write Only)
#define REG_BG2VOFS            *((vu16*)(REG_BASE + 0x01A))  // Vertical scroll co-ordinate for BG2 (Write Only)
#define REG_BG3HOFS            *((vu16*)(REG_BASE + 0x01C))  // Horizontal scroll co-ordinate for BG3 (Write Only)
#define REG_BG3VOFS            *((vu16*)(REG_BASE + 0x01E))  // Vertical scroll co-ordinate for BG3 (Write Only)

// F E D C  B A 9 8  7 6 5 4  3 2 1 0
// S I I I  I I I I  F F F F  F F F F
#define REG_BG2PA              *((vu16*)(REG_BASE + 0x020))  // BG2 Read Source Pixel X Increment (Write Only)
#define REG_BG3PA              *((vu16*)(REG_BASE + 0x030))  // BG3 Read Source Pixel X Increment (Write Only)
#define REG_BG2PB              *((vu16*)(REG_BASE + 0x022))  // BG2 Write Destination Pixel X Increment (Write Only)
#define REG_BG3PB              *((vu16*)(REG_BASE + 0x032))  // BG3 Write Destination Pixel X Increment (Write Only)
#define REG_BG2PC              *((vu16*)(REG_BASE + 0x024))  // BG2 Read Source Pixel Y Increment (Write Only)
#define REG_BG3PC              *((vu16*)(REG_BASE + 0x034))  // BG3 Read Source Pixel Y Increment (Write Only)
#define REG_BG2PD              *((vu16*)(REG_BASE + 0x026))  // BG2 Write Destination Pixel Y Increment (Write Only)
#define REG_BG3PD              *((vu16*)(REG_BASE + 0x036))  // BG3 Write Destination Pixel Y Increment (Write Only)

// 1F 1E 1D 1C : 1B 1A 19 18 : 17 16 15 14 : 13 12 11 10 : F  E  D  C : B  A  9  8 : 7  6  5  4 : 3  2  1  0
// X  X  X  X  : S  I  I  I  : I  I  I  I  : I  I  I  I  : I  I  I  I : I  I  I  I : F  F  F  F : F  F  F  F
#define REG_BG2PX              *((vu16*)(REG_BASE + 0x028))  // X Coordinate for BG2 Rotational Background (Write Only)
#define REG_BG3PX              *((vu16*)(REG_BASE + 0x038))  // X Coordinate for BG3 Rotational Background (Write Only)
#define REG_BG2PY              *((vu16*)(REG_BASE + 0x02C))  // Y Coordinate for BG2 Rotational Background (Write Only)
#define REG_BG3PY              *((vu16*)(REG_BASE + 0x03C))  // Y Coordinate for BG3 Rotational Background (Write Only)

//---Windowing Registers---

//---Effects Registers---

//---Sound Controls---

//---DMA Source Registers (Write Only)---

//---Timer Registers---

//---Serial Communication Registers---

//---Keypad Input and Control Registers---

//---Interrupt Registers---

#endif