#include "gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "engine/engine.h"

extern GLuint shader_program;

int gfx_init()
{
    printf("initialising graphics engine...");
    
    /*activate Z-Buffer*/
    glEnable(GL_DEPTH_TEST);  
    glDepthFunc(GL_LESS);
    
    /*setting background color as black*/
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*loading shaders*/
    shader_program=gfx_loading_shaders();

    
    printf("done\n");
}