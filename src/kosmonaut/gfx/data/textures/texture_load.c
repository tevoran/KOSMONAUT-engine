#include "gfx/data/data.h"

#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <string.h>

void data_texture_load(char *file_location, GLuint *textureID)
{
	GLfloat *texture_data=NULL;
	GLsizei texture_height=0;
	GLsizei texture_width=0;

	/*checking the file extension*/
	if(strstr(file_location, ".bmp")!=NULL)
	{
		data_texture_load_bmp(
			file_location, 
			&texture_data,
			&texture_height,
			&texture_width);
	}
	
	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_height, texture_width, 0, GL_RGB, GL_FLOAT, texture_data);

	free(texture_data);
}