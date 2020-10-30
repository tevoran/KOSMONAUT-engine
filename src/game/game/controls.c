#include "SBC.h"
#include "objects/objects.h"

#include "general/general.h"
#include "gfx/gfx.h"
#include "gfx/ui/ui.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <time.h>

#define player_speed 50
#define player_rot_speed 500

void game_player_controls_input(struct ship *player)
{
	struct vec3f cam_location_origin={0,12,-45};
	static struct vec3f moving_direction={0,0,1};
	struct vec3f moving_direction_origin={0,0,1};

		static struct ui_font *font=NULL;
		if(font==NULL)
		{
			font=gfx_ui_load_font("data/textures/bitmapfonts/ConsoleFont.bmp", 256);
		}

	static struct model *text=NULL;
	if(text!=NULL)
	{
		gfx_delete_model_entry(text);
	}
	text=gfx_ui_printf(0, 0.9, font, 32, "MOVING DIRECTION: %f %f %f", moving_direction.x, moving_direction.y, moving_direction.z);

	/*getting timers*/
	static clock_t old_time=0;

	clock_t new_time=clock();
	float frame_time_f=(float)(new_time-old_time)/CLOCKS_PER_SEC;
	old_time=new_time;

	/*controls*/
	/*keyboard*/
	const Uint8 *keyboard_state=SDL_GetKeyboardState(NULL); 

	if(keyboard_state[SDL_SCANCODE_W])
	{
		player->position.x=player->position.x+moving_direction.x*player_speed*frame_time_f;
		player->position.y=player->position.y+moving_direction.y*player_speed*frame_time_f;
		player->position.z=player->position.z+moving_direction.z*player_speed*frame_time_f;
	}

	if(keyboard_state[SDL_SCANCODE_S])
	{
		player->position.x=player->position.x-moving_direction.x*player_speed*frame_time_f;
		player->position.y=player->position.y-moving_direction.y*player_speed*frame_time_f;
		player->position.z=player->position.z-moving_direction.z*player_speed*frame_time_f;
	}

	if(keyboard_state[SDL_SCANCODE_A])
	{
		gfx_model_rotate_euler(player->model, player_rot_speed*frame_time_f*0.01, 'z');
	}

	if(keyboard_state[SDL_SCANCODE_D])
	{
		gfx_model_rotate_euler(player->model, -player_rot_speed*frame_time_f*0.01, 'z');
	}


	/*mouse*/
	static SDL_Event event;
	signed int mouse_x=0;
	signed int mouse_y=0;
	SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
	if(mouse_x!=0 || mouse_y!=0)
	{
		/*x-axis motion*/
		struct vec3f rot_axis;
		rot_axis.x=0;
		rot_axis.y=1;
		rot_axis.z=0;
		float mouse_rot_x=player_rot_speed*frame_time_f*(float)mouse_x/(float)engine_config_state().resolution_x;
		gfx_model_rotate(player->model, mouse_rot_x, rot_axis);

		struct vec3f moving_direction_tmp=moving_direction_origin;
		moving_direction=gfx_model_vector_rotate(player->model, moving_direction_tmp);

		/*y-axis motion*/
		rot_axis.x=1;
		rot_axis.y=0;
		rot_axis.z=0;

		float mouse_rot_y=player_rot_speed*frame_time_f*(float)mouse_y/(float)engine_config_state().resolution_y;
		gfx_model_rotate(player->model, -mouse_rot_y, rot_axis);

		moving_direction_tmp=moving_direction_origin;
		moving_direction=gfx_model_vector_rotate(player->model, moving_direction_tmp);

		moving_direction=normalize3f(moving_direction);
	}

	/*camera location*/
	gfx_update_model_location(player->model, player->position);
	struct vec3f cam_location;
	struct vec3f cam_location_relative_player;

		cam_location_relative_player=gfx_model_vector_rotate(player->model, cam_location_origin);

	cam_location=vec3f_add(player->position, cam_location_relative_player);
	gfx_camera_location(cam_location);

	gfx_camera_look_at(player->position,
		cross_product(moving_direction,
			cross_product(cam_location_relative_player, moving_direction)));

	/*moving ship*/

		if(keyboard_state[SDL_SCANCODE_ESCAPE])
		{
			engine_shutdown();
			exit(0);
		}

	return;
}