#include "gfx/gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "engine/engine.h"

void gfx_new_frame()
{
    /*drawing all primitives*/
    int i_high=gfx_get_highest_handle();
    for(int i=0; i<i_high; i++)
    {
    glBindVertexArray(gfx_get_arrayID(i));
    glDrawArrays(GL_TRIANGLES,0,gfx_get_num_vertices(i));
    }
    
    SDL_GL_SwapWindow(engine_get_window()); /*swapping the double buffer*/
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}