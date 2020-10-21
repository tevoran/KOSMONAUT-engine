#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <nng/nng.h>

/*engine*/
#include "general/general.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "gfx/ui/ui.h"
#include "net/net.h"

/*game*/
#include "SBC.h"
#include "objects/objects.h"

#define GLEW_STATIC
#undef main

int main(int argc, char **argv[])
{

	game_init();

	struct model *cube[1000];
	for(int i=0; i<1000; i++)
	{
		struct vec3f location={30*sin(i), 22*cos(i), i*7.5};
		struct vec3f color={1,1,1};
		if(i==0)
		{
			cube[0]=gfx_create_cube(location, color, 5);
			gfx_model_load_texture("data/textures/box.bmp", cube[i]);
		}
		if(i!=0)
		{
			cube[i]=gfx_copy_model(cube[0]);
			gfx_update_model_location(cube[i], location);
		}
	}

	struct ship player;
	player.position.x=0;
	player.position.y=0;
	player.position.z=100;
	player.rotation.x=0;
	player.rotation.y=0;
	player.rotation.z=0;
	player.model=gfx_load_model("data/models/stealth/stealth.obj", player.position);
	gfx_model_load_texture("data/textures/stealth.bmp", player.model);


	int quit=0;
	while(!quit) /*while not closing the window the main loop is continuing*/
	{
	engine_fps_count(ENGINE_TRUE,0);

	game_player_controls_input(&player);


	/*handling input via SDL2*/
	{
		SDL_Event event;

		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				quit=1;
				break;
		}
	}


	gfx_new_frame();
	}
	exit(0);
}