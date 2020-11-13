#ifndef KOSMONAUT_GENERAL_H
#define KOSMONAUT_GENERAL_H


/*includes*/
#include <SDL2/SDL.h>
#include <inttypes.h>

#define FALSE 0
#define TRUE 1
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



/*functions*/
int engine_init(char *window_name, char *config_file);
void engine_shutdown();
void engine_log(const char *logged_message, ...);
void engine_fps_count(int toggle_on_screen, int toggle_log);

/*config*/
struct config
{
	uint32_t resolution_x;
	uint32_t resolution_y;
	uint32_t wireframe_mode;
	uint32_t fullscreen_mode;
	float viewing_distance;
	char log_file[256];
	int logging_on;

	/*network member*/
	int net_host;
	int net_client;
	int net_port;
};

int engine_read_config(char *config_file_location);

/*return functions, so that it's not necessary to access
the global variables directly from the gfx engine*/
SDL_Window* engine_get_window();
SDL_Event engine_get_event();
struct config engine_config_state();
SDL_GLContext engine_get_gl_context();

void engine_write_window(SDL_Window *window_in);
void engine_write_gl_context(SDL_GLContext context);

#endif