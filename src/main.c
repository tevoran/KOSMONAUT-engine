#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "general/general.h"
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
    gfx_create_camera(cam_location,view_direction, 1000, 0.5*PI);

    
        struct vec3f pos={1,1.,4};
        struct vec3f col={1,0,0};
        struct model* cube1=gfx_create_cube(pos,col,0.4);
        struct vec3f rot;
        rot.x=0.0;
        rot.y=1.11;
        rot.z=0.00;
        float r1=0.0002;
        
        pos.x=5;
        pos.z=7;
        col.y=1;
        struct model* cube2=gfx_create_cube(pos,col,2);
        
        pos.z=6;
        col.z=9;
        struct model* cube3=gfx_create_cube(pos,col,1);
        
    pos.x=0;
    pos.y=4;
    pos.z=10;
    
    struct vec3f pos2={1,0,0};
    struct vec3f pos3={0,1,0};
    struct vec3f col2={0.9,0.8,0.3};
    struct model* tri1=gfx_create_triangle(pos,pos2,pos3,col2);

    
    struct vec3f rot_axis;
    rot_axis.x=0;
    rot_axis.y=0;
    rot_axis.z=1;
    struct vec3f pos_model={0,0,100};
    struct model* cat=gfx_load_model("data/models/test/cat.obj",pos_model);
    float r=1.5*PI;
    gfx_model_rotate(cat, r, rot_axis);

    rot_axis.x=0;
    rot_axis.y=1;
    rot_axis.z=0;
    r=1.4*PI;
    gfx_model_rotate(cat, r, rot_axis);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    
    int FPS=0;
    int lasttick=SDL_GetTicks();
    
    float i=0;
    while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
    {
    /*FPS count*/
    if(SDL_GetTicks()>(lasttick+1000))
    {
        printf("FPS: %i\n",FPS);
        FPS=0;
        lasttick=SDL_GetTicks();
    }
    FPS++;

       rot.x=0.0;
        rot.y=1.11;
        rot.z=0.00;
    gfx_model_rotate(cube2,r1,rot);

       rot.x=1;
        rot.y=0;
        rot.z=0.00;
    gfx_model_rotate(cube2,r1,rot);

    i=i+0.00025;
    pos.x=4*sin(i);
    pos.y=5*cos(i/13.8);
    pos.z=5;
    gfx_update_model_location(cube1,pos);
    

    pos.x=4*sin(i/5.3);
    pos.y=3*sin(i/9.2);
    pos.z=10;
    gfx_update_model_location(cube3,pos);
    
    pos.x=6*sin(i/4);
    pos.y=7*sin(i/3.7);
    pos.z=4*cos(i/10)+10;
    gfx_update_model_location(tri1,pos);

        
    gfx_new_frame();
    }
    return 0;
}