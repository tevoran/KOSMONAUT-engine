#include "maths.h"

#include <math.h>


/*scaling vector*/
struct vec3f vec3f_scale(float a, struct vec3f b)
{
    struct vec3f c;
    c.x=a*b.x;
    c.y=a*b.y;
    c.z=a*b.z;
    return c;
}

struct vec3d vec3d_scale(float a, struct vec3d b)
{
    struct vec3d c;
    c.x=a*b.x;
    c.y=a*b.y;
    c.z=a*b.z;
    return c;
}


/*vector addition*/

struct vec3f vec3f_add(struct vec3f a, struct vec3f b)
{
    struct vec3f c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    c.z=a.z+b.z;
    return c;
}


struct vec3d vec3d_add(struct vec3d a, struct vec3d b)
{
    struct vec3d c;
    c.x=a.x+b.x;
    c.y=a.y+b.y;
    c.z=a.z+b.z;
    return c;
}

/*rotation*/
/*x-axis*/
struct vec3f vec3f_rotate_x(float rotation, struct vec3f a)
{
    struct vec3f c;
    c.x=a.x;
    c.y=cos(rotation)*a.y-sin(rotation)*a.z;
    c.z=sin(rotation)*a.y+cos(rotation)*a.z;
    return c;
}

struct vec3d vec3d_rotate_x(float rotation, struct vec3d a)
{
    struct vec3d c;
    c.x=a.x;
    c.y=cos(rotation)*a.y-sin(rotation)*a.z;
    c.z=sin(rotation)*a.y+cos(rotation)*a.z;
    return c;
}

/*y-axis*/
struct vec3f vec3f_rotate_y(float rotation, struct vec3f a)
{
    struct vec3f c;
    c.x=cos(rotation)*a.x+sin(rotation)*a.z;
    c.y=a.y;
    c.z=-sin(rotation)*a.x+cos(rotation)*a.z;
    return c;
}

struct vec3d vec3d_rotate_y(float rotation, struct vec3d a)
{
    struct vec3d c;
    c.x=cos(rotation)*a.x+sin(rotation)*a.z;
    c.y=a.y;
    c.z=-sin(rotation)*a.x+cos(rotation)*a.z;
    return c;
}

/*z-axis*/
struct vec3f vec3f_rotate_z(float rotation, struct vec3f a)
{
    struct vec3f c;
    c.x=cos(rotation)*a.x-sin(rotation)*a.y;
    c.y=sin(rotation)*a.x+cos(rotation)*a.y;
    c.z=a.z;
    return c;
}

struct vec3d vec3d_rotate_z(float rotation, struct vec3d a)
{
    struct vec3d c;
    c.x=cos(rotation)*a.x-sin(rotation)*a.y;
    c.y=sin(rotation)*a.x+cos(rotation)*a.y;
    c.z=a.z;
    return c;
}