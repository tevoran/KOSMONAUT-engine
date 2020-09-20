#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>


#define vertex_element_number 8

struct model* gfx_load_model(char *file_location, struct vec3f location)
{
	struct model* model=gfx_create_model_entry();
	
	GLfloat *vertices=NULL;
	GLuint num_vertices=0;
	
	GLuint *indices=NULL;
	GLuint num_indices=0;
	
	/*finding out the model file type and load the file*/
	if(strstr(file_location, ".obj")!=NULL)
	{
		if(model_load_obj_model(
				file_location,
				&vertices, 
				&num_vertices, 
				vertex_element_number, 
				&indices, 
				&num_indices)!=GFX_NO_ERROR)
		{
			printf("ERROR: couldn't load:\n%s\n",file_location);
			return GFX_ERROR_NULL;
		}
	}
	else
	{
		printf("ERROR: model at %s\nWRONG FILE FORMAT\n",file_location);
		return GFX_ERROR_NULL;
	}
	
	/*writing model relevant data to model struct*/
	model->num_vertices=num_vertices;
	model->num_indices=num_indices;
	
	/*creating a default test texture*/
	GLbyte default_texture[]={
		0, 0, 0,	150, 0, 150,
		150, 0, 150, 	0, 0, 0
	};
	

	/*preparing for future drawing*/
	glGenVertexArrays(1, &model->arrayID);
	glGenBuffers(1, &model->vertex_bufferID);
	glGenBuffers(1, &model->index_bufferID);
	glGenTextures(1, &model->textureID);
	
	glBindVertexArray(model->arrayID);
	glBindBuffer(GL_ARRAY_BUFFER, model->vertex_bufferID);
	glBufferData(GL_ARRAY_BUFFER, model->num_vertices*vertex_element_number*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glBindTexture(GL_TEXTURE_2D, model->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,vertex_element_number*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,vertex_element_number*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,vertex_element_number*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->index_bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->num_indices*sizeof(GLuint), indices, GL_STATIC_DRAW);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, default_texture);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	/*doing gfx engine stuff*/
	gfx_update_model_location(model, location); /*placing it somewhere in the world*/
	
	
	return model;
}