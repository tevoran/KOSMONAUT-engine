#include "gfx/gfx.h"
#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void gfx_model_texture_load_bmp(
	char *file_location, 
	GLfloat **texture_data, 
	GLsizei *texture_height, 
	GLsizei *texture_width)
{
	FILE *texture_file=fopen(file_location, "rb");
	if(texture_file==NULL)
	{
		engine_log("Texture file at: %s couldn't be read\n", file_location);
		return;
	}
	

	uint32_t data_offset=0;
	/*reading .bmp file header*/
	/*finding offset to data*/
	fseek(texture_file, 0x0A, SEEK_SET);
	fread(&data_offset, sizeof(uint32_t), 1, texture_file);

	/*getting resolution of bmp file*/
	/*width*/
	int32_t read_val=0;
	fseek(texture_file, 0x12, SEEK_SET);
	fread(&read_val, sizeof(int32_t), 1, texture_file);
	*texture_width=(GLsizei)read_val;
	/*height*/
	fseek(texture_file, 0x16, SEEK_SET);
	fread(&read_val, sizeof(int32_t), 1, texture_file);
	*texture_height=(GLsizei)read_val;

	/*checking for compression*/
	fseek(texture_file, 0x1E, SEEK_SET);
	fread(&read_val, sizeof(int32_t), 1, texture_file);
	if(read_val!=0)
	{
		engine_log("Texture file at %s is compressed.\nKosmonaut doesn't support compression for .bmp files\n", file_location);
		return;
	}

	/*checking for color depth*/
	uint16_t color_depth=0;
	fseek(texture_file, 0x1C, SEEK_SET);
	fread(&color_depth, sizeof(uint16_t), 1, texture_file);
	if(color_depth!=24)
	{
		engine_log("Texture file at %s has an unsupported color depth. Only 24bits is supported.\n", file_location);
		return;
	}

	/*reading actual image data*/
	uint32_t pixel_count=(*texture_height)*(*texture_width);
	*texture_data=malloc(pixel_count*3*sizeof(GLfloat));
	
	GLfloat *texture_data_write=*texture_data;
	unsigned char bgr[3];
	GLfloat rgb[3];

	for(int i=0; i<pixel_count; i++)
	{
		fseek(texture_file, data_offset+(i*3), SEEK_SET);
		fread(bgr, sizeof(bgr), 1, texture_file);
		rgb[0]=(GLfloat)bgr[2]/256;
		rgb[1]=(GLfloat)bgr[1]/256;
		rgb[2]=(GLfloat)bgr[0]/256;
		*texture_data_write=rgb[0];
		texture_data_write++;
		*texture_data_write=rgb[1];
		texture_data_write++;
		*texture_data_write=rgb[2];
		texture_data_write++;

	}

	fclose(texture_file);

}