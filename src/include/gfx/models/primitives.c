#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <GL/glew.h>


uint32_t gfx_create_triangle(struct vec3f vertex1, struct vec3f vertex2, struct vec3f vertex3, struct vec3f color) /*returns a uint32_t handle*/
{
    GLfloat triangle_data[]=
    {
        vertex1.x,vertex1.y,vertex1.z,
        color.x,color.y,color.z,
        vertex2.x,vertex2.y,vertex2.z,
        color.x,color.y,color.z,
        vertex3.x,vertex3.y,vertex3.z,
        color.x,color.y,color.z,
    };
}