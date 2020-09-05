#include "general.h"

/*this file initialises everything necessary for SDL2 and OpenGL 4.6 but does itself nothing for the graphics*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "gfx/gfx.h" /*graphics engine header*/

extern SDL_Window *window;
extern struct config config;

int engine_init(char *window_name, char *config_file)
{
	printf("Initialising SBC-Engine...\n");
	
	/*reading config file for initialization, if there is one*/
	if(engine_read_config(config_file)!=ENGINE_NO_ERROR)
	{
		printf("ERROR: error while reading config file at:\n%s",config_file);
	}
	
	/*initialising SDL2*/
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		return ENGINE_SDL_ERROR;
	}
	
	window=SDL_CreateWindow(
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
	
	/*initialising OpenGL 4.6*/
	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)!=0)
	{
		printf("ERROR: OpenGL has to be at least version 4.5\n");
		return ENGINE_GL_ERROR;
	}
	
	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5)!=0)
	{
		printf("ERROR: OpenGL has to be at least version 4.5\n");
		return ENGINE_GL_ERROR;
	}
	
	context=SDL_GL_CreateContext(window);
	if(context==NULL)
	{
		return ENGINE_GL_ERROR;
	}
	
	/*initialising GLEW*/
	if(glewInit()!=GLEW_OK)
	{
		return ENGINE_GLEW_ERROR;
	}
	
	/*initialising graphics engine*/
	gfx_init();
	printf("Engine successfully initialised\n");
	return ENGINE_NO_ERROR;
}