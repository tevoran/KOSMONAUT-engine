#ifndef MATHS_H
#define MATHS_H

/*the maths library for the SPACE BATTLE: COMMAND game*/

/*define constants*/
#define PI 3.141593

/*define different vectors*/
struct vec2f
{
    float x;
    float y;
};

struct vec3f /*float*/
{
    float x;
    float y;
    float z;
};

struct vec3d /*double*/
{
    double x;
    double y;
    double z;
};

/*scaling vector*/
struct vec3f vec3f_scale(float a, struct vec3f b);
struct vec3d vec3d_scale(float a, struct vec3d b);

/*vector addition*/
struct vec3f vec3f_add(struct vec3f a, struct vec3f b);
struct vec3d vec3d_add(struct vec3d a, struct vec3d b);

/*vector rotation*/
/*x-axis*/
struct vec3f vec3f_rotate_x(float rotation, struct vec3f a);
struct vec3d vec3d_rotate_x(float rotation, struct vec3d a);

/*y-axis*/
struct vec3f vec3f_rotate_y(float rotation, struct vec3f a);
struct vec3d vec3d_rotate_y(float rotation, struct vec3d a);

/*z-axis*/
struct vec3f vec3f_rotate_z(float rotation, struct vec3f a);
struct vec3d vec3d_rotate_z(float rotation, struct vec3d a);

#endif