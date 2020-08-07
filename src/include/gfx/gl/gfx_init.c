#include "gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "engine/engine.h"

int gfx_init()
{
    printf("initialising graphics engine...");

    /*setting background color as black*/
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*loading shaders*/
    gfx_loading_shaders();
    
    printf("done\n");
}