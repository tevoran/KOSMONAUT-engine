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

    
        struct vec3f pos={1,1.,1.8};
        struct vec3f col={1,0,0};
        struct entry* cube1=gfx_create_cube(pos,col,0.4);
        
        pos.x=1;
        pos.z=3;
        col.y=1;
        struct entry* cube2=gfx_create_cube(pos,col,0.4);
        
        pos.z=6;
        col.z=1;
        struct entry* cube3=gfx_create_cube(pos,col,0.4);


    glPolygonMode(GL_FRONT, GL_FILL);
    
    int FPS;
    int lasttick=SDL_GetTicks();
    
    float i=0;
    
    int secs=0;
    while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
    {
    /*FPS count*/
    if(SDL_GetTicks()>(lasttick+1000))
    {
        printf("FPS: %i\n",FPS);
        FPS=0;
        lasttick=SDL_GetTicks();
        secs++;
        if(secs==4)
        {
            gfx_delete_model_entry(cube1);
        }
        if(secs==7)
        {
            pos.x=1;
            pos.y=1;
            pos.z=1.8;
            col.y=0;
            col.z=0;
            cube1=gfx_create_cube(pos,col,1);
        }

    }
    FPS++;

    /*i=i+0.0001;
    cam_location.z=cam_location.z+0.005;
    cam_location.y=5*sin(i*5*PI);
    cam_location.x=5*sin(i*PI);
    gfx_camera_location(cam_location);*/
    

        
    gfx_new_frame();
    }
    return 0;
}