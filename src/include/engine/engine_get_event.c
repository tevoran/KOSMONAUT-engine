#include "engine.h"

#include <SDL2/SDL.h>

/*this functions returns a SDL_Event struct*/

extern SDL_Event event;

SDL_Event engine_get_event()
{
    SDL_PollEvent(&event);
    return event;
}