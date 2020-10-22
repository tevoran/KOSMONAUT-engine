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

	return ships_current_entry;
}