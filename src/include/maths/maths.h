#ifndef MATHS_H
#define MATHS_H

/*the maths library for the SPACE BATTLE: COMMAND game*/

/*define constants*/
#define PI 3.141593

/*define different vectors*/
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

/*vector addition*/
struct vec3f vec3f_add(struct vec3f a, struct vec3f b);
struct vec3d vec3d_add(struct vec3d a, struct vec3d b);

#endif