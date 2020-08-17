#include "general.h"

/*this file initialises everything necessary for SDL2 and OpenGL 4.6 but does itself nothing for the graphics*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "gfx/gfx.h" /*graphics engine header*/

extern SDL_Window *window;

int engine_init()
{
    printf("Initialising SBC-Engine...\n");
    
    /*initialising SDL2*/
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        return ENGINE_SDL_ERROR;
    }
    
    window=SDL_CreateWindow("Space Battle Command",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,800,SDL_WINDOW_OPENGL);
    if(window==NULL)
    {
        return ENGINE_SDL_ERROR;
    }
    
    /*initialising OpenGL 4.6*/
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)!=0)
    {
        printf("ERROR: OpenGL has to be at least version 4.5\n");
        return ENGINE_GL_ERROR;
    }
    
    if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5)!=0)
    {
        printf("ERROR: OpenGL has to be at least version 4.5\n");
        return ENGINE_GL_ERROR;
    }
    
    context=SDL_GL_CreateContext(window);
    if(context==NULL)
    {
        return ENGINE_GL_ERROR;
    }
    
    /*initialising GLEW*/
    if(glewInit()!=GLEW_OK)
    {
        return ENGINE_GLEW_ERROR;
    }
    
    /*initialising graphics engine*/
    gfx_init();
    printf("Engine successfully initialised\n");
    return ENGINE_NO_ERROR;
}