#include "gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "general/general.h"

extern GLuint shader_program;

int gfx_init()
{
    printf("initialising graphics engine...");
    
    /*enable debug output*/
    glEnable(GL_DEBUG_OUTPUT);
    
    /*activate Z-Buffer*/
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glClearDepth(1.0f);
    glDepthRange(0.0f,1.0f);
    
    /*setting background color as black*/
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*loading shaders*/
    shader_program=gfx_loading_shaders();

    
    printf("done\n");
}