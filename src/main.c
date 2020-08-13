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

    
    /*struct vec3f v1={0,0,5};
    struct vec3f v2={1,0,5};
    struct vec3f v3={0,1,5};
    struct vec3f col={0.3,0.3,0.3};
    gfx_create_triangle(v1,v2,v3,col);*/
    
    for(float i=1; i<100; i=i+0.3)
    {
        struct vec3f v1a={1,0,i};
        struct vec3f v2a={2,0,i};
        struct vec3f v3a={1,1,i};
        struct vec3f cola={1/i,1-(1/i),0.4};
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
        
    /*view_direction.x=view_direction.x+0.0003;
    view_direction.y=view_direction.y+0.0003;*/
    cam_location.z=cam_location.z+0.0001;
    gfx_camera_location(cam_location);
    gfx_set_camera_rotation(view_direction);
    

        
    gfx_new_frame();
    }
    return 0;
}