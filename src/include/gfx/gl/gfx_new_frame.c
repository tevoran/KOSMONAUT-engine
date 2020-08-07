#include "gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "engine/engine.h"

void gfx_new_frame()
{
    SDL_GL_SwapWindow(engine_get_window()); /*swapping the double buffer*/
}