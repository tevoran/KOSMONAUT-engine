#include "general.h"

/*this file initialises everything necessary for SDL2 and OpenGL 4.5 but does itself nothing for the graphics*/

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
//#include <nng/nng.h>

#include "gfx/gfx.h" /*graphics engine header*/

int engine_init(char *window_name, char *config_file)
{	
	/*reading config file for initialization, if there is one*/
	if(engine_read_config(config_file)!=ENGINE_NO_ERROR)
	{
		engine_log("ERROR: error while reading config file at:\n%s",config_file);
	}

	/*writing an header to the log file*/
	engine_log("The log file of the kosmonaut engine is rewritten for each run of the engine.\n\n");

	/*initialising SDL2*/
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		return ENGINE_SDL_ERROR;
	}
	
	struct config config=engine_config_state();

	SDL_Window *window=SDL_CreateWindow(
		window_name,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		config.resolution_x,
		config.resolution_y,
		SDL_WINDOW_OPENGL);
	if(window==NULL)
	{
		return ENGINE_SDL_ERROR;
	}
	engine_write_window(window);
	/*if fullscreen is set in the config file then set the window to fullscreen mode*/
	if(config.fullscreen_mode==ENGINE_TRUE)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_ShowCursor(SDL_DISABLE);
	}

	
	/*initialising OpenGL 4.6*/
	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)!=0)
	{
		engine_log("ERROR: OpenGL has to be at least version 4.5\n");
		return ENGINE_GL_ERROR;
	}
	
	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5)!=0)
	{
		engine_log("ERROR: OpenGL has to be at least version 4.5\n");
		return ENGINE_GL_ERROR;
	}
	
	SDL_GLContext context=SDL_GL_CreateContext(window);
	if(context==NULL)
	{
		return ENGINE_GL_ERROR;
	}
	engine_write_gl_context(context);
	
	/*initialising GLEW*/
	if(glewInit()!=GLEW_OK)
	{
		return ENGINE_GLEW_ERROR;
	}
	
	/*initialising graphics engine*/
	gfx_init();
	engine_log("Engine successfully initialised\n");

	/*NNG - network library*/
/*	const char *nng_version_ptr=nng_version();
	engine_log("\nNNG library version: %s\n", nng_version_ptr);
*/
	return ENGINE_NO_ERROR;
}