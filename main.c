/*

*(type*)address == casting address as a type and then derefrencing

*/

#include <math.h>

#include "../include/GBATypes.h"
#include "../include/GBARegisters.h"
#include "../include/GBAGraphics.h"

int main()
{
    setBackground(2,1);
    setGraphicMode(4);
    setScreenBlank(0);

    u16 yellow = add_palette_color(31, 31, 0, 4);
    u16 green = add_palette_color(0, 31, 0, 2);
    u16 blue = add_palette_color(0, 0, 31, 3);
    u16 red = add_palette_color(31, 0, 0, 1);
    u16 white = add_palette_color(31, 31, 31, 0);

    u16 xo = 0;
    /* the buffer we start with */
    vu16 buffer = 0;

    while (true) {
        //draw
        //mode4DrawLine(buffer^1, 0, 0, xo, 0, blue);
        mode4SetPixel(buffer, xo, 0, blue);
        //show
        buffer = flip_buffers(buffer);
        //erase old buffer
        //mode4ClearScreen(buffer^1, white);
        mode4SetPixel(buffer, xo - 1, 0, white);
        //calc
        xo += 1;
        if (xo > 60) xo = 0;

        while(getVCount() != 160){}
    }
}