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
	struct vec2f view_direction={0,0};
	gfx_create_camera(cam_location,view_direction, 10000, 0.5*PI);


	struct vec3f rot_axis;
	rot_axis.x=0;
	rot_axis.y=0;
	rot_axis.z=1;
	struct vec3f pos_model={0,0-800,2000};
	struct model* cat=gfx_load_model("data/models/test/woman.obj",pos_model);
	float r=1.5*PI;
	gfx_model_rotate(cat, r, rot_axis);

	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	r=1.4*PI;
	gfx_model_rotate(cat, r, rot_axis);
	
	glPolygonMode(GL_FRONT, GL_FILL);
	
	int FPS=0;
	int lasttick=SDL_GetTicks();
	
	float i=0;
	while(engine_get_event().type!=SDL_QUIT) /*while not closing the window the main loop is continuing*/
	{
	/*FPS count*/
	if(SDL_GetTicks()>(lasttick+1000))
	{
		printf("FPS: %i\n",FPS);
		FPS=0;
		lasttick=SDL_GetTicks();
	}
	FPS++;

	rot_axis.x=0;
	rot_axis.y=0;
	rot_axis.z=1;
	r=0.001;
	gfx_model_rotate(cat, r, rot_axis);
		
	gfx_new_frame();
	}
	exit(0);
}