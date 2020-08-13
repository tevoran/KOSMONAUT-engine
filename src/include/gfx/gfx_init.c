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
    
    /*setting background color as black*/
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*loading shaders*/
    shader_program=gfx_loading_shaders();
    


    /*setting up the camera values*/
    /*telling the shader how to convert world space to the opengl internal space*/
    /*gfx_set_ws2nds_factor(1);*/
    gfx_set_ws2nds_factor(0.000001);/*setting conversion factor it's 1.000.000*/
    gfx_set_fov(0.5*PI);
    
    printf("done\n");
}