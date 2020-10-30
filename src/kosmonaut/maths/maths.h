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

struct vec4f /*float*/
{
	float x;
	float y;
	float z;
	float w;
};

/*random function*/
long long_random(long seed);

/*scaling vector*/
struct vec3f vec3f_scale(float a, struct vec3f b);
struct vec3d vec3d_scale(float a, struct vec3d b);

/*vector addition*/
struct vec3f vec3f_add(struct vec3f a, struct vec3f b);
struct vec3d vec3d_add(struct vec3d a, struct vec3d b);

/*dot product*/
float dot_product3f(struct vec3f a, struct vec3f b);

/*cross product*/
struct vec3f cross_product(struct vec3f a, struct vec3f b);

/*normalizing vector*/
struct vec3f normalize3f(struct vec3f a);
struct vec4f normalize4f(struct vec4f a);

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

/*matrix multiplication 4x4 matrices*/
void matrix_multiplication4x4(float const a[4][4], float const b[4][4], float result[4][4]);

#endif