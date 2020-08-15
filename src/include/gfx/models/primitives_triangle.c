#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


uint32_t gfx_create_triangle(struct vec3f vertex1, struct vec3f vertex2, struct vec3f vertex3, struct vec3f color) /*returns a uint32_t handle*/
{
    uint32_t handle=gfx_create_handle();
    
    GLfloat triangle_data[]=
    {
        vertex1.x,vertex1.y,vertex1.z,
        color.x,color.y,color.z,
        vertex2.x,vertex2.y,vertex2.z,
        color.x,color.y,color.z,
        vertex3.x,vertex3.y,vertex3.z,
        color.x,color.y,color.z,
    };
    
    gfx_set_num_vertices(handle, 3); /*value is three, because this is a triangle*/
    
    GLuint triangle_arrayID;
    glGenVertexArrays(1, &triangle_arrayID);
    gfx_set_arrayID(handle,triangle_arrayID);
    
    GLuint vertex_bufferID;
    glGenBuffers(1, &vertex_bufferID);
    gfx_set_vertex_bufferID(handle,vertex_bufferID);


    glBindVertexArray(gfx_get_arrayID(handle));
    glBindBuffer(GL_ARRAY_BUFFER, gfx_get_vertex_bufferID(handle));
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle_data),triangle_data,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
}