#ifndef KOSMONAUT_UI_H
#define KOSMONAUT_UI_H

#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <GL/glew.h>

/*gui*/
struct ui_window
{
	/*list members*/
	void *next_entry;
	void *previous_entry;

	/*window members*/
	int16_t pos_x;
	int16_t pos_y;
	uint16_t size_x;
	uint16_t size_y;

	/*window OpenGL related members*/
	GLuint textureID;
	GLuint arrayID;
	GLuint index_bufferID;

	/*subelements*/
	void *subelements;

	struct model *render_object; /*this is used for rendering*/
};

struct ui_font
{
	GLuint textureID;
	GLuint num_characters;
};

/*element list*/
struct ui_window* gfx_ui_create_window_list_element();
struct ui_window* gfx_ui_window_select_first_element();
struct ui_window* gfx_ui_window_select_next_element();
void gfx_ui_window_remove_window(struct ui_window *window);
	void gfx_ui_window_list_init_data(struct ui_window *window);

/*windows*/
struct ui_window* gfx_ui_create_window(uint16_t size_x, uint16_t size_y, int16_t pos_x, int16_t pos_y);
void gfx_ui_set_window_location(struct ui_window *window, int16_t pos_x, int16_t pos_y);
void gfx_ui_resize_window(struct ui_window *window, uint16_t size_x, uint16_t size_y);
void gfx_ui_window_texture(struct ui_window *window, char *file_location);
void gfx_ui_copy_window_texture(struct ui_window *window_src, struct ui_window *window_dst);

/*text*/
struct ui_font* gfx_ui_load_font(char *file_location, uint32_t num_characters);
void gfx_ui_set_font(char *file_location, uint32_t num_characters);
struct model* gfx_ui_printf(float pos_x, float pos_y, struct ui_font *font, int font_size_pt, const char *text, ...);

/*ui system intern functions*/
void gfx_ui_set_ui_trigger(struct model *model);

#endif