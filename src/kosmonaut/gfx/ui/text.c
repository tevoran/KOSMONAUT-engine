#include "gfx/ui/ui.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <inttypes.h>
#include <stdarg.h>

GLuint font_texture_id;

/*only bitmap fonts are currently supported*/
struct ui_font* gfx_ui_load_font(char *file_location, uint32_t num_characters)
{
	struct ui_font *font=malloc(sizeof(struct ui_font));

	font->num_characters=num_characters;

	/*loading bitmap font*/
	GLfloat *font_image_data=NULL;
	GLsizei height=0, width=0;
	gfx_model_texture_load_bmp(file_location, &font_image_data, &height, &width);


	glGenTextures(1, &font->textureID);
	glBindTexture(GL_TEXTURE_2D, font->textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, font_image_data);

	printf("Font size: %ix%i\n", height, width);

	free(font_image_data);

	return font;
}

/*writing text*/
struct model* gfx_ui_printf(float pos_x, float pos_y, struct ui_font *font, int font_size_pt, const char *text, ...)
{
	/*formatting text*/
	va_list args;
	va_start(args, text);

	char f_text[1024];
	int f_text_sz=vsprintf(f_text, text, args);
	va_end(args);

	/*creating quads*/
	struct model* text_batch=gfx_create_model_entry();

	GLfloat *vertex_buffer=malloc(sizeof(GLfloat)*5*4*f_text_sz);
	GLuint *index_buffer=malloc(sizeof(GLuint)*6*f_text_sz);

	/*writing vertex buffer*/
	GLfloat *vertex_buffer_write=vertex_buffer;
	char *f_text_read=f_text;

	GLfloat char_size_x=(GLfloat)font_size_pt/(GLfloat)engine_config_state().resolution_x;
	GLfloat char_size_y=(GLfloat)font_size_pt/(GLfloat)engine_config_state().resolution_y;

	for(int i=0; i<f_text_sz; i++)
	{
		/*first vertex*/
		*vertex_buffer_write=-1+i*char_size_x;
		vertex_buffer_write++;
		*vertex_buffer_write=-1;
		vertex_buffer_write++;
		*vertex_buffer_write=0;
		vertex_buffer_write++;

		f_text_read=f_text+i;
		*vertex_buffer_write=(GLfloat)(uint8_t)f_text[i]/(GLfloat)font->num_characters;
		vertex_buffer_write++;
		*vertex_buffer_write=0;
		vertex_buffer_write++;

		/*second vertex*/
		*vertex_buffer_write=-1+i*char_size_x;
		vertex_buffer_write++;
		*vertex_buffer_write=-1+char_size_y;
		vertex_buffer_write++;
		*vertex_buffer_write=0;
		vertex_buffer_write++;

		f_text_read=f_text+i;
		*vertex_buffer_write=(GLfloat)(uint8_t)f_text[i]/(GLfloat)font->num_characters;
		vertex_buffer_write++;
		*vertex_buffer_write=1;
		vertex_buffer_write++;

		/*third vertex*/
		*vertex_buffer_write=-1+(i+1)*char_size_x;
		vertex_buffer_write++;
		*vertex_buffer_write=-1;
		vertex_buffer_write++;
		*vertex_buffer_write=0;
		vertex_buffer_write++;

		f_text_read=f_text+i;
		*vertex_buffer_write=(GLfloat)(uint8_t)(f_text[i]+1)/(GLfloat)font->num_characters;
		vertex_buffer_write++;
		*vertex_buffer_write=0;
		vertex_buffer_write++;

		/*fourth vertex*/
		*vertex_buffer_write=-1+(i+1)*char_size_x;
		vertex_buffer_write++;
		*vertex_buffer_write=-1+char_size_y;
		vertex_buffer_write++;
		*vertex_buffer_write=0;
		vertex_buffer_write++;

		f_text_read=f_text+i;
		*vertex_buffer_write=(GLfloat)(uint8_t)(f_text[i]+1)/(GLfloat)font->num_characters;
		vertex_buffer_write++;
		*vertex_buffer_write=1;
		vertex_buffer_write++;
	}

	GLuint *index_buffer_write=index_buffer;

	for(int i=0; i<f_text_sz; i++)
	{
		*index_buffer_write=i*4;
		index_buffer_write++;

		*index_buffer_write=i*4+1;
		index_buffer_write++;

		*index_buffer_write=i*4+2;
		index_buffer_write++;

		*index_buffer_write=i*4+1;
		index_buffer_write++;

		*index_buffer_write=i*4+2;
		index_buffer_write++;

		*index_buffer_write=i*4+3;
		index_buffer_write++;
	}

	struct vec3f location;
	location.x=pos_x*2;
	location.y=pos_y*2;
	location.z=0;

	
	
	text_batch->num_vertices=4*f_text_sz; /*value is four, because this is a quad*/
	text_batch->num_indices=6*f_text_sz;
	
	/*saving OpenGL IDs*/
	glGenVertexArrays(1, &text_batch->arrayID);
	glGenBuffers(1, &text_batch->vertex_bufferID);
	glGenBuffers(1, &text_batch->index_bufferID);
	text_batch->textureID=font->textureID;

	glBindVertexArray(text_batch->arrayID);
	glBindBuffer(GL_ARRAY_BUFFER, text_batch->vertex_bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, text_batch->index_bufferID);
	glBindTexture(GL_TEXTURE_2D, font->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*5*4*f_text_sz, vertex_buffer, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, text_batch->num_indices*sizeof(GLuint), index_buffer, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	/*gfx engine stuff*/
	gfx_update_model_location(text_batch,location);
	
	/*clean up*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	gfx_ui_set_ui_trigger(text_batch);
	return text_batch;
}