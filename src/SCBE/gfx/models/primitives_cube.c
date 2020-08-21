#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


struct model* gfx_create_cube(struct vec3f location, struct vec3f color, float size)
{
    struct model* model_entry=gfx_create_model_entry();
    
    /*this object doesn't use an index buffer*/
    model_entry->index_bufferID=0;
    
    
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
    glGenVertexArrays(1, &model_entry->arrayID);
    
    /*saving OpenGL vertex buffer ID*/
    glGenBuffers(1, &model_entry->vertex_bufferID);


    glBindVertexArray(model_entry->arrayID);
    glBindBuffer(GL_ARRAY_BUFFER, model_entry->vertex_bufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    /*gfx engine stuff*/
    gfx_update_model_location(model_entry,location);
    struct vec3f rot_axis;
    rot_axis.x=0;
    rot_axis.y=1;
    rot_axis.z=0;
    gfx_model_rotate(model_entry, 0, rot_axis);
    
    /*clean up*/
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    return model_entry;
}