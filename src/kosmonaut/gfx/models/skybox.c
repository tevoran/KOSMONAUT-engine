#include "gfx/gfx.h"

#include "general/general.h"
#include "maths/maths.h"

#define a 0.2

struct model *front=NULL, 
			*right=NULL, 
			*back=NULL, 
			*left=NULL, 
			*top=NULL, 
			*bottom=NULL;

void gfx_create_skybox(
	char *file_location_front,
	char *file_location_right, 
	char *file_location_back, 
	char *file_location_left, 
	char *file_location_top, 
	char *file_location_bottom)
{
	struct vec3f cam_location=gfx_camera_get_location();
	struct config config=engine_config_state();

	/*front*/
	struct vec3f color={1,1,1};
	struct vec3f sizex, sizey;
	struct vec3f pos=cam_location;
		pos.x=cam_location.x-a*config.viewing_distance;
		pos.y=cam_location.y-a*config.viewing_distance;
		pos.z=cam_location.z+a*config.viewing_distance;
	sizex.x=2*a*config.viewing_distance;
	sizex.y=0;
	sizex.z=0;
	sizey.x=0;
	sizey.y=2*a*config.viewing_distance;
	sizey.z=0;

	front=gfx_create_quad(pos, sizex, sizey, color);
	gfx_model_load_texture(file_location_front, front);

	/*right*/
		pos.x=cam_location.x+a*config.viewing_distance;
		pos.y=cam_location.y-a*config.viewing_distance;
		pos.z=cam_location.z+a*config.viewing_distance;
	sizex.x=0;
	sizex.y=0;
	sizex.z=-2*a*config.viewing_distance;
	sizey.x=0;
	sizey.y=2*a*config.viewing_distance;
	sizey.z=0;

	right=gfx_create_quad(pos, sizex, sizey, color);
	gfx_model_load_texture(file_location_right, right);

	/*back*/
		pos.x=cam_location.x-a*config.viewing_distance;
		pos.y=cam_location.y-a*config.viewing_distance;
		pos.z=cam_location.z-a*config.viewing_distance;
	sizex.x=2*a*config.viewing_distance;
	sizex.y=0;
	sizex.z=0;
	sizey.x=0;
	sizey.y=2*a*config.viewing_distance;
	sizey.z=0;

	back=gfx_create_quad(pos, sizex, sizey, color);
	gfx_model_load_texture(file_location_back, back);

	/*left*/
		pos.x=cam_location.x-a*config.viewing_distance;
		pos.y=cam_location.y-a*config.viewing_distance;
		pos.z=cam_location.z-a*config.viewing_distance;
	sizex.x=0;
	sizex.y=0;
	sizex.z=2*a*config.viewing_distance;
	sizey.x=0;
	sizey.y=2*a*config.viewing_distance;
	sizey.z=0;

	left=gfx_create_quad(pos, sizex, sizey, color);
	gfx_model_load_texture(file_location_left, left);
	
	/*top*/
		pos.x=cam_location.x-a*config.viewing_distance;
		pos.y=cam_location.y+a*config.viewing_distance;
		pos.z=cam_location.z-a*config.viewing_distance;
	sizex.x=2*a*config.viewing_distance;
	sizex.y=0;
	sizex.z=0;
	sizey.x=0;
	sizey.y=0;
	sizey.z=2*a*config.viewing_distance;

	top=gfx_create_quad(pos, sizex, sizey, color);
	gfx_model_load_texture(file_location_top, top);

	/*bottom*/
		pos.x=cam_location.x-a*config.viewing_distance;
		pos.y=cam_location.y-a*config.viewing_distance;
		pos.z=cam_location.z-a*config.viewing_distance;
	sizex.x=2*a*config.viewing_distance;
	sizex.y=0;
	sizex.z=0;
	sizey.x=0;
	sizey.y=0;
	sizey.z=2*a*config.viewing_distance;

	bottom=gfx_create_quad(pos, sizex, sizey, color);
	gfx_model_load_texture(file_location_bottom, bottom);

}

void gfx_update_skybox_location()
{
		if(front!=NULL)
		{
			struct vec3f cam_location=gfx_camera_get_location();
			struct vec3f pos;
			struct config config=engine_config_state();

			pos.x=cam_location.x-a*config.viewing_distance;
			pos.y=cam_location.y-a*config.viewing_distance;
			pos.z=cam_location.z+a*config.viewing_distance;
			gfx_update_model_location(front, pos);

			pos.x=cam_location.x+a*config.viewing_distance;
			pos.y=cam_location.y-a*config.viewing_distance;
			pos.z=cam_location.z+a*config.viewing_distance;
			gfx_update_model_location(right, pos);

			pos.x=cam_location.x-a*config.viewing_distance;
			pos.y=cam_location.y-a*config.viewing_distance;
			pos.z=cam_location.z-a*config.viewing_distance;
			gfx_update_model_location(back, pos);

			pos.x=cam_location.x-a*config.viewing_distance;
			pos.y=cam_location.y-a*config.viewing_distance;
			pos.z=cam_location.z-a*config.viewing_distance;
			gfx_update_model_location(left, pos);

			pos.x=cam_location.x-a*config.viewing_distance;
			pos.y=cam_location.y+a*config.viewing_distance;
			pos.z=cam_location.z-a*config.viewing_distance;
			gfx_update_model_location(top, pos);

			pos.x=cam_location.x-a*config.viewing_distance;
			pos.y=cam_location.y-a*config.viewing_distance;
			pos.z=cam_location.z-a*config.viewing_distance;
			gfx_update_model_location(bottom, pos);
		}

}