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
		/*top*/
		-0.5*size,0.5*size,-0.5*size,
		1, 1,
		-0.5*size,0.5*size,0.5*size,
		1, 1,
		0.5*size,0.5*size,-0.5*size,
		1, 1,

		-0.5*size,0.5*size,0.5*size,
		1, 1,
		0.5*size,0.5*size,-0.5*size,
		1, 1,
		0.5*size,0.5*size,0.5*size,
		1, 1,
		
		/*back*/
		-0.5*size,-0.5*size,0.5*size,
		1, 1,
		-0.5*size,0.5*size,0.5*size,
		1, 1,
		0.5*size,-0.5*size,0.5*size,
		1, 1,

		-0.5*size,0.5*size,0.5*size,
		1, 1,
		0.5*size,0.5*size,0.5*size,
		1, 1,
		0.5*size,-0.5*size,0.5*size,
		1, 1,
		
		/*right*/
		0.5*size,0.5*size,-0.5*size,
		1, 1,
		0.5*size,0.5*size,0.5*size,
		1, 1,
		0.5*size,-0.5*size,0.5*size,
		1, 1,

		0.5*size,-0.5*size,0.5*size,
		1, 1,
		0.5*size,-0.5*size,-0.5*size,
		1, 1,
		0.5*size,0.5*size,-0.5*size,
		1, 1,

		/*left*/
		-0.5*size,0.5*size,-0.5*size,
		1, 1,
		-0.5*size,0.5*size,0.5*size,
		1, 1,
		-0.5*size,-0.5*size,0.5*size,
		1, 1,

		-0.5*size,-0.5*size,0.5*size,
		1, 1,
		-0.5*size,-0.5*size,-0.5*size,
		1, 1,
		-0.5*size,0.5*size,-0.5*size,
		1, 1,
		
		/*bottom*/
		-0.5*size,-0.5*size,-0.5*size,
		1, 1,
		-0.5*size,-0.5*size,0.5*size,
		1, 1,
		0.5*size,-0.5*size,-0.5*size,
		1, 1,

		-0.5*size,-0.5*size,0.5*size,
		1, 1,
		0.5*size,-0.5*size,-0.5*size,
		1, 1,
		0.5*size,-0.5*size,0.5*size,
		1, 1,
		
		/*front*/
		-0.5*size,-0.5*size,-0.5*size,
		1, 1,
		-0.5*size,0.5*size,-0.5*size,
		1, 1,
		0.5*size,-0.5*size,-0.5*size,
		1, 1,

		-0.5*size,0.5*size,-0.5*size,
		1, 1,
		0.5*size,0.5*size,-0.5*size,
		1, 1,
		0.5*size,-0.5*size,-0.5*size,
		1, 1,
		
	};
	
	model_entry->num_vertices=sizeof(cube_data)/(5*sizeof(GLfloat));
	
	/*saving OpenGL IDs*/
	glGenVertexArrays(1, &model_entry->arrayID);
	glGenBuffers(1, &model_entry->vertex_bufferID);
	glGenTextures(1, &model_entry->textureID);


	glBindVertexArray(model_entry->arrayID);
	glBindBuffer(GL_ARRAY_BUFFER, model_entry->vertex_bufferID);
	glBindTexture(GL_TEXTURE_2D, model_entry->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);
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