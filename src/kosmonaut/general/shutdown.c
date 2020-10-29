#include "general.h"

/*this file shuts everything down and cleans up*/

#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <nng/nng.h>

#include "gfx/gfx.h" /*graphics engine header*/
void engine_shutdown()
{
	/*cleaning up all models or render objects*/
	gfx_model_list_cleanup();


	/*SDL related cleanup*/
	SDL_GL_DeleteContext(engine_get_gl_context());
	SDL_Quit();
}