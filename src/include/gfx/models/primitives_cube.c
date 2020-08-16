#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


uint32_t gfx_create_cube(struct vec3f location, struct vec3f color, float size)
{
    uint32_t handle=gfx_create_handle();
    
    if(handle==GFX_ERROR)
    {
        printf("ERROR: couldn't create triangle as a primitive - invalid handle\n");
        return GFX_ERROR;
    }
    
    
    GLfloat cube_data[]=
    {
        /*top*/
        location.x,location.y,location.z,
        color.x,color.y,color.z,
        location.x,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z,
        color.x,color.y,color.z,

        location.x+size,location.y,location.z,
        color.x,color.y,color.z,
        location.x,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z+size,
        color.x,color.y,color.z,
        
        /*back*/
        location.x,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z+size,
        color.x,color.y,color.z,
        
        location.x,location.y-size,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z+size,
        color.x,color.y,color.z,
        
        /*right*/
        location.x+size,location.y,location.z,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z+size,
        color.x,color.y,color.z,
        
        location.x+size,location.y,location.z,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z+size,
        color.x,color.y,color.z,

        /*left*/
        location.x,location.y,location.z,
        color.x,color.y,color.z,
        location.x,location.y,location.z+size,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z+size,
        color.x,color.y,color.z,
        
        location.x,location.y,location.z,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z+size,
        color.x,color.y,color.z,
        
        /*bottom*/
        location.x,location.y-size,location.z,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z,
        color.x,color.y,color.z,

        location.x+size,location.y-size,location.z,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z+size,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z+size,
        color.x,color.y,color.z,
        
        /*front*/
        location.x,location.y,location.z,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z,
        color.x,color.y,color.z,
        location.x,location.y-size,location.z,
        color.x,color.y,color.z,
        
        location.x,location.y-size,location.z,
        color.x,color.y,color.z,
        location.x+size,location.y,location.z,
        color.x,color.y,color.z,
        location.x+size,location.y-size,location.z,
        color.x,color.y,color.z,
        
    };
    
    gfx_set_num_vertices(handle, sizeof(cube_data)/(6*sizeof(GLfloat))); /*value is three, because this is a triangle*/
    
    /*saving OpenGL array ID*/
    GLuint cube_arrayID;
    glGenVertexArrays(1, &cube_arrayID);
    gfx_set_arrayID(handle,cube_arrayID);
    
    /*saving OpenGL vertex buffer ID*/
    GLuint vertex_bufferID;
    glGenBuffers(1, &vertex_bufferID);
    gfx_set_vertex_bufferID(handle,vertex_bufferID);


    glBindVertexArray(gfx_get_arrayID(handle));
    glBindBuffer(GL_ARRAY_BUFFER, gfx_get_vertex_bufferID(handle));
    glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    return handle;
}