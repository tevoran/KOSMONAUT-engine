#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#include <nng/nng.h>

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

	struct ui_window *window_test1=gfx_ui_create_window(300,300,0,0);
	struct ui_window *window_test2=gfx_ui_create_window(100,100,400,0);
	struct ui_window *window_test3=gfx_ui_create_window(100,100,0,400);
	struct ui_window *window_test=gfx_ui_create_window(100,100,750,350);
	gfx_ui_window_texture(window_test, "data/textures/window.bmp");
	gfx_ui_copy_window_texture(window_test, window_test1);
	gfx_ui_copy_window_texture(window_test, window_test2);
	gfx_ui_copy_window_texture(window_test, window_test3);

	struct ship *player=game_create_ship();
	player->position.x=0;
	player->position.y=0;
	player->position.z=100;
	player->model=gfx_load_model("data/models/stealth/stealth.obj", player->position);
	gfx_model_load_texture("data/textures/stealth.bmp", player->model);
	game_ship_is_player(player);

	struct ship *ships[100];
	for(int i=0; i<100; i++)
	{
		struct vec3f position={i*30, 10, 0};
		ships[i]=game_create_ship();
		ships[i]->model=gfx_copy_model(player->model);
		game_ship_location(ships[i], position);
		game_ship_new_destination(ships[i], "EF3");
	}
	
	float i=0;

	int quit=0;
	while(!quit) /*while not closing the window the main loop is continuing*/
	{
	engine_fps_count(ENGINE_TRUE,0);
	game_player_controls_input(player);
	game_ships_update();

	i=i+0.001;
	gfx_ui_set_window_location(window_test, 500*sin(i)+500, 450*cos(i)+500);

	static struct model *text=NULL;
	if(text!=NULL)
	{
		gfx_delete_model_entry(text);
	}
	char *location=game_get_coordinate(player->position);
	text=gfx_ui_printf(0.7, 0.97, NULL, 50, "CURRENT LOCATION: %s", location);

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

	engine_shutdown();
	exit(0);
}