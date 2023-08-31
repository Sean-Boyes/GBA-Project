/*

*(type*)address == casting address as a type and then derefrencing

*/

#include "../include/GBATypes.h"
#include "../include/GBAVideo.h"

int main()
{
    int reg = DCNT_BG2 | DCNT_MODE3;
    
    *(unsigned int*)REG_BASE = reg;

    //*(unsigned int*)0x04000000 = 0x0403;

    ((unsigned short*)0x06000000)[120+80*240] = 0x001F;
    ((unsigned short*)0x06000000)[136+80*240] = 0x03E0;
    ((unsigned short*)0x06000000)[120+96*240] = 0x7C00;

    while(1);
    return(0);
}