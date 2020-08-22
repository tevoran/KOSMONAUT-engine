#include "general.h"

#include <stdio.h>
#include <stdlib.h>

extern struct config config;

int engine_read_config(char *config_file_location)
{
	FILE *config_file=fopen(config_file_location, "r");

	/*setting standard values, if there is no specification in the config file
	or if there is no config file at all*/
	config.resolution_x=800;
	config.resolution_y=600;

	/*if there is no config file then leave*/
	if(config_file==NULL)
	{
		return ENGINE_NO_CONFIG_FILE;
	}
	
	char file_line[256];
	
	/*reading the config file line wise*/

	while(fgets(file_line, 256, config_file)!=NULL)
	{
		/*interpreting config file*/
		sscanf(file_line, "resx=%u", &config.resolution_x);
		sscanf(file_line, "resy=%u", &config.resolution_y);
	}
	
	printf("Resolution: %ix%i\n", config.resolution_x, config.resolution_y);
	return ENGINE_NO_ERROR;
}