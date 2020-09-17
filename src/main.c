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

	struct vec3f cam_location={0,0,0};
	gfx_create_camera(cam_location, 10000, 0.5*PI);


	struct vec3f rot_axis;
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	struct vec3f pos_model={0,0,40};
	struct model* ship=gfx_load_model("data/models/stealth/stealth.obj",pos_model);
	float r=0.6*PI;
	gfx_model_rotate(ship, r, rot_axis);

	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	r=1.4*PI;
	gfx_model_rotate(ship, r, rot_axis);



	struct model* ship2=gfx_copy_model(ship);
	pos_model.y=pos_model.y+10;
	gfx_update_model_location(ship2,pos_model);	

	int FPS=0;


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
	gfx_model_rotate(ship, r, rot_axis);
		

	gfx_new_frame();
	}
	exit(0);
}