/*

*(type*)address == casting address as a type and then derefrencing

*/

#include <math.h>

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
    // mode3SetPixel(1,1,0xFFFF); // White

    // mode3Line(1,1,10,10,0x7C00);

    // from 1,1 to 3,3

    // for (u16 x = 0; x < 24; x++)
    // {
    //     for (u16 y = 0; y < 16; y++)
    //     {
    //         mode3DrawLine(x*24,y*16,SCREENWIDTH-1,SCREENHEIGHT-1,0x001F);
    //         mode3DrawLine(x*24,y*16,0,SCREENHEIGHT-1,0x03E0);
    //         mode3DrawLine(x*24,y*16,SCREENWIDTH-1,0,0x7C00);
    //         mode3DrawLine(x*24,y*16,0,0,0x7777);
    //     }
    // }
    // mode3SetPixel(0,0,0);
    // mode3SetPixel(239,159,0);
    // mode3SetPixel(0,159,0);
    // mode3SetPixel(239,0,0);

    // Vertex test

    u16 pointA[] = {100,110};
    u16 pointB[] = {100,20};
    u16 pointC[] = {25,20};
    u16 pointD[] = {25,110};
    u16 pointE[] = {100,110};
    u16 pointF[] = {100,20};
    u16 pointG[] = {25,20};
    u16 pointH[] = {25,110};

    u16 oldpointA[] = {100,110};
    u16 oldpointB[] = {100,20};
    u16 oldpointC[] = {25,20};
    u16 oldpointD[] = {25,110};
    u16 oldpointE[] = {100,110};
    u16 oldpointF[] = {100,20};
    u16 oldpointG[] = {25,20};
    u16 oldpointH[] = {25,110};
    float t = 0;
    float xScale = 40;
    float yScale = 10;
    u16 buffer = 0;

    u16 colour1 = 0x001F;
    u16 colour2 = 0x0310;
    u16 colour3 = 0x3100;
    u16 colour4 = 0xF100;
    u16 blank   = 0x0000;

    for (u32 i = VRAM; i < VRAM+0x17ff0; i++)
    {
        set16Bit(i, 0, 16, 0x0000);
    }
    setBackgroundScale(2, 0x1 << 7, 0x1 << 7);
    // set16Bit(0x04000020, 0, 16, 0x1 << 7);
    // set16Bit(0x04000026, 0, 16, 0x1 << 7);

    while(1)
    {   
        // mode5SetPixel(buffer, 0,0,colour1);
        // mode5SetPixel(buffer, (SCREENWIDTH/2)-1,0,colour1);
        // mode5SetPixel(buffer, (SCREENWIDTH/2)-1,(SCREENHEIGHT/2)-1,colour1);
        // mode5SetPixel(buffer, 0,(SCREENHEIGHT/2)-1,colour1);

        // draw cube
        mode5DrawLine(buffer,pointA[0],pointA[1],pointB[0],pointB[1],colour1); 
        mode5DrawLine(buffer,pointB[0],pointB[1],pointC[0],pointC[1],colour2); 
        mode5DrawLine(buffer,pointC[0],pointC[1],pointD[0],pointD[1],colour2);
        mode5DrawLine(buffer,pointD[0],pointD[1],pointA[0],pointA[1],colour1);
        mode5DrawLine(buffer,pointE[0],pointE[1],pointF[0],pointF[1],colour3);
        mode5DrawLine(buffer,pointF[0],pointF[1],pointG[0],pointG[1],colour3);
        mode5DrawLine(buffer,pointG[0],pointG[1],pointH[0],pointH[1],colour4);
        mode5DrawLine(buffer,pointH[0],pointH[1],pointE[0],pointE[1],colour4);
        mode5DrawLine(buffer,pointE[0],pointE[1],pointA[0],pointA[1],colour1);
        mode5DrawLine(buffer,pointF[0],pointF[1],pointB[0],pointB[1],colour3);
        mode5DrawLine(buffer,pointG[0],pointG[1],pointC[0],pointC[1],colour2);
        mode5DrawLine(buffer,pointH[0],pointH[1],pointD[0],pointD[1],colour4);

        buffer = flip_buffers(buffer);

        mode5DrawLine(buffer,oldpointA[0],oldpointA[1],oldpointB[0],oldpointB[1],blank);
        mode5DrawLine(buffer,oldpointB[0],oldpointB[1],oldpointC[0],oldpointC[1],blank);
        mode5DrawLine(buffer,oldpointC[0],oldpointC[1],oldpointD[0],oldpointD[1],blank);
        mode5DrawLine(buffer,oldpointD[0],oldpointD[1],oldpointA[0],oldpointA[1],blank);
        mode5DrawLine(buffer,oldpointE[0],oldpointE[1],oldpointF[0],oldpointF[1],blank);
        mode5DrawLine(buffer,oldpointF[0],oldpointF[1],oldpointG[0],oldpointG[1],blank);
        mode5DrawLine(buffer,oldpointG[0],oldpointG[1],oldpointH[0],oldpointH[1],blank);
        mode5DrawLine(buffer,oldpointH[0],oldpointH[1],oldpointE[0],oldpointE[1],blank);
        mode5DrawLine(buffer,oldpointE[0],oldpointE[1],oldpointA[0],oldpointA[1],blank);
        mode5DrawLine(buffer,oldpointF[0],oldpointF[1],oldpointB[0],oldpointB[1],blank);
        mode5DrawLine(buffer,oldpointG[0],oldpointG[1],oldpointC[0],oldpointC[1],blank);
        mode5DrawLine(buffer,oldpointH[0],oldpointH[1],oldpointD[0],oldpointD[1],blank);
        
        //take old values
        oldpointA[0] = pointA[0];
        oldpointB[0] = pointB[0];
        oldpointC[0] = pointC[0];
        oldpointD[0] = pointD[0];
        oldpointA[1] = pointA[1];
        oldpointB[1] = pointB[1];
        oldpointC[1] = pointC[1];
        oldpointD[1] = pointD[1];
        oldpointE[0] = pointE[0];
        oldpointF[0] = pointF[0];
        oldpointG[0] = pointG[0];
        oldpointH[0] = pointH[0];
        oldpointE[1] = pointE[1];
        oldpointF[1] = pointF[1];
        oldpointG[1] = pointG[1];
        oldpointH[1] = pointH[1];
        // left to right
        pointA[0] = xScale*cos(t) + 60; 
        pointB[0] = xScale*cos(t+1.57) + 60;
        pointC[0] = xScale*cos(t+3.14) + 60; 
        pointD[0] = xScale*cos(t+4.71) + 60; 

        pointA[1] = yScale*sin(t) + 60; 
        pointB[1] = yScale*sin(t+1.57) + 60;
        pointC[1] = yScale*sin(t+3.14) + 60; 
        pointD[1] = yScale*sin(t+4.71) + 60; 

        pointE[0] = xScale*cos(t) + 60; 
        pointF[0] = xScale*cos(t+1.57) + 60;
        pointG[0] = xScale*cos(t+3.14) + 60; 
        pointH[0] = xScale*cos(t+4.71) + 60; 

        pointE[1] = yScale*sin(t) + 20; 
        pointF[1] = yScale*sin(t+1.57) + 20;
        pointG[1] = yScale*sin(t+3.14) + 20; 
        pointH[1] = yScale*sin(t+4.71) + 20; 

        t += .01;
        
        while(getVCount() != 160){}; // VSync 60fps
    };
    return(0);
}