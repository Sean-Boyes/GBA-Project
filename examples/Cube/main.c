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

    for(u16 i = 0; i <= SCREENWIDTH; ++i)
    {
        for(u16 ii = 0; ii <= SCREENHEIGHT; ++ii)
        {
            mode3SetPixel(i,ii,0xFFFF);
        }
    }

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

    u16 pointA[] = {200,140};
    u16 pointB[] = {200,70};
    u16 pointC[] = {50,70};
    u16 pointD[] = {50,140};
    u16 pointE[] = {200,140};
    u16 pointF[] = {200,70};
    u16 pointG[] = {50,70};
    u16 pointH[] = {50,140};

    float t = 0;
    float xScale = 50;
    float yScale = 10;

    // mode3DrawLine(1,1,240,2,0x0000);
    // mode3DrawLine(240,2,1,1,0x0000);
    // mode3DrawLine(1,1,3,180,0x0000);
    // mode3DrawLine(3,180,1,1,0x0000);

    while(1)
    {   


        mode3DrawLine(pointA[0],pointA[1],pointB[0],pointB[1],0xFFFF);
        mode3DrawLine(pointB[0],pointB[1],pointC[0],pointC[1],0xFFFF);
        mode3DrawLine(pointC[0],pointC[1],pointD[0],pointD[1],0xFFFF);
        mode3DrawLine(pointD[0],pointD[1],pointA[0],pointA[1],0xFFFF);
        mode3DrawLine(pointE[0],pointE[1],pointF[0],pointF[1],0xFFFF);
        mode3DrawLine(pointF[0],pointF[1],pointG[0],pointG[1],0xFFFF);
        mode3DrawLine(pointG[0],pointG[1],pointH[0],pointH[1],0xFFFF);
        mode3DrawLine(pointH[0],pointH[1],pointE[0],pointE[1],0xFFFF);
        mode3DrawLine(pointE[0],pointE[1],pointA[0],pointA[1],0xFFFF);
        mode3DrawLine(pointF[0],pointF[1],pointB[0],pointB[1],0xFFFF);
        mode3DrawLine(pointG[0],pointG[1],pointC[0],pointC[1],0xFFFF);
        mode3DrawLine(pointH[0],pointH[1],pointD[0],pointD[1],0xFFFF);

        pointA[0] = xScale*cos(t) + 120; 
        pointB[0] = xScale*cos(t+1.57) + 120;
        pointC[0] = xScale*cos(t+3.14) + 120; 
        pointD[0] = xScale*cos(t+4.71) + 120; 

        pointA[1] = yScale*sin(t) + 110; 
        pointB[1] = yScale*sin(t+1.57) + 110;
        pointC[1] = yScale*sin(t+3.14) + 110; 
        pointD[1] = yScale*sin(t+4.71) + 110; 

        pointE[0] = xScale*cos(t) + 120; 
        pointF[0] = xScale*cos(t+1.57) + 120;
        pointG[0] = xScale*cos(t+3.14) + 120; 
        pointH[0] = xScale*cos(t+4.71) + 120; 

        pointE[1] = yScale*sin(t) + 40; 
        pointF[1] = yScale*sin(t+1.57) + 40;
        pointG[1] = yScale*sin(t+3.14) + 40; 
        pointH[1] = yScale*sin(t+4.71) + 40; 

        mode3DrawLine(pointA[0],pointA[1],pointB[0],pointB[1],0x001F);
        mode3DrawLine(pointB[0],pointB[1],pointC[0],pointC[1],0x03E0);
        mode3DrawLine(pointC[0],pointC[1],pointD[0],pointD[1],0x7C00);
        mode3DrawLine(pointD[0],pointD[1],pointA[0],pointA[1],0x0000);
        mode3DrawLine(pointE[0],pointE[1],pointF[0],pointF[1],0x001F);
        mode3DrawLine(pointF[0],pointF[1],pointG[0],pointG[1],0x03E0);
        mode3DrawLine(pointG[0],pointG[1],pointH[0],pointH[1],0x7C00);
        mode3DrawLine(pointH[0],pointH[1],pointE[0],pointE[1],0x0000);
        mode3DrawLine(pointE[0],pointE[1],pointA[0],pointA[1],0x001F);
        mode3DrawLine(pointF[0],pointF[1],pointB[0],pointB[1],0x03E0);
        mode3DrawLine(pointG[0],pointG[1],pointC[0],pointC[1],0x7C00);
        mode3DrawLine(pointH[0],pointH[1],pointD[0],pointD[1],0x0000);


        vu32 y = 0;
        for (u16 x = 0; x < 0x0FFF; x++)
        {
            y = y + 3;
            y = y + 1;
            y = y + 1;
        }
        t = t + 0.1;
        
        while(getVBlankStatus())
        {

        }; // VSync
    };
    return(0);
}