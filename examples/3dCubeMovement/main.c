/*

*(type*)address == casting address as a type and then derefrencing

*/

#include <math.h>

#include "../include/GBATypes.h"
#include "../include/GBARegisters.h"
#include "../include/GBAGraphics.h"
#include "../include/GBAMath.h"
#include "../include/GBA3D.h"


int main()
{
    // setup
    setGraphicMode(5);
    setBackground(2, 1);
    setScreenBlank(0);
    setBackgroundScale(2, 1<<7, 1<<7);
    s8 buffer = 0;
    u16 frame = 1;

    // colours
    u16 black = 0x0000;
    u16 white = 0xFFFF;

    struct camera camera = createCamera(0,0,150,0,0,0);

    // create object
    u16 scalar = 50;

    struct point3d p1 = createVertex(scalar,scalar,scalar);
    struct point3d p2 = createVertex(-scalar,scalar,scalar);
    struct point3d p3 = createVertex(-scalar,-scalar,scalar);
    struct point3d p4 = createVertex(scalar,-scalar,scalar);
    struct point3d p5 = createVertex(scalar,scalar,-scalar);
    struct point3d p6 = createVertex(-scalar,scalar,-scalar);
    struct point3d p7 = createVertex(-scalar,-scalar,-scalar);
    struct point3d p8 = createVertex(scalar,-scalar,-scalar);

    struct polygon object1[] = {createPolygon(createVertex(10,10,10), createVertex(-10,10,10), createVertex(-10,-10,10)), 
                                createPolygon(createVertex(-10,-10,10), createVertex(-10,10,10), createVertex(-10,10,-10)), 
                                createPolygon(createVertex(10,10,10), createVertex(-10,10,10), createVertex(-10,10,-10))};
    u16 cubePolyCount = 12;
    struct polygon cube[] = {createPolygon(p1,p2,p3),createPolygon(p1,p3,p4), // front
                             createPolygon(p5,p6,p7),createPolygon(p5,p7,p8), // back
                             createPolygon(p3,p4,p7),createPolygon(p4,p7,p8), // top
                             createPolygon(p1,p2,p5),createPolygon(p2,p5,p6), // bottom
                             createPolygon(p1,p4,p5),createPolygon(p4,p5,p8), // right
                             createPolygon(p2,p3,p6),createPolygon(p3,p6,p7)  // left
                             };

    struct point3d origin = createVertex(0,0,0);
    struct point3d offsetOrigin = createVertex(0,100,0);

    while(1)
    {   
        // Clear screen
        for (u32 i = 0; i < (SCREENHEIGHT * SCREENWIDTH); i++)
        {
            mode5SetPixel(buffer, i, 0, white);
        } 
        
        drawObject(buffer, cube, cubePolyCount, camera, origin);
        drawObject(buffer, cube, cubePolyCount, camera, offsetOrigin);

        while(getVCount() != 5){}

        // flip buffer
        buffer = flip_buffers(buffer);
        frame += 1;
        if (frame > 60) frame = 1;

        // TODO: define as macros
        if (frame % 1 == 0)
        {
            if (read16Bit(REG_KEYINPUT, 8,1) == 0) 
            {
                // turn right
                camera.roll += (5) * (3.1415/180);
            }
            if (read16Bit(REG_KEYINPUT, 9,1) == 0) 
            {
                // turn left
                camera.roll -= (5) * (3.1415/180);
            }
            if (read16Bit(REG_KEYINPUT, 6,1) == 0) 
            {
                // forward
                camera.z += (10 * cos(camera.roll));
                camera.x += (10 * sin(camera.roll));
            }
            if (read16Bit(REG_KEYINPUT, 7,1) == 0) 
            {
                // back
                camera.z -= (10 * cos(camera.roll));
                camera.x -= (10 * sin(camera.roll));
            }
            if (read16Bit(REG_KEYINPUT, 4,1) == 0) 
            {
                // right
                camera.z += (10 * cos(camera.roll+1.57));
                camera.x += (10 * sin(camera.roll+1.57));
            }
            if (read16Bit(REG_KEYINPUT, 5,1) == 0) 
            {
                // left
                camera.z -= (10 * cos(camera.roll+1.57));
                camera.x -= (10 * sin(camera.roll+1.57));
            }
        }
    };
    return(0);
}