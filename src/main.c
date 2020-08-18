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
    gfx_create_camera(cam_location,view_direction, 100, 0.5*PI);

    
        struct vec3f pos={1,1.,4};
        struct vec3f col={1,0,0};
        struct entry* cube1=gfx_create_cube(pos,col,0.4);
        
        pos.x=1;
        pos.z=7;
        col.y=1;
        struct entry* cube2=gfx_create_cube(pos,col,0.4);
        
        pos.z=6;
        col.z=9;
        struct entry* cube3=gfx_create_cube(pos,col,0.4);


    glPolygonMode(GL_FRONT, GL_FILL);
    
    int FPS;
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

    i=i+0.00025;
    pos.x=4*sin(i);
    pos.y=2.5*sin(i/13.8);
    gfx_update_model_location(cube2,pos);
    

        
    gfx_new_frame();
    }
    return 0;
}