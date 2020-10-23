#include "objects/objects.h"

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
		free(ship);
	}

	/*the first ship of the list*/
	if(ship->previous_entry==NULL && ship->next_entry!=NULL)
	{
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