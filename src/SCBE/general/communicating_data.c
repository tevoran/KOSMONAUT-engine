#include "general.h"

#include <SDL2/SDL.h>


extern struct config config;

struct config engine_config_state()
{
	return config;
}


/*this functions returns a SDL_Event struct*/

extern SDL_Event event;

SDL_Event engine_get_event()
{
	SDL_PollEvent(&event);
	return event;
}

/*the function returns a SDL Window pointer*/

extern SDL_Window *window;

SDL_Window* engine_get_window()
{
	return window;
}