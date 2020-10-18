#ifndef KOSMONAUT_UI_H
#define KOSMONAUT_UI_H

#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>

/*gui*/
struct ui_element
{
	struct model *render_object; /*this is used for rendering*/
};

struct ui_font
{
	GLuint textureID;
	GLuint num_characters;
};

struct ui_element* gfx_ui_create_window(struct vec2f position, struct vec2f size);
struct ui_font* gfx_ui_load_font(char *file_location, uint32_t num_characters);
struct model* gfx_ui_printf(float pos_x, float pos_y, struct ui_font *font, int font_size_pt, const char *text, ...);

/*ui system intern functions*/
void gfx_ui_set_ui_trigger(struct model *model);

#endif