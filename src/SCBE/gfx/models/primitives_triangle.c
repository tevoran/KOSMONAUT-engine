#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


/*corner1 and corner2 are relative to the triangle's position*/
struct model* gfx_create_triangle(struct vec3f location, struct vec3f corner1, struct vec3f corner2, struct vec3f color) /*returns a uint32_t handle*/
{
    
    struct model* model_entry=gfx_create_model_entry();

    /*this object doesn't use an index buffer*/
    model_entry->index_bufferID=0;
    
    GLfloat triangle_data[]=
    {
        0,0,0,
        color.x,color.y,color.z,
        
        corner1.x,corner1.y,corner1.z,
        color.x,color.y,color.z,
        
        corner2.x,corner2.y,corner2.z,
        color.x,color.y,color.z
    };
    
    
    
    model_entry->num_vertices=3; /*value is three, because this is a triangle*/
    
    /*saving OpenGL array ID*/;
    glGenVertexArrays(1, &model_entry->arrayID);
    
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