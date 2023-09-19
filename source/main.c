/*

*(type*)address == casting address as a type and then derefrencing

*/

#include "../include/GBATypes.h"
#include "../include/GBARegisters.h"
#include "../include/GBAGraphics.h"

int main()
{
    setGraphicMode(5);
    setBackground(2, 1);
    setScreenBlank(0);

    // ((unsigned short*)0x06000000)[120+80*240] = 0x001F;
    // ((unsigned short*)0x06000000)[136+80*240] = 0x03E0;
    // ((unsigned short*)0x06000000)[120+96*240] = 0x7C00;

    // mode3SetPixel(1,1,0x001F); // Red
    // mode3SetPixel(1,2,0x03E0); // Green
    // mode3SetPixel(1,3,0x7C00); // Blue

    mode3SetPixel(1,1,0b11111);
    setPage(1);

    while(1)
    {
        // if(getVCount >= 160)
        // {
        //     setPage(0);
        // }
        // if(getVCount <= 80)
        // {
        //     setPage(1);
        // }
    };
    return(0);
}