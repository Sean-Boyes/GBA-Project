#ifndef GBA_Backgrounds
#define GBA_Backgrounds

#include <stdbool.h>

#include "GBABase.h"
#include "GBARegisters.h"
#include "GBATypes.h"


// Scroll co-ordinates
void setHScroll(u8 backgound, u16 value)
{
    switch(backgound)
    {
        case 0: set16Bit(REG_BG0HOFS, 0, 9, value); break;
        case 1: set16Bit(REG_BG1HOFS, 0, 9, value); break;
        case 2: set16Bit(REG_BG2HOFS, 0, 9, value); break;
        case 3: set16Bit(REG_BG3HOFS, 0, 9, value); break;
    }
}
void setVScroll(u8 backgound, u16 value)
{
    switch(backgound)
    {
        case 0: set16Bit(REG_BG0VOFS, 0, 9, value); break;
        case 1: set16Bit(REG_BG1VOFS, 0, 9, value); break;
        case 2: set16Bit(REG_BG2VOFS, 0, 9, value); break;
        case 3: set16Bit(REG_BG3VOFS, 0, 9, value); break;
    }
}


#endif