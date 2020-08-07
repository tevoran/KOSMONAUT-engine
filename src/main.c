#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "engine/engine.h"
#include "gfx/gl/gfx.h"
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


GLuint triangle_array_reference;
    GLuint vertex_buffer_reference;
    glGenVertexArrays(1, &triangle_array_reference);
    glGenBuffers(1, &vertex_buffer_reference);
    
    


/*maths test*/
struct vec3f a,f,c;
a.x=0;
a.y=3;
a.z=5;
f.x=3;
f.y=6;
f.z=0;

c=vec3f_add(a,f);

printf("a=%f, %f, %f and f=%f, %f, %f\n",a.x,a.y,a.z,f.x,f.y,f.z);
printf("result %f, %f, %f\n",c.x,c.y,c.z);

    struct vec3f cen={0.0,0.0,-0.4};
    struct vec3f vex={0.5,-0.5,0};
    struct vec3f vey={0.0,-0.5,0};
    struct vec3f vez={0.5,0.5,0};
    while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
    {
        /*test opengl*/
    /*rotating triangle*/
    cen=vec3f_scale(-1,cen);
    
    vex=vec3f_add(vex,cen);
    vey=vec3f_add(vey,cen);
    vez=vec3f_add(vez,cen);
    
    cen=vec3f_scale(-1,cen);
    
    vex=vec3f_rotate_y(0.001,vex);
    vey=vec3f_rotate_x(0.0003,vey);
    vez=vec3f_rotate_z(0.00037,vez);
   
    vex=vec3f_add(vex,cen);
    vey=vec3f_add(vey,cen);
    vez=vec3f_add(vez,cen);
   
    GLfloat triangle_data[] = //a test square
    {
        //position              //color         //comment
        vey.x,vey.y,vey.z,   0.8f,0.8f,0.3f, //top left
        vex.x,vex.y,vex.z,   0.8f,0.8f,0.3f, //top right
        vez.x,vez.y,vez.z,   0.8f,0.8f,0.3f, //bottom left
/*
        -0.5f,0.5f,-0.4f,    0.9f,0.6f,0.4f, //bottom left
        0.5f,0.5f,0.0f,     0.1f,0.5f,0.8f, //bottom right
        0.5f,-0.5f,-0.2f,    0.5f,0.5f,0.5f, //top right
         */
        
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
        (void*)0        //array buffer offset
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