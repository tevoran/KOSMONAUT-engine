#include "objects/objects.h"

#include "SBC.h"

#include "gfx/gfx.h"

#include <stdio.h>
#include <stdlib.h>


struct ship *ships_initial_entry=NULL;
struct ship *ships_current_entry=NULL;

struct ship* game_create_ship()
{
	/*initial ship*/
	if(ships_initial_entry==NULL)
	{
		ships_initial_entry=malloc(sizeof(struct ship));

		ships_initial_entry->previous_entry=NULL;
		ships_initial_entry->next_entry=NULL;

		/*setting default values for ship struct*/
		ships_initial_entry->is_moving=SHIP_FALSE;
		ships_initial_entry->is_player=SHIP_FALSE;
		ships_initial_entry->current_speed=50;
		ships_initial_entry->original_orientation.x=0;
		ships_initial_entry->original_orientation.y=0;
		ships_initial_entry->original_orientation.z=1;
		ships_initial_entry->max_rotation_speed=1;

		return ships_initial_entry;
	}

	/*regular added ship*/
	/*looking for last entry*/
	ships_current_entry=ships_initial_entry;
	while(ships_current_entry->next_entry!=NULL)
	{
		ships_current_entry=ships_current_entry->next_entry;
	}

	void *previous_entry=ships_current_entry;
	ships_current_entry->next_entry=malloc(sizeof(struct ship));
	ships_current_entry=ships_current_entry->next_entry;
	ships_current_entry->previous_entry=previous_entry;
	ships_current_entry->next_entry=NULL;

		/*setting default values for ship struct*/
		ships_current_entry->is_moving=SHIP_FALSE;
		ships_current_entry->is_player=SHIP_FALSE;
		ships_current_entry->current_speed=50;
		ships_current_entry->original_orientation.x=0;
		ships_current_entry->original_orientation.y=0;
		ships_current_entry->original_orientation.z=1;
		ships_current_entry->max_rotation_speed=1;

	return ships_current_entry;
}

void game_remove_ship(struct ship *ship)
{
	if(ship->model!=NULL)
	{
		gfx_delete_model_entry(ship->model);
	}
	/*if there is only one ship*/
	if(ship->previous_entry==NULL && ship->next_entry==NULL)
	{
		ships_initial_entry=NULL;
		free(ship);
	}

	/*the first ship of the list*/
	if(ship->previous_entry==NULL && ship->next_entry!=NULL)
	{
		ships_initial_entry=ship->next_entry;
		struct ship *next_ship=ship->next_entry;
		next_ship->previous_entry=NULL;
		free(ship);

	}

	/*a ship in the middle of the list*/
	if(ship->previous_entry!=NULL && ship->next_entry!=NULL)
	{
		struct ship *last_ship=ship->previous_entry;
		last_ship->next_entry=ship->next_entry;
		free(ship);
	}

	/*the last ship of the list*/
	if(ship->previous_entry!=NULL && ship->next_entry==NULL)
	{
		struct ship *last_ship=ship->previous_entry;
		last_ship->next_entry=NULL;
		free(ship);
	}

	return;
}

struct ship* game_select_first_ship()
{
	struct ship *ship=NULL;
	if(ships_initial_entry!=NULL)
	{
		ship=ships_initial_entry;
		ships_current_entry=ship;
	}
	return ship;
}

struct ship* game_select_next_ship()
{
	struct ship *ship=NULL;
	if(ships_current_entry->next_entry!=NULL)
	{
		ships_current_entry=ships_current_entry->next_entry;
		ship=ships_current_entry;
	}
	return ship;
}



/*functions for writing to special members of the ships*/
void game_ship_is_player(struct ship *ship)
{
	ship->is_player=SHIP_TRUE;
}

void game_ship_new_destination(struct ship *ship, signed char destination_coords[4])
{
	struct vec3f destination_location=game_set_coordinate(destination_coords);
	ship->is_moving=SHIP_TRUE;
	ship->target_destination=destination_location;
	destination_location=vec3f_scale(-1, destination_location);
	ship->moving_direction=vec3f_add(ship->moving_direction, destination_location);
	ship->moving_direction=normalize3f(ship->moving_direction);
	printf("SHIP_MOVING moving_direction: %f %f %f\n", ship->moving_direction.x, ship->moving_direction.y, ship->moving_direction.z);
}

void game_ship_location(struct ship *ship, struct vec3f location)
{
	ship->position=location;
	gfx_update_model_location(ship->model, location);
}