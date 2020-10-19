#include "SBC.h"
#include "objects/objects.h"

#include <SDL2/SDL.h>
#include <time.h>

#define player_speed 30
#define player_rot_speed 6
#define cam_distance 50

void game_player_controls_input(struct ship *player)
{
	/*getting timers*/
	static clock_t old_time=0;

	clock_t new_time=clock();
	float frame_time_f=(float)(new_time-old_time)/CLOCKS_PER_SEC;
	old_time=new_time;

	/*controls*/
	const Uint8 *keyboard_state=SDL_GetKeyboardState(NULL); 

	if(keyboard_state[SDL_SCANCODE_W])
	{
		player->position.z=player->position.z+player_speed*frame_time_f*cos(player->rotation.y);
		player->position.x=player->position.x+player_speed*frame_time_f*sin(player->rotation.y);
	}

	if(keyboard_state[SDL_SCANCODE_S])
	{
		player->position.z=player->position.z-player_speed*frame_time_f*cos(player->rotation.y);
		player->position.x=player->position.x-player_speed*frame_time_f*sin(player->rotation.y);
	}

	if(keyboard_state[SDL_SCANCODE_A])
	{
		struct vec3f rot_axis;
		rot_axis.x=0;
		rot_axis.y=1;
		rot_axis.z=0;

		player->rotation.y=player->rotation.y-player_rot_speed*frame_time_f;
		gfx_model_rotate(player->model, -player_rot_speed*frame_time_f, rot_axis);
		gfx_camera_rotate(-player_rot_speed*frame_time_f, rot_axis);
	}

	if(keyboard_state[SDL_SCANCODE_D])
	{
		struct vec3f rot_axis;
		rot_axis.x=0;
		rot_axis.y=1;
		rot_axis.z=0;

		player->rotation.y=player->rotation.y+player_rot_speed*frame_time_f;
		gfx_model_rotate(player->model, player_rot_speed*frame_time_f, rot_axis);
		gfx_camera_rotate(player_rot_speed*frame_time_f, rot_axis);
	}

	gfx_update_model_location(player->model, player->position);
	struct vec3f cam_location;
	cam_location.x=player->position.x+cam_distance*sin(-player->rotation.y);
	cam_location.y=player->position.y+10;
	cam_location.z=player->position.z-cam_distance*cos(-player->rotation.y);
	gfx_camera_location(cam_location);

		if(keyboard_state[SDL_SCANCODE_ESCAPE])
		{
			exit(0);

		}

	return;
}