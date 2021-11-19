#ifndef SBC_H
#define SBC_H

#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//#include <nng/nng.h>


/*engine*/
#include "general/general.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "gfx/ui/ui.h"
#include "net/net.h"

/*game*/
#include "objects/objects.h"

int game_init();
void game_player_controls_input(struct ship *player);

signed char *game_get_coordinate(struct vec3f position);
struct vec3f game_set_coordinate(signed char coordinate[4]);

#endif