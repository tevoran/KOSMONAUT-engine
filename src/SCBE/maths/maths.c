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

/*normalizing vector*/
struct vec4f normalize4f(struct vec4f a)
{
	float length=sqrt(a.x*a.x+a.y*a.y+a.z*a.z+a.w*a.w);
	struct vec4f b;
	b.x=a.x/length;
	b.y=a.y/length;
	b.z=a.z/length;
	b.w=a.w/length;
	return b;
}


/*dot product*/
float dot_product(struct vec3f a, struct vec3f b)
{
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

/*cross product*/
struct vec3f cross_product(struct vec3f a, struct vec3f b)
{
	struct vec3f c;
	c.x=a.y*b.z-a.z*b.y;
	c.y=a.z*b.x-a.x*b.z;
	c.z=a.x*b.y-a.y*b.x;
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

/*matrix multiplication 4x4 matrices*/
void matrix_multiplication4x4(float *a, float *b, float *result)
{
	for(int y=0; y<4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			*((result+x*4)+y)=*(a+x*4)*(*(b+y))
							+*((a+x*4)+1)*(*((b+1*4)+y))
							+*((a+x*4)+2)*(*((b+2*4)+y))
							+*((a+x*4)+3)*(*((b+3*4)+y));
		}
	}
}