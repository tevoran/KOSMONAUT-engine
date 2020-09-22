#include "gfx/gfx.h"

#include "maths/maths.h"
#include <inttypes.h>
#include <stdio.h>
#include <GL/glew.h>


/*corner1 and corner2 are relative to the triangle's position*/
struct model* gfx_create_triangle(struct vec3f location, struct vec3f corner1, struct vec3f corner2, struct vec3f color) /*returns a uint32_t handle*/
{
	
	struct model* model_entry=gfx_create_model_entry();

	/*this object doesn't use an index buffer*/
	model_entry->index_bufferID=0;
	
	GLfloat triangle_color_texture[]=
	{
		color.x, color.y, color.z
	};

	GLfloat triangle_data[]=
	{
		0,0,0,
		1,1,
		
		corner1.x,corner1.y,corner1.z,
		1,1,
		
		corner2.x,corner2.y,corner2.z,
		1,1,
	};
	
	
	
	model_entry->num_vertices=3; /*value is three, because this is a triangle*/
	
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

	glBufferData(GL_ARRAY_BUFFER,sizeof(triangle_data),triangle_data,GL_STATIC_DRAW);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, triangle_color_texture);
	
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