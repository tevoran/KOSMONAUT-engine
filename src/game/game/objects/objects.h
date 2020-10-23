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
struct ship
{
	/*list related members*/
	void *previous_entry;
	void *next_entry;

	/*game related members*/
	struct vec3f position;
	struct vec3f moving_direction;
	struct model *model;
};

struct ship* game_create_ship();
void game_remove_ship(struct ship *ship);

#endif
