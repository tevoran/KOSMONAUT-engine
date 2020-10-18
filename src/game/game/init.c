#include "SBC.h"

#include <stdio.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <nng/nng.h>

#include "general/general.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "gfx/ui/ui.h"
#include "net/net.h"

int game_init()
{
	/*initialisinge game engine*/
	switch(engine_init("Star Battle Command", "data/config.conf"))
	{
		case ENGINE_NO_ERROR:
		break;
		
		case ENGINE_SDL_ERROR:
		engine_log("ERROR: SDL ERROR\n");
		return 1;
		break;
		
		case ENGINE_GL_ERROR:
		engine_log("ERROR: OpenGL ERROR\n");
		return 1;
		break;
		
		case ENGINE_GLEW_ERROR:
		engine_log("ERROR: GLEW ERROR\n");
		return 1;
		break;
		
		case ENGINE_GFX_ERROR:
		engine_log("ERROR: graphics engine error\n");
		return 1;
		break;
		
	}

	/*initializing network stuff*/
	if(engine_config_state().net_host==ENGINE_TRUE)
	{
		if(net_host_pair(1)!=NET_NOERROR)
		{
			printf("Network error: can't host\n");
			exit(1);
		}
	}
	if(engine_config_state().net_client==ENGINE_TRUE)
	{
		if(net_connect_pair(engine_config_state().net_port,1)!=NET_NOERROR)
		{
			printf("Network error: can't join\n");
			exit(1);
		}
	}

	/*initialising camera*/
	struct vec3f cam_location={0,10,0};
	gfx_create_camera(cam_location, 0.5*PI);
	
	return 0;
}