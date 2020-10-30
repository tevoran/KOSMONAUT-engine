#include "objects/objects.h"
#include "SBC.h"

#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLEARANCE 0.1

void game_ships_update()
{
	static long seed=100;
	/*getting current frame time*/
	static clock_t old_time=0;
	static clock_t new_time=0;

	new_time=clock();
	float frame_time_f=(float)new_time/CLOCKS_PER_SEC-(float)old_time/CLOCKS_PER_SEC;
	old_time=new_time;

	struct ship *ship;
	ship=game_select_first_ship();

	while(ship!=NULL)
	{
		if(ship->is_player==SHIP_FALSE)
		{
			/*moving ship*/
				/*rotating towards destination*/
				int is_rotating=SHIP_TRUE;
					struct vec3f direction;
					direction.x=ship->target_destination.x-ship->position.x;
					direction.y=ship->target_destination.y-ship->position.y;
					direction.z=ship->target_destination.z-ship->position.z;

					direction=normalize3f(direction);

					ship->moving_direction=gfx_model_vector_rotate(ship->model, ship->original_orientation);
					ship->moving_direction=normalize3f(ship->moving_direction);

				if(	ship->moving_direction.x<=(direction.x+4*CLEARANCE) &&
					ship->moving_direction.y<=(direction.y+4*CLEARANCE) &&
					ship->moving_direction.z<=(direction.z+4*CLEARANCE) &&

					ship->moving_direction.x>=(direction.x-4*CLEARANCE) &&
					ship->moving_direction.y>=(direction.y-4*CLEARANCE) &&
					ship->moving_direction.z>=(direction.z-4*CLEARANCE))
				{
					is_rotating=SHIP_FALSE;
				}
				else
				{
					struct vec3f negative_moving_direction=vec3f_scale(-1, ship->moving_direction);
					struct vec3f rot_diff=vec3f_add(direction, negative_moving_direction);
					struct vec3f rot_ortho=cross_product(ship->moving_direction, direction);

					gfx_model_rotate(ship->model, ship->max_rotation_speed*frame_time_f, rot_ortho);
					
				}

				/*moving ship towards its location*/
				if(	ship->is_moving==SHIP_TRUE && 
					ship->is_player==SHIP_FALSE &&
					is_rotating==SHIP_FALSE)
				{
					direction=vec3f_scale(ship->current_speed*frame_time_f, direction);
					ship->position=vec3f_add(ship->position, direction);
					gfx_update_model_location(ship->model, ship->position);
				}

				/*if ship reached the destination then stop*/
				if(	ship->position.x<=(ship->target_destination.x+10*CLEARANCE) &&
					ship->position.y<=(ship->target_destination.y+10*CLEARANCE) &&
					ship->position.z<=(ship->target_destination.z+10*CLEARANCE) &&

					ship->position.x>=(ship->target_destination.x-10*CLEARANCE) &&
					ship->position.y>=(ship->target_destination.y-10*CLEARANCE) &&
					ship->position.z>=(ship->target_destination.z-10*CLEARANCE) &&
					ship->is_moving==SHIP_TRUE)
				{
					ship->is_moving=SHIP_FALSE;
					while(1)
					{
						struct vec3f dst_coord;
						seed=long_random(seed);
						dst_coord.x=seed%1600-800;
						seed=long_random(seed);
						dst_coord.y=seed%1600-800;
						seed=long_random(seed);
						dst_coord.z=seed%800-400;
						signed char* dst=game_get_coordinate(dst_coord);
						printf("%s\n", dst);
						game_ship_new_destination(ship, dst);
						if(strstr(dst, "OoB")==NULL)
						{
							break;
						}

					}

				}
		}


		ship=game_select_next_ship();
	}
}