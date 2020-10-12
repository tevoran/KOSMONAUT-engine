#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "general/general.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "gfx/ui/ui.h"
#include "net/net.h"

#define GLEW_STATIC
#undef main

int main(int argc, char **argv[])
{
	/*initialisinge game engine*/
	switch(engine_init("Star Battle Command", "data/config.conf"))
	{
		case ENGINE_NO_ERROR:
		break;
		
		case ENGINE_SDL_ERROR:
		engine_log("ERROR: SDL ERROR\n");
		return 1;
		break;
		
		case ENGINE_GL_ERROR:
		engine_log("ERROR: OpenGL ERROR\n");
		return 1;
		break;
		
		case ENGINE_GLEW_ERROR:
		engine_log("ERROR: GLEW ERROR\n");
		return 1;
		break;
		
		case ENGINE_GFX_ERROR:
		engine_log("ERROR: graphics engine error\n");
		return 1;
		break;
		
	}

	struct vec3f cam_location={0,10,0};
	gfx_create_camera(cam_location, 0.5*PI);

	/*skybox*/
	gfx_create_skybox(
		"data/textures/skybox/front.bmp",
		"data/textures/skybox/right.bmp",
		"data/textures/skybox/back.bmp",
		"data/textures/skybox/left.bmp",
		"data/textures/skybox/top.bmp",
		"data/textures/skybox/bottom.bmp");

	/*ship*/
	struct vec3f rot_axis;
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	struct vec3f ship_pos={0,0,40};
	struct model* ship=gfx_load_model("data/models/stealth/stealth.obj",ship_pos);
	gfx_model_load_texture("data/textures/stealth.bmp", ship);
	float r=0.6*PI;
	gfx_model_rotate(ship, r, rot_axis);
	struct vec3f ship_current_rotation;
	ship_current_rotation.x=0;
	ship_current_rotation.y=0;
	ship_current_rotation.z=0;

	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	r=1.4*PI;
	gfx_model_rotate(ship, r, rot_axis);

	struct vec3f color={0,0,0};
	struct vec3f pos_model={10,10,30};	
	struct model *cube_origin=gfx_create_cube(pos_model, color, 4);
	gfx_model_load_texture("data/textures/box.bmp", cube_origin);

	struct model *cube[1000];

	for(int i=0; i<1000; i++)
	{
		cube[i]=gfx_copy_model(cube_origin);
		pos_model.z=pos_model.z+75;
		gfx_update_model_location(cube[i],pos_model);
	}

	/*NNG_TEST*/
	net_test_send();

	/*ui test*/
	struct vec2f win_pos, win_size;
	win_pos.x=0;
	win_pos.y=0;
	win_size.x=0.25;
	win_size.y=0.25;
	struct ui_element *window=gfx_ui_create_window(win_pos, win_size);
	gfx_model_load_texture("data/textures/window.bmp", window->render_object);

	win_pos.x=0.75;
	win_pos.y=0;
	win_size.x=0.25;
	win_size.y=0.25;
	struct ui_element *window2=gfx_ui_create_window(win_pos, win_size);
	gfx_model_load_texture("data/textures/window.bmp", window2->render_object);

	/*time related stuff*/
	int FPS=0;
	int lasttick=SDL_GetTicks();
	clock_t old_time=clock();
	clock_t new_time, frame_time;
	float frame_time_f;

	float cube_rotation_speed=1; /*1 radian per second*/
	float ship_speed=50;
	float ship_rotation_speed=2.3;

	float scale_test_speed=0.5;

	int quit=0;
	while(!quit) /*while not closing the window the main loop is continuing*/
	{
	/*FPS count*/
	if(SDL_GetTicks()>(lasttick+1000))
	{
		engine_log("FPS: %i\n",FPS);
		FPS=0;
		lasttick=SDL_GetTicks();
	printf("F: %i us\n", (int)(frame_time_f*1000000));
	}
	FPS++;

	/*determining time*/
	new_time=clock();
	frame_time=new_time-old_time;
	old_time=new_time;
	frame_time_f=(float)frame_time/CLOCKS_PER_SEC;

	/*handling input via SDL2*/
	{
		const Uint8 *keyboard_state=SDL_GetKeyboardState(NULL); 
		SDL_Event event;

		if(keyboard_state[SDL_SCANCODE_W])
		{
			ship_pos.z=ship_pos.z+ship_speed*frame_time_f*cos(ship_current_rotation.y);
			ship_pos.x=ship_pos.x+ship_speed*frame_time_f*sin(ship_current_rotation.y);
		}

		if(keyboard_state[SDL_SCANCODE_S])
		{
			ship_pos.z=ship_pos.z-ship_speed*frame_time_f*cos(ship_current_rotation.y);
			ship_pos.x=ship_pos.x-ship_speed*frame_time_f*sin(ship_current_rotation.y);
		}

		if(keyboard_state[SDL_SCANCODE_A])
		{
			ship_current_rotation.y=ship_current_rotation.y-ship_rotation_speed*frame_time_f;
			gfx_model_rotate(ship, -ship_rotation_speed*frame_time_f, rot_axis);
			gfx_camera_rotate(-ship_rotation_speed*frame_time_f, rot_axis);
		}

		if(keyboard_state[SDL_SCANCODE_D])
		{
			ship_current_rotation.y=ship_current_rotation.y+ship_rotation_speed*frame_time_f;
			gfx_model_rotate(ship, ship_rotation_speed*frame_time_f, rot_axis);
			gfx_camera_rotate(ship_rotation_speed*frame_time_f, rot_axis);
		}

		if(keyboard_state[SDL_SCANCODE_ESCAPE])
		{
			quit=1;

		}
		SDL_PollEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				quit=1;
				break;
		}
	}

	/*ship and camera*/
	gfx_update_model_location(ship, ship_pos);
	cam_location=ship_pos;
	cam_location.x=cam_location.x+40*sin(-ship_current_rotation.y);
	cam_location.y=cam_location.y+10;
	cam_location.z=cam_location.z-40*cos(-ship_current_rotation.y);
	gfx_camera_location(cam_location);

	/*rotating stuff*/
	rot_axis.x=0;
	rot_axis.y=1;
	rot_axis.z=0;
	r=cube_rotation_speed*frame_time_f;
	gfx_model_rotate(cube_origin, r, rot_axis);
	for(int i=0; i<1000; i++)
	{
		gfx_model_rotate(cube[i], r, rot_axis);
	}


	gfx_new_frame();
	}
	exit(0);
}