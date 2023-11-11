#include <math.h>

#include "../include/GBATypes.h"
#include "../include/GBARegisters.h"
#include "../include/GBAGraphics.h"
#include "../include/GBAMath.h"

// Variables
s8 screenX = SCREENWIDTH / 2; // screen width
s8 screenY = SCREENHEIGHT / 2; // screen height
float rotation = 0;

// Structures
struct point3d
{
    s32 x;
    s32 y;
    s32 z;
};
struct point2d
{
    s32 x;
    s32 y;
};
struct camera
{
    s32 x;
    s32 y;
    s32 z;

    // TODO: make fixed point math
    float yaw;
    float roll;
    float pitch;
};

struct polygon
{
    struct point3d vertex1;
    struct point3d vertex2;
    struct point3d vertex3;
};

// Functions

struct point3d createVertex(s8 x, s8 y, s8 z)
{
    struct point3d vertex;
    vertex.x = x;
    vertex.y = y;
    vertex.z = z;

    return vertex;
}

struct camera createCamera(s8 x, s8 y, s8 z, s8 yaw, s8 roll, s8 pitch)
{
    struct camera camera;
    camera.x = x;
    camera.y = y;
    camera.z = z;

    camera.yaw = yaw;
    camera.roll = roll;
    camera.pitch = pitch;

    return camera;
}

struct point2d getScreenCoordinate(struct point3d vertex, struct camera camera)
{
    struct point2d point;

    s16 rx = 2; // recording surface width
    s16 ry = 2; // recording surface height
    s16 rz = 1; // distance from recording surface to camera

    s16 x = (vertex.x-camera.x);//<<16;
    s16 y = (vertex.y-camera.y);//<<16;
    s16 z = (vertex.z-camera.z);//<<16;

    float sx = (sin(camera.yaw));
    float sy = (sin(camera.roll));
    float sz = (sin(camera.pitch));

    float cx = (cos(camera.yaw));
    float cy = (cos(camera.roll));
    float cz = (cos(camera.pitch));

    s16 dx = cy*(sz*y+cz*x)-sy*z;
    s16 dy = sx*(cy*z+sy*(sz*y+cz*x))+cx*(cz*y-sz*x);
    s16 dz = cx*(cy*z+sy*(sz*y+cz*x))-sx*(cz*y-sz*x);

    point.x = (dx * (screenX/2))/((dz * rx) * rz);
    point.y = (dy * (screenY/2))/((dz * ry) * rz);

    point.x += screenX/2;
    point.y += screenY/2;

    return point;
}
// typedef struct polygon polygon;
struct polygon createPolygon(struct point3d vertex1, struct point3d vertex2, struct point3d vertex3)
{
    struct polygon polygon;
    polygon.vertex1 = vertex1;
    polygon.vertex2 = vertex2;
    polygon.vertex3 = vertex3;
    return polygon;
}

void drawVector(u8 buffer, struct point2d vec1, struct point2d vec2, u16 colour)
{
    mode5DrawLine(buffer, vec1.x, vec1.y, vec2.x, vec2.y, colour);
}
void drawPolygon(u8 buffer, struct polygon polygon, struct camera camera)
{
    struct point2d v1 = getScreenCoordinate(polygon.vertex1, camera);
    struct point2d v2 = getScreenCoordinate(polygon.vertex2, camera);
    struct point2d v3 = getScreenCoordinate(polygon.vertex3, camera);

    drawVector(buffer, v1, v2, 0x0000);
    drawVector(buffer, v2, v3, 0x0000);
    drawVector(buffer, v3, v1, 0x0000);

    // TODO: Fill in poly according to distance from camera
}
void drawObject(u8 buffer, struct polygon object[], u16 polyCount, struct camera camera)
{
    // potentialy could wait untill object[i] is a null character of some sort
    for ( int i = 0; i < polyCount; i++)
    {
        drawPolygon(buffer, object[i], camera);
    }
}

// TODO: make this work
struct point3d revolve(struct point3d vertex)
{
    // u8 theta = 1;
    // vertex.x = vertex.x*cos(theta) - vertex.y*sin(theta);
    // vertex.y = vertex.x*sin(theta) + vertex.y*cos(theta);

    vertex.x = vertex.x*0.7 - vertex.y*0.7;
    vertex.y = vertex.x*0.7 + vertex.y*0.7;
    // vertex.z *= cos(rotation);
    return vertex;
}