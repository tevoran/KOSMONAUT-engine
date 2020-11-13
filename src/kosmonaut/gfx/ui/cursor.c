#include "gfx/ui/ui.h"

#include "general/general.h"

struct ui_cursor
{
	int16_t pos_x;
	int16_t pos_y;
	uint16_t size_x;
	uint16_t size_y;

	/*window OpenGL related members*/
	GLuint textureID;
	GLuint arrayID;
	GLuint index_bufferID;
};

struct ui_cursor cursor;
int cursor_active=FALSE;

void ui_cursor_init()
{

}