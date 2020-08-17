#include "general.h"

#include <SDL2/SDL.h>

/*the function returns a SDL Window pointer*/

extern SDL_Window *window;

SDL_Window* engine_get_window()
{
    return window;
}