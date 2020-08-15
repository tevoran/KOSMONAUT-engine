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
    gfx_create_camera(cam_location,view_direction, 100);

    
    

    for(float i=0; i<100; i=i+0.3)
    {
        struct vec3f v1a={0.-sin(i),-1+sin(i),0.8+(i*0.1)};
        struct vec3f v2a={1.-sin(i),-1+sin(i),0.8+(i*0.1)};
        struct vec3f v3a={1.-sin(i),0.+sin(i),0.8+(i*0.1)};
        struct vec3f cola={1-sin(i),1-sin(i/3),1-sin(i)};
    gfx_create_triangle(v1a,v2a,v3a,cola);
    }

    int FPS;
    int lasttick=SDL_GetTicks();
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
        
    /*view_direction.x=view_direction.x-0.0001;*/
    /*view_direction.y=view_direction.y+0.0005;*/
    cam_location.z=cam_location.z+0.0001;
    gfx_camera_location(cam_location);
    /*gfx_set_camera_rotation(view_direction);*/
    

        
    gfx_new_frame();
    }
    return 0;
}