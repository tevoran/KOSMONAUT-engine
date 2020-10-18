#include "gfx/ui/ui.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>


struct ui_element* gfx_ui_create_window(struct vec2f position, struct vec2f size)
{
	struct ui_element *ui_window=malloc(sizeof(struct ui_element));
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
		
	ui_window->render_object=gfx_create_quad(position_3d, sizex, sizey, color);
	gfx_ui_set_ui_trigger(ui_window->render_object);
	return ui_window;
}




/*ui system intern functions*/
void gfx_ui_set_ui_trigger(struct model *model)
{
	model->ui_element=GFX_TRUE;
}