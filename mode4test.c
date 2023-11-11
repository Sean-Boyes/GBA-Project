/*
 * square2.c
 * this program attempts to draw a square in a loop
 */

#include "GBABase.h"
#include "GBAGraphics.h"
#include "GBATypes.h"

/* the main function */
int main() {
    /* we set the mode to mode 4 with bg2 on */
    setScreenBlank(0);
    setGraphicMode(4);
    setBackground(2,1);
    //set16Bit(MEM_PAL, 0, 16, 0xFFFF);
    set16Bit(BACK_BUFFER, 0, 1, 1);
    set16Bit(FRONT_BUFFER, 0, 1, 1);

    /* add to the palette */
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
        mode4SetPixel(buffer^1, xo, 0, blue);
        //show
        buffer = flip_buffers(buffer);
        //erase old buffer
        //mode4ClearScreen(buffer^1, white);
        mode4SetPixel(buffer^1, xo - 1, 0, white);
        //calc
        xo += 1;
        if (xo > 100) xo = 0;
    }
}
