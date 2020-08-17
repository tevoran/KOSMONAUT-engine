#ifndef ENGINE_H
#define ENGINE_H


/*includes*/
#include <SDL2/SDL.h>


/*error returns*/
#define ENGINE_NO_ERROR 0
#define ENGINE_ERROR 1
#define ENGINE_SDL_ERROR 2
#define ENGINE_GL_ERROR 3
#define ENGINE_GLEW_ERROR 4
#define ENGINE_GFX_ERROR 100


/*global variables*/
SDL_Window *window;
SDL_Event event;
SDL_GLContext context; /*OpenGL context handler*/

/*functions*/
int engine_init();

/*return functions, so that it's not necessary to access the global variables directly from the gfx engine*/
SDL_Window* engine_get_window();
SDL_Event engine_get_event();

#endif