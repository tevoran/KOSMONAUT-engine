#include "gfx/ui/ui.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>


struct ui_window* gfx_ui_create_window(struct vec2f position, struct vec2f size)
{
	struct ui_window *window=malloc(sizeof(struct ui_window));
	struct vec3f position_3d, sizex, sizey, color;
		position_3d.x=position.x*2-1;
		position_3d.y=position.y*2-1;
		position_3d.z=0;
		sizex.x=(size.x)*2;
		sizex.y=sizex.z=0;
		sizey.y=(size.y)*2;
		sizey.x=sizey.z=0;

		/*setting white as default color*/
		color.x=1;
		color.y=1;
		color.z=1;
		
	window->render_object=gfx_create_quad(position_3d, sizex, sizey, color);
	gfx_ui_set_ui_trigger(window->render_object);
	return window;
}

void gfx_ui_window_texture(char *file_location, struct ui_window *window)
{
	gfx_model_load_texture(file_location, window->render_object);
}


/*ui system intern functions*/
void gfx_ui_set_ui_trigger(struct model *model)
{
	model->ui_element=GFX_TRUE;
}