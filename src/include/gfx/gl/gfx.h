#ifndef GFX_H
#define GFX_H

#include <GL/glew.h>

int gfx_init();
GLuint gfx_loading_shaders(); /*loads, compiles and links vertex and fragment shaders into one program. its handle is returned as GLuint*/

void gfx_new_frame(); /*draws the current frame and clears the buffer for the next frame*/


#endif