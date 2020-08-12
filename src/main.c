#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "engine/engine.h"
#include "gfx/gfx.h"
#include "maths/maths.h"



int main()
{
    /*initialisinge game engine*/
    switch(engine_init())
    {
        case ENGINE_NO_ERROR:
        break;
        
        case ENGINE_SDL_ERROR:
        printf("ERROR: SDL ERROR\n");
        return 1;
        break;
        
        case ENGINE_GL_ERROR:
        printf("ERROR: OpenGL ERROR\n");
        return 1;
        break;
        
        case ENGINE_GLEW_ERROR:
        printf("ERROR: GLEW ERROR\n");
        return 1;
        break;
        
        case ENGINE_GFX_ERROR:
        printf("ERROR: graphics engine error\n");
        return 1;
        break;
        
    }

    struct vec3f cam_location={0,0,0};
    struct vec2f view_direction={0,0};
    gfx_create_camera(cam_location,view_direction, 1000000);

    GLuint triangle_array_reference;
    GLuint vertex_buffer_reference;
    glGenVertexArrays(1, &triangle_array_reference);
    glGenBuffers(1, &vertex_buffer_reference);
    

    
    float z=0;
    
    for(int i=0; i<7500; i++)
    {
    printf("handle: %u\n",gfx_create_handle());
    }

    while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
    {
    
    view_direction.x=view_direction.x+0.0003;
    view_direction.y=view_direction.y+0.0003;
    cam_location.z=cam_location.z-0.00001;
    gfx_camera_location(cam_location);
    gfx_set_camera_rotation(view_direction);
    
    GLfloat triangle_data[] = //a test square
    {
        //position              //color         //comment
        0,1,2,                0.8f,0.8f,0.3f, //top left
        1,1,2,                0.9f,0.7f,0.3f, //top right
        0,0,2,                0.4f,0.85f,0.25f, //bottom left
        
        
    };
    
    glBindVertexArray(triangle_array_reference);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_reference);
    glBufferData(GL_ARRAY_BUFFER,sizeof(triangle_data),triangle_data,GL_STATIC_DRAW);
        
    //describing data for OpenGL for its interpretation
    glVertexAttribPointer
    (
        0,
        3,              //size
        GL_FLOAT,       //type
        GL_FALSE,       //normalized
        6*sizeof(float),//stride
        (void*)0        //array buffer offsets
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer
    (
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6*sizeof(float),
        (void*)(3*sizeof(float))
    );
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES,0,3);
        
    gfx_new_frame();
    }
    return 0;
}