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

#define GLEW_STATIC
#undef main

int main(int argc, char **argv[])
{

	game_init();

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
	struct vec3f ship_pos;
	float r;
	struct vec3f ship_current_rotation;

	/*placement if host*/
		ship_pos.x=0;
		ship_pos.y=0;
		ship_pos.z=40;
		ship_current_rotation.x=0;
		ship_current_rotation.y=0;
		ship_current_rotation.z=0;

	/*placement if client*/
	if(engine_config_state().net_client==ENGINE_TRUE)
	{
		ship_pos.x=0;
		ship_pos.y=0;
		ship_pos.z=100;
		ship_current_rotation.x=0;
		ship_current_rotation.y=0;
		ship_current_rotation.z=0;
	}

	struct model *ship=gfx_load_model("data/models/stealth/stealth.obj",ship_pos);
	r=2*PI;
	gfx_model_rotate(ship, r, rot_axis);
	gfx_model_load_texture("data/textures/stealth.bmp", ship);

	/*rotation if client*/
	if(engine_config_state().net_client==ENGINE_TRUE)
	{
			ship_current_rotation.y=ship_current_rotation.y-PI;
			gfx_model_rotate(ship, -PI, rot_axis);
			gfx_camera_rotate(-PI, rot_axis);
	}

	/*other player*/
	struct vec3f other_pos={0,0,0};
	struct model *other_ship=gfx_load_model("data/models/stealth/stealth.obj",other_pos);
	r=2*PI;
	gfx_model_rotate(other_ship, r, rot_axis);
	gfx_model_load_texture("data/textures/stealth.bmp", other_ship);

	/*time related stuff*/
	clock_t old_time=clock();
	clock_t new_time, frame_time;
	float frame_time_f;

	float ship_speed=50;
	float ship_rotation_speed=2.3;

	float scale_test_speed=0.5;

	/*network timers*/
	clock_t new_msg_time=clock();
	clock_t old_msg_time=clock();
	int msg_count=0;

	int quit=0;
	while(!quit) /*while not closing the window the main loop is continuing*/
	{
	engine_fps_count(ENGINE_TRUE,0);

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
	struct vec3f cam_location=ship_pos;
	cam_location.x=cam_location.x+40*sin(-ship_current_rotation.y);
	cam_location.y=cam_location.y+10;
	cam_location.z=cam_location.z-40*cos(-ship_current_rotation.y);
	gfx_camera_location(cam_location);

	/*network with other player*/
			struct net_msg net_msg;
			net_msg=net_recv_msg();
			void *msg=net_msg.msg;
			if(msg!=NULL)
			{
				/*retrieving other players location*/
				other_pos=*(struct vec3f*)msg;
				gfx_update_model_location(other_ship, other_pos);
				nng_free(msg, net_msg.msg_size);
			}


		/*sending position*/
		struct vec3f *msg_out;
		msg_out=&ship_pos;
		net_send_msg(msg_out, sizeof(struct vec3f));

		msg_count++;

	if(msg_count==1)
	{
		msg_count=0;
		net_sync();
	}

	gfx_new_frame();
	}
	exit(0);
}