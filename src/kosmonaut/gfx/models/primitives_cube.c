#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


struct model* gfx_create_cube(struct vec3f location, struct vec3f color, float size)
{
	struct model* model_entry=gfx_create_model_entry();
	
	/*this object doesn't use an index buffer*/
	model_entry->index_bufferID=0;
	
	GLfloat cube_color_texture[]=
	{
		color.x, color.y, color.z
	};

	GLfloat cube_data[]=
	{
		/*front*/
		-0.5*size,-0.5*size,-0.5*size,
		0, 0,

		0.5*size,-0.5*size,-0.5*size,
		1, 0,

		-0.5*size,0.5*size,-0.5*size,
		0, 1,

		0.5*size,0.5*size,-0.5*size,
		1, 1,

		/*back*/
		-0.5*size,-0.5*size,0.5*size,
		0, 0,

		0.5*size,-0.5*size,0.5*size,
		1, 0,

		-0.5*size,0.5*size,0.5*size,
		0, 1,

		0.5*size,0.5*size,0.5*size,
		1, 1,

		/*bottom*/
		-0.5*size,-0.5*size,-0.5*size,
		0, 0,

		0.5*size,-0.5*size,-0.5*size,
		1, 0,

		-0.5*size,-0.5*size,0.5*size,
		0, 1,

		0.5*size,-0.5*size,0.5*size,
		1, 1,

		/*top*/
		-0.5*size,0.5*size,-0.5*size,
		0, 0,

		0.5*size,0.5*size,-0.5*size,
		1, 0,

		-0.5*size,0.5*size,0.5*size,
		0, 1,

		0.5*size,0.5*size,0.5*size,
		1, 1,

		/*right*/
		0.5*size,-0.5*size,-0.5*size,
		0, 0,

		0.5*size,-0.5*size,0.5*size,
		1, 0,

		0.5*size,0.5*size,-0.5*size,
		0, 1,

		0.5*size,0.5*size,0.5*size,
		1, 1,

		/*left*/
		-0.5*size,-0.5*size,-0.5*size,
		0, 0,

		-0.5*size,-0.5*size,0.5*size,
		1, 0,

		-0.5*size,0.5*size,-0.5*size,
		0, 1,

		-0.5*size,0.5*size,0.5*size,
		1, 1,

	};
	
	GLuint cube_indices[]=
	{
		/*front face*/
		0,1,2,
		1,2,3,

		/*back face*/
		4,5,6,
		5,6,7,

		/*bottom face*/
		8,9,10,
		9,10,11,

		/*top face*/
		12,13,14,
		13,14,15,

		/*right face*/
		16,17,18,
		17,18,19,

		/*left face*/
		20,21,22,
		21,22,23,

	};

	model_entry->num_vertices=sizeof(cube_data)/(5*sizeof(GLfloat));
	model_entry->num_indices=sizeof(cube_indices)/sizeof(GLuint);

	/*saving OpenGL IDs*/
	glGenVertexArrays(1, &model_entry->arrayID);
	glGenBuffers(1, &model_entry->vertex_bufferID);
	glGenTextures(1, &model_entry->textureID);
	glGenBuffers(1, &model_entry->index_bufferID);


	glBindVertexArray(model_entry->arrayID);
	glBindBuffer(GL_ARRAY_BUFFER, model_entry->vertex_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_entry->index_bufferID);
	glBindTexture(GL_TEXTURE_2D, model_entry->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model_entry->num_indices*sizeof(GLuint), cube_indices, GL_STATIC_DRAW);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, cube_color_texture);
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	/*gfx engine stuff*/
	gfx_update_model_location(model_entry,location);
	
	/*clean up*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	return model_entry;
}