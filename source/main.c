/*

*(type*)address == casting address as a type and then derefrencing

*/

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

    while(1);
    return(0);
}