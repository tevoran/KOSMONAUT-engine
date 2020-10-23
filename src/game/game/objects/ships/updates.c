#include "objects/objects.h"
#include "SBC.h"

#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game_ships_update()
{
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
		/*moving ship towards its location*/
		if(ship->is_moving==SHIP_TRUE && ship->is_player==SHIP_FALSE)
		{
			struct vec3f direction;
			direction.x=ship->target_destination.x-ship->position.x;
			direction.y=ship->target_destination.y-ship->position.y;
			direction.z=ship->target_destination.z-ship->position.z;

			direction=normalize3f(direction);
			direction=vec3f_scale(ship->current_speed*frame_time_f, direction);
			ship->position=vec3f_add(ship->position, direction);
			gfx_update_model_location(ship->model, ship->position);
		}

		ship=game_select_next_ship();
	}
}