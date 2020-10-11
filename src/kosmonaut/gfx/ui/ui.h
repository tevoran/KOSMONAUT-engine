#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>

struct ui_element
{
	struct model *render_object; /*this is used for rendering*/
};

struct ui_element* gfx_ui_create_window(struct vec2f position, struct vec2f size);

/*ui system intern functions*/
void gfx_ui_set_ui_trigger(struct model *model);