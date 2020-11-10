#include "gfx/ui/ui.h"

#include <stdio.h>
#include <inttypes.h>

struct ui_window* gfx_ui_create_window(uint16_t size_x, uint16_t size_y)
{
	struct ui_window *window=gfx_ui_create_window_list_element();
	/*temporary OpenGL variables*/
	GLuint vertexBufferID;

	/*creating render quad*/
	GLfloat window_base_texture[]=
	{
		1,1,1
	};

	GLfloat window_vertices[]=
	{
		0,0,0,
		0,0,

		size_x,0,0,
		1,0,

		0,size_y,0,
		0,1,

		size_x,size_y,0,
		1,1
	};

	GLuint window_indices[]=
	{
		0,1,2,
		1,2,3
	};

	glGenVertexArrays(1, &window->arrayID);
	glGenBuffers(1, &vertexBufferID);
	glGenBuffers(1, &window->index_bufferID);
	glGenTextures(1, &window->textureID);

	glBindVertexArray(window->arrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, window->index_bufferID);
	glBindTexture(GL_TEXTURE_2D, window->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBufferData(GL_ARRAY_BUFFER, sizeof(window_vertices), window_vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(window_indices), window_indices, GL_STATIC_DRAW);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, window_base_texture);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	return window;
}