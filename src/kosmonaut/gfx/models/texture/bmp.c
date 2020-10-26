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

	/*checking for order of image data*/
	int32_t data_order=0;
	fseek(texture_file, 0x16, SEEK_SET);
	fread(&data_order, sizeof(uint32_t), 1, texture_file);

	/*reading actual image data*/
	uint32_t pixel_count=(*texture_height)*(*texture_width);
	*texture_data=malloc(pixel_count*3*sizeof(GLfloat));
	void *texture_data_read_file=malloc(pixel_count*3*sizeof(char));


	GLfloat *texture_data_write=*texture_data;

	unsigned char *bgr;
	GLfloat rgb[3];

	fseek(texture_file, data_offset, SEEK_SET);
	fread(texture_data_read_file, pixel_count*3*sizeof(char), 1, texture_file);

	if(data_order>0)
	{
		for(int i=0; i<pixel_count; i++)
		{
			bgr=(char*)(texture_data_read_file+i*3);
			rgb[0]=(GLfloat)*(bgr+2)/256;
			rgb[1]=(GLfloat)*(bgr+1)/256;
			rgb[2]=(GLfloat)*(bgr)/256;
			*texture_data_write=rgb[0];
			texture_data_write++;
			*texture_data_write=rgb[1];
			texture_data_write++;
			*texture_data_write=rgb[2];
			texture_data_write++;
		}
	}

	else if(data_order<0)
	{
		for(int i=pixel_count; i>0; i--)
		{
			bgr=(char*)(texture_data_read_file+i*3);
			rgb[0]=(GLfloat)*(bgr+2)/256;
			rgb[1]=(GLfloat)*(bgr+1)/256;
			rgb[2]=(GLfloat)*(bgr)/256;
			*texture_data_write=rgb[0];
			texture_data_write++;
			*texture_data_write=rgb[1];
			texture_data_write++;
			*texture_data_write=rgb[2];
			texture_data_write++;
		}
	}

	else
	{
		engine_log("Texture file at %s is neither a top-down nor a bottom-up bitmap.\n", file_location);
		return;
	}

	/*logging debug info*/
	engine_log("\nTexture file %s was read.\n", file_location);
	engine_log("Resolution: %ix%i\n", *texture_width, *texture_height);
	engine_log("Image data size: %i bytes\n", ((*texture_height)*(*texture_width)*3));
	if(data_order>0)
		{
			engine_log("Bottom-Up bitmap file\n\n");
		}
	if(data_order<0)
		{
			engine_log("Top-Down bitmap file\n\n");
		}

	fclose(texture_file);

}