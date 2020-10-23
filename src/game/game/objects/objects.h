#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


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

/*ships*/
#define SHIP_TRUE 1
#define SHIP_FALSE 0

struct ship
{
	/*list related members*/
	void *previous_entry;
	void *next_entry;

	/*game related members*/
	/*ship related members*/
		int max_health;
		int current_health;
		struct vec3f position;
		struct vec3f moving_direction;
		int is_moving;
		struct vec3f target_destination;
		float max_speed;
		float current_speed;
		struct model *model;

	/*player related members*/
	int is_player;
	int team;
};

struct ship* game_create_ship();
void game_remove_ship(struct ship *ship);
struct ship* game_select_first_ship();
struct ship* game_select_next_ship();

void game_ships_update();

void game_ship_is_player(struct ship *ship);
void game_ship_new_destination(struct ship *ship, signed char destination_coords[4]);
void game_ship_location(struct ship *ship, struct vec3f location);

#endif
