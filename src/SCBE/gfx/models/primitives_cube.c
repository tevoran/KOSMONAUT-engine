#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


struct entry* gfx_create_cube(struct vec3f location, struct vec3f color, float size)
{
    struct entry* model_entry=gfx_create_model_entry();
    
    
    
    GLfloat cube_data[]=
    {
        /*top*/
        -0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        -0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,

        -0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        
        /*back*/
        -0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        -0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,

        -0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        
        /*right*/
        0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,

        0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,

        /*left*/
        -0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        -0.5*size,0.5*size,0.5*size,
        color.x,color.y,color.z,
        -0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,

        -0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        -0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,
        -0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        
        /*bottom*/
        -0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,
        -0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,

        -0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,0.5*size,
        color.x,color.y,color.z,
        
        /*front*/
        -0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,
        -0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,

        -0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,0.5*size,-0.5*size,
        color.x,color.y,color.z,
        0.5*size,-0.5*size,-0.5*size,
        color.x,color.y,color.z,
        
    };
    
    model_entry->num_vertices=sizeof(cube_data)/(6*sizeof(GLfloat));
    
    /*saving OpenGL array ID*/
    GLuint cube_arrayID;
    glGenVertexArrays(1, &cube_arrayID);
    model_entry->arrayID=cube_arrayID;
    
    /*saving OpenGL vertex buffer ID*/
    GLuint vertex_bufferID;
    glGenBuffers(1, &vertex_bufferID);
    model_entry->vertex_bufferID=vertex_bufferID;


    glBindVertexArray(model_entry->arrayID);
    glBindBuffer(GL_ARRAY_BUFFER, model_entry->vertex_bufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    /*calculating world transform matrix*/
    GLfloat world_matrix[4][4]=
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        location.x, location.y, location.z, 1
    };
    
    for(int ix=0,iy=0; iy<4; ix++)
    {
        model_entry->world_transform_matrix[ix][iy]=world_matrix[ix][iy];
        if(ix==3)
        {
            ix=-1;
            iy++;
        }
    }
        
    return model_entry;
}