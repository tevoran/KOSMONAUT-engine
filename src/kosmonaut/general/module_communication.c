#include "general.h"

#include <SDL2/SDL.h>

/*global variables*/
SDL_Window *window;
SDL_Event event;
SDL_GLContext gl_context;


/*this functions returns a SDL_Event struct*/
SDL_Event engine_get_event()
{
	SDL_PollEvent(&event);
	return event;
}

/*handling with gl context*/
void engine_write_gl_context(SDL_GLContext context)
{
	gl_context=context;
}

SDL_GLContext engine_get_gl_context()
{
	return gl_context;
}

/*the function returns a SDL Window pointer*/
SDL_Window* engine_get_window()
{
	return window;
}

void engine_write_window(SDL_Window *window_in)
{
	window=window_in;
}