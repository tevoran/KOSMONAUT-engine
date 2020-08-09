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

    struct vec3f cen={-0.1,0.0,0.01};
    struct vec3f vex={0.1,0.1,0.4};
    struct vec3f vey={0.1,-0.1,0.4};
    struct vec3f vez={-0.1,0,0.5};
    
    float z=0;
    while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
    {
        /*test opengl*/
    /*rotating triangle*/
    /*vex=vec3f_add(vex,cen);
    vey=vec3f_add(vey,cen);
    vez=vec3f_add(vez,cen);
    
    cen=vec3f_scale(-1,cen);
    
    vex=vec3f_rotate_y(0.0001,vex);
    vey=vec3f_rotate_y(0.0001,vey);
    vez=vec3f_rotate_y(0.0001,vez);
    
    vex=vec3f_rotate_x(0.0009,vex);
    vey=vec3f_rotate_x(0.0009,vey);
    vez=vec3f_rotate_x(0.0009,vez);
    
    vex=vec3f_rotate_z(0.00078,vex);
    vey=vec3f_rotate_z(0.00078,vey);
    vez=vec3f_rotate_z(0.00078,vez);
   
    vex=vec3f_add(vex,cen);
    vey=vec3f_add(vey,cen);
    vez=vec3f_add(vez,cen);*/
    
    view_direction.x=view_direction.x+0.0003;
    view_direction.y=view_direction.y+0.0003;
    cam_location.z=cam_location.z-0.00001;
    gfx_camera_location(cam_location);
    gfx_set_camera_rotation(view_direction);
    
    GLfloat triangle_data[] = //a test square
    {
        //position              //color         //comment
        vey.x,vey.y,vey.z,   0.8f,0.8f,0.3f, //top left
        vex.x,vex.y,vex.z,   0.9f,0.7f,0.3f, //top right
        vez.x,vez.y,vez.z,   0.4f,0.85f,0.25f, //bottom left
        

        /*0.8f,-0.8f,z,    0.9f,0.6f,0.4f, //bottom left
        0.8f,-0.7f,0.2,     0.1f,0.5f,0.8f, //bottom right
        -0.8f,0.8f,0.2,    0.5f,0.5f,0.5f, //top right
        
        -0.5f,0.5f,1,    0.9f,0.6f,0.4f, //bottom left
        0.5f,0.5f,1,     0.1f,0.5f,0.8f, //bottom right
        0.5f,-0.5f,1,    0.5f,0.5f,0.5f, //top right*/
        
        
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