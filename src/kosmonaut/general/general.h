#ifndef ENGINE_H
#define ENGINE_H


/*includes*/
#include <SDL2/SDL.h>
#include <inttypes.h>


#define ENGINE_FALSE 0
#define ENGINE_TRUE 1

/*error returns*/
#define ENGINE_NO_ERROR 0
#define ENGINE_ERROR 1
#define ENGINE_SDL_ERROR 2
#define ENGINE_GL_ERROR 3
#define ENGINE_GLEW_ERROR 4
#define ENGINE_GFX_ERROR 100
#define ENGINE_NO_CONFIG_FILE 200



/*global variables*/
SDL_Window *window;
SDL_Event event;
SDL_GLContext context; /*OpenGL context handler*/

struct config config;


/*functions*/
int engine_init(char *window_name, char *config_file);

/*config*/
struct config
{
	uint32_t resolution_x;
	uint32_t resolution_y;
	uint32_t wireframe_mode;
	char *log_file;
};

int engine_read_config(char *config_file_location);

/*return functions, so that it's not necessary to access
the global variables directly from the gfx engine*/
SDL_Window* engine_get_window();
SDL_Event engine_get_event();
struct config engine_config_state();

#endif