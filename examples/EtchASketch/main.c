/*

*(type*)address == casting address as a type and then derefrencing

*/

#include <math.h>

#include "../include/GBATypes.h"
#include "../include/GBARegisters.h"
#include "../include/GBAGraphics.h"

int main()
{
    setGraphicMode(3);
    setBackground(2, 1);
    setScreenBlank(0);

    // ((unsigned short*)0x06000000)[120+80*240] = 0x001F;
    // ((unsigned short*)0x06000000)[136+80*240] = 0x03E0;
    // ((unsigned short*)0x06000000)[120+96*240] = 0x7C00;

    // mode3SetPixel(1,1,0x001F); // Red
    // mode3SetPixel(1,2,0x03E0); // Green
    // mode3SetPixel(1,3,0x7C00); // Blue
    // mode3SetPixel(1,1,0xFFFF); // White

    // mode3Line(1,1,10,10,0x7C00);

    // Paint Screen White
    for(u16 i = 0; i <= SCREENWIDTH; ++i)
    {
        for(u16 ii = 0; ii <= SCREENHEIGHT; ++ii)
        {
            mode3SetPixel(i,ii,0xFFFF);
        }
    }

    // Vertex test

    struct point {
        u32 xPos;
        u32 yPos;
        u32 zPos;
    };

    u32 frameCount = 0;

    u32 t = 80<<8;
    u32 r = 120<<8;

    while(1)
    {   
        // mode3SetPixel(t>>8,r>>8,0xFFFF);
        mode3SetPixel(t>>8,r>>8,0x0000);
        if(frameCount==1)
        {            
            if (read16Bit(REG_KEYINPUT, 1,1) == 1)
            {
                mode3SetPixel(t>>8,r>>8,0xFFFF);
            }
            if (read16Bit(REG_KEYINPUT, 4,1) == 0) t = t + 1;
            if (read16Bit(REG_KEYINPUT, 5,1) == 0) t = t - 1;
            if (read16Bit(REG_KEYINPUT, 6,1) == 0) r = r + 1;
            if (read16Bit(REG_KEYINPUT, 7,1) == 0) r = r - 1;
            if (read16Bit(REG_KEYINPUT, 0,1) == 0) 
            {
                for(u16 i = 0; i <= SCREENWIDTH; ++i)
                {
                    for(u16 ii = 0; ii <= SCREENHEIGHT; ++ii)
                    {
                        mode3SetPixel(i,ii,0xFFFF);
                    }
                }
            }

        }

        
        
        
        while(getVBlankStatus()){}; // VSync
        frameCount = frameCount*(frameCount >=60) + 1;
        };
    return(0);
}