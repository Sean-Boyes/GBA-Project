/*
    Huge thanks to GBAdev.net for supplying the locations and uses of all of the registers
*/
#ifndef GBA_REG_H
#define GBA_REG_H
#include "../include/GBABase.h"
#include "../include/GBATypes.h"


//---Graphics Hardware Registers 0x04000000 - 0x04000054

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

#define REG_BG0HOFS            *((vu16*)(REG_BASE + 0x010))  // Horizontal scroll co-ordinate for BG0 (Write Only)
#define REG_BG0BOFS            *((vu16*)(REG_BASE + 0x012))  // Vertical scroll co-ordinate for BG0 (Write Only)
#define REG_BG1HOFS            *((vu16*)(REG_BASE + 0x014))  // Horizontal scroll co-ordinate for BG1 (Write Only)
#define REG_BG1VOFS            *((vu16*)(REG_BASE + 0x016))  // Vertical scroll co-ordinate for BG1 (Write Only)
#define REG_BG2HOFS            *((vu16*)(REG_BASE + 0x018))  // Horizontal scroll co-ordinate for BG2 (Write Only)
#define REG_BG2VOFS            *((vu16*)(REG_BASE + 0x01A))  // Vertical scroll co-ordinate for BG2 (Write Only)
#define REG_BG3HOFS            *((vu16*)(REG_BASE + 0x01C))  // Horizontal scroll co-ordinate for BG3 (Write Only)
#define REG_BG3VOFS            *((vu16*)(REG_BASE + 0x01E))  // Vertical scroll co-ordinate for BG3 (Write Only)
    // Bits 0-9 | Scroll value (pixels)

#define REG_BG2PA              *((vu16*)(REG_BASE + 0x020))  // BG2 Read Source Pixel X Increment (Write Only)
#define REG_BG3PA              *((vu16*)(REG_BASE + 0x030))  // BG3 Read Source Pixel X Increment (Write Only)
#define REG_BG2PB              *((vu16*)(REG_BASE + 0x022))  // BG2 Write Destination Pixel X Increment (Write Only)
#define REG_BG3PB              *((vu16*)(REG_BASE + 0x032))  // BG3 Write Destination Pixel X Increment (Write Only)
#define REG_BG2PC              *((vu16*)(REG_BASE + 0x024))  // BG2 Read Source Pixel Y Increment (Write Only)
#define REG_BG3PC              *((vu16*)(REG_BASE + 0x034))  // BG3 Read Source Pixel Y Increment (Write Only)
#define REG_BG2PD              *((vu16*)(REG_BASE + 0x026))  // BG2 Write Destination Pixel Y Increment (Write Only)
#define REG_BG3PD              *((vu16*)(REG_BASE + 0x036))  // BG3 Write Destination Pixel Y Increment (Write Only)
    // Bits 0-7 | Fraction 
    // Bits 8-E | Integer
    // Bit F | Sign bit

#define REG_BG2PX              *((vu16*)(REG_BASE + 0x028))  // X Coordinate for BG2 Rotational Background (Write Only)
#define REG_BG3PX              *((vu16*)(REG_BASE + 0x038))  // X Coordinate for BG3 Rotational Background (Write Only)
#define REG_BG2PY              *((vu16*)(REG_BASE + 0x02C))  // Y Coordinate for BG2 Rotational Background (Write Only)
#define REG_BG3PY              *((vu16*)(REG_BASE + 0x03C))  // Y Coordinate for BG3 Rotational Background (Write Only)
    // Bits 0-7 | Fraction 
    // Bits 8-E | Integer
    // Bit F | Sign bit


//---Windowing Registers---

#define REG_WIN0H              *((vu16*)(REG_BASE + 0x040))  // Window 0 X Coordinates (Write Only)
#define REG_WIN1H              *((vu16*)(REG_BASE + 0x042))  // Window 1 X Coordinates (Write Only)
    // Bits 0-7 | X coordinate for the rightmost side of the window
    // Bits 8-F | X coordinate for the leftmost side of the window

#define REG_WIN0V              *((vu16*)(REG_BASE + 0x044))  // Window 0 V Coordinates (Write Only)
#define REG_WIN1V              *((vu16*)(REG_BASE + 0x046))  // Window 1 V Coordinates (Write Only)
    // Bits 0-7 | Y coordinate for the rightmost side of the window
    // Bits 8-F | Y coordinate for the leftmost side of the window
    
#define REG_WININ              *((vu16*)(REG_BASE + 0x048))  // Inside Window Settings
    // WININ | Bits 0-D
    // Bit 0 | BG0 in win0
    // Bit 1 | BG1 in win0
    // Bit 2 | BG2 in win0
    // Bit 3 | BG3 in win0
    // Bit 4 | Sprites in win0
    // Bit 5 | Blends in win0
    // Bit 8 | BG0 in win1
    // Bit 9 | BG1 in win1
    // Bit A | BG2 in win1
    // Bit B | BG3 in win1
    // Bit C | Sprites in win1
    // Bit D | Blends in win1


#define REG_WINOUT              *((vu16*)(REG_BASE + 0x04A)) // Outside Window and Sprite Window
    // WINOUT | Bits 0-D
    // Bit 0 | BG0 outside
    // Bit 1 | BG1 outside
    // Bit 2 | BG2 outside
    // Bit 3 | BG3 outside
    // Bit 4 | Sprites in win0 might be sprite win
    // Bit 5 | Blends in win0 might be sprite win
    // Bit 8 | BG0 in sprite win
    // Bit 9 | BG1 in sprite win
    // Bit A | BG2 in sprite win
    // Bit B | BG3 in sprite win
    // Bit C | Sprites in sprite win
    // Bit D | Blends in sprite win


//---Effects Registers--- 0x0400004C - 0x04000054

#define REG_MOSAIC              *((vu16*)(REG_BASE + 0X04C)) // V: Sprite Y Size U: Sprite X Size J: BG Y Size I: BG X Size (Write Only)
    // Bits 0-3 | BG X Size
    // Bits 4-7 | BG Y Size
    // Bits 8-B | Sprite X Size
    // Bits C-F | Sprite Y Size

#define REG_BLDCNT              *((vu16*)(REG_BASE + 0x050)) // Blending modes
    // Bit 0 | Blend BG0 (source)
    // Bit 1 | Blend BG1 (source)
    // Bit 2 | Blend BG2 (source)
    // Bit 3 | Blend BG3 (source)
    // Bit 4 | Blend sprites (source)
    // Bit 5 | Blend backdrop (source)
    // Bits 6-7 | Blend Mode (00: All effects off 01: Alpha blend 10: Lighten 11: Darken)
    // Bit 8 | Blend BG0 (target)
    // Bit 9 | Blend BG1 (target)
    // Bit A | Blend BG2 (target)
    // Bit B | Blend BG3 (target)
    // Bit C | Blend sprites (target)
    // Bit D | Blend backdrop (target)

#define REG_BLDALPHA            *((vu16*)(REG_BASE + 0x052)) // Write Only
    // Bits 0-4 | Coefficient B, target pixel (layer below)
    // Bits 8-C | Coefficient A, source pixel (layer above)

#define REG_BLDY                *((vu16*)(REG_BASE + 0x054)) // Write Only
    // Bits 0-4 | The lighten / Darken value


//---Sound Controls--- 0x040000060 - 0x0400000A6

#define REG_SOUND1CNT_L         *((vu16*)(REG_BASE + 0x060)) // Sound 1 Sweep control
    // Bits 0-2 | Number of sweep shifts | T = T +- T / (2n)
    // Bit 3 | Sweep increase or decrease
    // Bits 4-6 | Sweep Time

#define REG_SOUND1CNT_H         *((vu16*)(REG_BASE + 0x062)) // Sound 1 length, wave duty and evelope control
    // Bits 0-5 | Sound length (Write Only) | (64 - value) * (1 / 256) seconds
    // Bits 6-7 | Wave duty cycle, percentage on
    // Bits 8-A | Evelope step time | value * (1 / 64) seconds
    // Bit B | Evelope mode (0: decreases 1: increases)
    // Bits C-F | Initial Envelope value

#define REG_SOUND1CNT_X         *((vu16*)(REG_BASE + 0x064)) // Sound 1 Frequency, reset and loop control
    // Bits 0-A | Sound Frequency (Write Only) | F(hz) = 4194304 / (32 * (2048 - value))
    // Bit E | Timed sound (0: sound 1 is played continuously 1: sound is played for the specified length)
    // Bit F | Sound reset (Write Only)

#define REG_SOUND2CNT_L         *((vu16*)(REG_BASE + 0x068)) // Sound 2 Length, wave duty
    // Bits 0-5 | Sound length (Write Only) | (64 - value) * (1 / 256) seconds
    // Bits 6-7 | Wave duty cycle, percentage on
    // Bits 8-A | Evelope step time | value * (1 / 64) seconds
    // Bit B | Evelope mode (0: decreases 1: increases)
    // Bits C-F | Initial Envelope value
#define REG_SOUND2CNT_H         *((vu16*)(REG_BASE + 0x06C)) // Sound 2 Frequency, reset and loop control
    // Bits 0-A | Sound Frequency (Write Only) | F(hz) = 4194304 / (32 * (2048 - value))
    // Bit E | Timed sound (0: sound 1 is played continuously 1: sound is played for the specified length)
    // Bit F | Sound reset (Write Only)

#define REG_SOUND3CNT_L         *((vu16*)(REG_BASE + 0x070)) // Sound 3 Enable and wave ram bank control
    // Bit 5 | Bank Mode
    // Bit 6 | Bank Select
    // Bit 7 | Sound Channel 3 output enable

#define REG_SOUND3CNT_H         *((vu16*)(REG_BASE + 0x072)) // Sound 3 Sound length and output level control
    // Bits 0-7 | Sound length (Write Only) | Note length (in seconds) * 256
    // Bits D-F | Output volune ratio

#define REG_SOUND3CNT_X         *((vu16*)(REG_BASE + 0x074)) // Sound 3 Frequency, reset and loop control
    // Bits 0-A | Sound Frequency (Write Only) | F(hz) = 4194304 / (32 * (2048 - value))
    // Bit E | Timed sound (0: sound 1 is played continuously 1: sound is played for the specified length)
    // Bit F | Sound reset (Write Only)

#define REG_SOUND4CNT_L         *((vu16*)(REG_BASE + 0x078)) // Sound 4 Length, output level and evelope control
    // Bits 0-5 | Sound length (Write Only) | (64 - value) * (1 / 256) seconds
    // Bits 6-7 | Wave duty cycle, percentage on
    // Bits 8-A | Evelope step time | value * (1 / 64) seconds
    // Bit B | Evelope mode (0: decreases 1: increases)
    // Bits C-F | Initial Envelope value

#define REG_SOUND4CNT_H         *((vu16*)(REG_BASE + 0x07C)) // Sound 4 Noise parameters, reset and loop control
    // Bits 0-2 | Clock divide frequency
    // Bit 3 | Counter stages
    // Bits 4-7 | Counter Pre-Stepper frequency
    // Bit E | Timed sound (0: sound 4 is played continuously 1: sound is played for that specified length)
    // Bit F | Sound reset (Write Only)

#define REG_SOUNDCNT_L          *((vu16*)(REG_BASE + 0x080)) // Sound 1-4 Output level and Stereo control
    // Bits 0-2 | DMG Left Volume
    // Bit 3 | Vin Left on/off
    // Bits 4-6 | DMG Right Volume
    // Bit 7 | Vin Right on/off
    // Bit 8 | DMG Sound 1 to left output
    // Bit 9 | DMG Sound 2 to left output
    // Bit A | DMG Sound 3 to left output
    // Bit B | DMG Sound 4 to left output
    // Bit C | DMG Sound 1 to right output
    // Bit D | DMG Sound 2 to right output
    // Bit E | DMG Sound 3 to right output
    // Bit F | DMG Sound 4 to right output

#define REG_SOUNDCNT_H          *((vu16*)(REG_BASE + 0x082)) // Direct Sound control and Sound 1-4 output ratio
    // Bits 0-1 | Output Sound Ratio for channels 1-4
    // Bit 2 | Direct sound A output ratio
    // Bit 3 | Direct sound B output ratio
    // Bit 8 | Direct sound A to right output
    // Bit 9 | Direct sound A to right output
    // Bit A | Direct sound A sampling rate timer (timer 0 or 1)
    // Bit B | Direct sound A FIFO reset (Write Only)
    // Bit C | Direct sound B to right output
    // Bit D | Direct sound B to left output
    // Bit E | Direct sound B sampling rate timer (timer 0 or 1)
    // Bit F | Direct sound B FIFO reset (Write Only)

#define REG_SOUNDCNT_X          *((vu16*)(REG_BASE + 0x084)) // Master sound enable and Sound 1-4 play status
    // Bit 0 | DMG sound 1 Status (Read Only) (0: Stopped 1:Playing)
    // Bit 1 | DMG sound 2 Status (Read Only) (0: Stopped 1:Playing)
    // Bit 2 | DMG sound 3 Status (Read Only) (0: Stopped 1:Playing)
    // Bit 3 | DMG sound 4 Status (Read Only) (0: Stopped 1:Playing)
    // Bit 7 | All sound circuit enable

#define REG_SOUNDBIAS           *((vu16*)(REG_BASE + 0x088)) // Sound bias and Amplitude resolution control
    // Bits 1-9 | PWM bias value, controled by the BIOS
    // Bits E-F | Amplitude resolutions

// These registers together contain four 4-bit wave RAM sample for sound channel 3 (4 bytes each)
#define REG_WAVE_RAM0_L         *((vu16*)(REG_BASE + 0x090)) // Sound 3 sample 0-3
#define REG_WAVE_RAM0_H         *((vu16*)(REG_BASE + 0x092)) // Sound 3 sample 4-7
#define REG_WAVE_RAM1_L         *((vu16*)(REG_BASE + 0x094)) // Sound 3 sample 8-11
#define REG_WAVE_RAM1_H         *((vu16*)(REG_BASE + 0x096)) // Sound 3 sample 12-15
#define REG_WAVE_RAM2_L         *((vu16*)(REG_BASE + 0x098)) // Sound 3 sample 16-19
#define REG_WAVE_RAM2_H         *((vu16*)(REG_BASE + 0x09A)) // Sound 3 sample 20-23
#define REG_WAVE_RAM3_L         *((vu16*)(REG_BASE + 0x09C)) // Sound 3 sample 23-27
#define REG_WAVE_RAM3_H         *((vu16*)(REG_BASE + 0x09E)) // Sound 3 sample 28-31

// These are locations of the Direct Sound 8-bit FIFO
#define REG_FIFO_A_L            *((vu16*)(REG_BASE + 0x0A0)) // Direct Sound channel A sampless 0-1 (Write Only)
#define REG_FIFO_A_H            *((vu16*)(REG_BASE + 0x0A2)) // Direct Sound channel A sampless 2-3 (Write Only)
#define REG_FIFO_B_L            *((vu16*)(REG_BASE + 0x0A4)) // Direct Sound channel B sampless 0-1 (Write Only)
#define REG_FIFO_B_H            *((vu16*)(REG_BASE + 0x0A6)) // Direct Sound channel B sampless 2-3 (Write Only)


//---DMA Soure Registers--- (0x040000B0, 0x040000BC, 0x040000C8, 0x040000D4)

#define REG_DMA0SAD             *((vu16*)(REG_BASE + 0x0B0)) // DMA0 Source Adress (Write Only)
    // Bits 0-26 | 27-bit
#define REG_DMA1SAD             *((vu16*)(REG_BASE + 0x0BC)) // DMA1 Source Adress (Write Only)
#define REG_DMA2SAD             *((vu16*)(REG_BASE + 0x0C8)) // DMA2 Source Adress (Write Only)
#define REG_DMA3SAD             *((vu16*)(REG_BASE + 0x0D4)) // DMA3 Source Adress (Write Only)
    // Bits 0-27 | 28-bit


//---DMA Destination Registers--- (0x040000B4, 0x040000C0, 0x040000CC, 0x040000D8)

#define REG_DMA0DAD             *((vu16*)(REG_BASE + 0x0B4)) // DMA0 Destination Address
#define REG_DMA1DAD             *((vu16*)(REG_BASE + 0x0C0)) // DMA1 Destination Address
#define REG_DMA2DAD             *((vu16*)(REG_BASE + 0x0CC)) // DMA2 Destination Address
    // Bits 0-26 | 27-bit
#define REG_DMA3DAD             *((vu16*)(REG_BASE + 0x0D8)) // DMA3 Destination Address
    // Bits 0-27 | 28-bit


//---DMA Count Registers--- (0x040000B8, 0x040000C4, 0x040000D0, 0x040000DC)

#define REG_DMA0CNT_L           *((vu16*)(REG_BASE + 0x0B8)) // DMA0 Count Register
#define REG_DMA1CNT_L           *((vu16*)(REG_BASE + 0x0B8)) // DMA1 Count Register
#define REG_DMA2CNT_L           *((vu16*)(REG_BASE + 0x0B8)) // DMA2 Count Register
#define REG_DMA3CNT_L           *((vu16*)(REG_BASE + 0x0B8)) // DMA3 Count Register
    // Bits 0-D | Number of words or halfwords to copy


//---DMA Control Registers--- (0x040000BA, 0x040000C6, 0x040000D2, 0x040000DE)

#define REG_DMA0CNT_H           *((vu16*)(REG_BASE + 0x0BA)) // DMA0 Control Register
#define REG_DMA1CNT_H           *((vu16*)(REG_BASE + 0x0C6)) // DMA1 Control Register
#define REG_DMA2CNT_H           *((vu16*)(REG_BASE + 0x0D2)) // DMA2 Control Register
#define REG_DMA3CNT_H           *((vu16*)(REG_BASE + 0x0DE)) // DMA3 Control Register


//---Timer Registers--- (0x04000100 - 0x0400010E)

#define REG_TM0D                *((vu16*)(REG_BASE + 0x100)) // Timer 0 Data
#define REG_TM1D                *((vu16*)(REG_BASE + 0x104)) // Timer 1 Data
#define REG_TM2D                *((vu16*)(REG_BASE + 0x108)) // Timer 2 Data
#define REG_TM3D                *((vu16*)(REG_BASE + 0x10C)) // Timer 3 Data
    // Bits 0-F | Current count of the timer

#define REG_TM0CNT              *((vu16*)(REG_BASE + 0x102)) // Timer 0 Control
#define REG_TM1CNT              *((vu16*)(REG_BASE + 0x106)) // Timer 1 Control
#define REG_TM2CNT              *((vu16*)(REG_BASE + 0x10A)) // Timer 2 Control
#define REG_TM3CNT              *((vu16*)(REG_BASE + 0x10E)) // Timer 3 Control
    // Bits 0-1 | Frequency at which the timer updates
    // Bit 2 | Cascade
    // Bit 6 | Generate an interrupt on overflow
    // Bit 7 | Enable the timer


//---Serial Communication Registers--- (0x04000120 - 0x0400012A)

#define REG_SCD0                *((vu16*)(REG_BASE + 0x120)) // Master/Slave 0 destination (Read Only)
#define REG_SCD1                *((vu16*)(REG_BASE + 0x122)) // Slave 1 destination (Read Only)
#define REG_SCD2                *((vu16*)(REG_BASE + 0x124)) // Slave 2 destination (Read Only)
#define REG_SCD3                *((vu16*)(REG_BASE + 0x126)) // Slave 3 destination (Read Only)
    // Bits 0-F | The data recieved

#define REG_SCCNT_L             *((vu16*)(REG_BASE + 0x128)) // Serial Communication channel control register
    // Bits 0-1 | Baud rate
    // Bits 2-3 | SI (bit 2) & SD (bit 3) line direct access
    // Bits 4-5 | ID of GBA
    // Bit 6 | Error (1: ON) (Read Only)
    // Bit 7 | Start Transfer (1: ON)
    // Bits C-D | Comm Mode
    // Bit E | Enable Comm Interupt

#define REG_SCCNT_H             *((vu16*)(REG_BASE + 0x12A)) // Serial Communication Source Register
    // Bits 0-F | The data to be sent over the link cable

//---Keypad Input and Control Registers--- (0x04000130 - 0x04000132)
#define REG_KEYINPUT            *((vu16*)(REG_BASE + 0x130)) // Keypad Input (Read Only)
    // 0: Pressed | 1: Not Pressed
    // Bit 0 | A button
    // Bit 1 | B button
    // Bit 2 | Select button
    // Bit 3 | Start button
    // Bit 4 | D-pad Right
    // Bit 5 | D-pad Left
    // Bit 6 | D-pad Up
    // Bit 7 | D-pad Down
    // Bit 8 | Right shoulder button
    // Bit 9 | Left shoulder button

#define REG_KEYCNT              *((vu16*)(REG_BASE + 0x132)) // Key Control
    // Bit 0 | A button
    // Bit 1 | B button
    // Bit 2 | Select button
    // Bit 3 | Start button
    // Bit 4 | D-pad Right
    // Bit 5 | D-pad Left
    // Bit 6 | D-pad Up
    // Bit 7 | D-pad Down
    // Bit 8 | Right shoulder button
    // Bit 9 | Left shoulder button
    // Bit E | Generate interrup on keypress
    // Bit F | Interrupt "type" (0: generated if any specified key are pressed, 1: generated if all specified keys are pressed)

#define REG_RCNT                *((vu16*)(REG_BASE + 0x134)) // Dirrect access to line of the link port
    // Unknown as of Writing this (Sep. 2023)

//---Interrupt Registers---
#define REG_IE                  *((vu16*)(REG_BASE + 0x200)) // Interrupt Enable Register
    // 0: disable | 1:enable
    // Bit 0 | VBlank Interrupt
    // Bit 1 | HBlank Interrupt
    // Bit 2 | VCount Interrupt
    // Bit 3 | Timer 0 Interrupt
    // Bit 4 | Timer 1 Interrupt
    // Bit 5 | Timer 2 Interrupt
    // Bit 6 | Timer 3 Interrupt
    // Bit 7 | Serial Communication Interrupt
    // Bit 8 | DMA0 Interrupt
    // Bit 9 | DMA1 Interrupt
    // Bit A | DMA2 Interrupt
    // Bit B | DMA3 Interrupt
    // Bit C | Key Interrupt
    // Bit D | Cartridge Interrupt

#define REG_IF                  *((vu16*)(REG_BASE + 0x202)) // Interrupt Flags
    // Bit 0 | VBlank Interrupt
    // Bit 1 | HBlank Interrupt
    // Bit 2 | VCount Interrupt
    // Bit 3 | Timer 0 Interrupt
    // Bit 4 | Timer 1 Interrupt
    // Bit 5 | Timer 2 Interrupt
    // Bit 6 | Timer 3 Interrupt
    // Bit 7 | Serial Communication Interrupt
    // Bit 8 | DMA0 Interrupt
    // Bit 9 | DMA1 Interrupt
    // Bit A | DMA2 Interrupt
    // Bit B | DMA3 Interrupt
    // Bit C | Key Interrupt
    // Bit D | Cartridge Interrupt

#define REG_WAITCNT             *((vu16*)(REG_BASE + 0x204)) // Wait State Control
    // Bits 0-1 | SRAM wait state
    // Bits 2-3 | Bank 0x08000000 initial wait state
    // Bit 4 | Bank 0x08000000 subsequent wait state
    // Bits 5-6 | Bank 0x0A000000 initial wait state
    // Bit 7 | Bank 0x0A000000 subsequent wait state
    // Bits 8-9 | Bank 0x0C000000 initial wait state
    // Bit A | Bank 0x0C000000 subsequent wait state
    // Bits B-C | Cart clock. Don't touch.
    // Bit E | Prefetch
    // Bit F | Game Pak type

#define REG_IME                 *((vu16*)(REG_BASE + 0x208)) // Intterupt Master Enable
    // 0: all interrupts disabled | 1: enabled
    // Bit 0 | Master

#define REG_HALTCNT             *((vu16*)(REG_BASE + 0x300))
    // Bit F | Mode
    // Bit E | Power Down

#endif