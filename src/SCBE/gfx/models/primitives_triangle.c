#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


struct entry* gfx_create_triangle(struct vec3f vertex1, struct vec3f vertex2, struct vec3f vertex3, struct vec3f color) /*returns a uint32_t handle*/
{
    
    struct entry* model_entry=gfx_create_model_entry();

    
    GLfloat triangle_data[]=
    {
        vertex1.x,vertex1.y,vertex1.z,
        color.x,color.y,color.z,
        
        vertex2.x,vertex2.y,vertex2.z,
        color.x,color.y,color.z,
        
        vertex3.x,vertex3.y,vertex3.z,
        color.x,color.y,color.z
    };
    
    
    
    model_entry->num_vertices=3; /*value is three, because this is a triangle*/
    
    /*saving OpenGL array ID*/
    GLuint triangle_arrayID;
    glGenVertexArrays(1, &triangle_arrayID);
    model_entry->arrayID=triangle_arrayID;
    
    /*saving OpenGL vertex buffer ID*/
    GLuint vertex_bufferID;
    glGenBuffers(1, &vertex_bufferID);
    model_entry->vertex_bufferID=vertex_bufferID;


    glBindVertexArray(model_entry->arrayID);
    glBindBuffer(GL_ARRAY_BUFFER, model_entry->vertex_bufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle_data),triangle_data,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    return model_entry;
}