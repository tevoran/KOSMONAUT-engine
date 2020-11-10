#include "gfx/ui/ui.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>


void gfx_ui_window_texture(char *file_location, struct ui_window *window)
{
	gfx_model_load_texture(file_location, window->render_object);
}


/*ui system intern functions*/
void gfx_ui_set_ui_trigger(struct model *model)
{
	model->ui_element=GFX_TRUE;
}