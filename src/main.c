#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "general/general.h"
#include "gfx/gfx.h"
#include "maths/maths.h"



int main()
{
	/*initialisinge game engine*/
	switch(engine_init("Star Battle Command", "data/config.conf"))
	{
		case ENGINE_NO_ERROR:
		break;
		
		case ENGINE_SDL_ERROR:
		printf("ERROR: SDL ERROR\n");
		return 1;
		break;
		
		case ENGINE_GL_ERROR:
		printf("ERROR: OpenGL ERROR\n");
		return 1;
		break;
		
		case ENGINE_GLEW_ERROR:
		printf("ERROR: GLEW ERROR\n");
		return 1;
		break;
		
		case ENGINE_GFX_ERROR:
		printf("ERROR: graphics engine error\n");
		return 1;
		break;
		
	}

	struct vec3f cam_location={0,10,0};
	gfx_create_camera(cam_location, 10000, 0.5*PI);


	struct vec3f rot_axis;
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	struct vec3f pos_model={0,0,40};
	struct model* ship=gfx_load_model("data/models/stealth/stealth.obj",pos_model);
	gfx_model_load_texture("data/textures/stealth.bmp", ship);
	float r=0.6*PI;
	gfx_model_rotate(ship, r, rot_axis);

	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	r=1.4*PI;
	gfx_model_rotate(ship, r, rot_axis);

	int FPS=0;

	struct vec3f color;
	color.x=0.8;
	color.y=0.2;
	color.z=0.21;

	pos_model.x=10;
	pos_model.y=10;
	pos_model.z=30;
	struct model *cube_origin=gfx_create_cube(pos_model, color, 4);
	gfx_model_load_texture("data/textures/box.bmp", cube_origin);

	struct model *cube[1000];

	for(int i=0; i<1000; i++)
	{
		cube[i]=gfx_copy_model(cube_origin);
		pos_model.z=pos_model.z+100;
		gfx_update_model_location(cube[i],pos_model);
	}

	int lasttick=SDL_GetTicks();

	float i=0;
	while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
	{
	/*FPS count*/
	if(SDL_GetTicks()>(lasttick+1000))
	{
		engine_log("FPS: %i\n",FPS);
		FPS=0;
		lasttick=SDL_GetTicks();

	}
	FPS++;

	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	r=0.001;
	gfx_model_rotate(cube_origin, r, rot_axis);

	for(int i=0; i<1000; i++)
	{
		gfx_model_rotate(cube[i], r, rot_axis);
	}


	gfx_new_frame();
	}
	exit(0);
}