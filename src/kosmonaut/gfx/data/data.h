#ifndef KOSMONAUT_DATA
#define KOSMONAUT_DATA

#include <GL/glew.h>
#include <stdlib.h>

void data_texture_load(char *file_location, GLuint *textureID);

void data_texture_load_bmp(
	char *file_location, 
	GLfloat **texture_data, 
	GLsizei *texture_height, 
	GLsizei *texture_width);




#endif