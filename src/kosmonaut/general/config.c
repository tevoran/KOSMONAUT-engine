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
	config.wireframe_mode=ENGINE_FALSE;
	config.logging_on=ENGINE_FALSE;

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
		sscanf(file_line, "log=%s", config.log_file);
		
		if(strstr(file_line, "wireframe")!=NULL)
		{
			config.wireframe_mode=ENGINE_TRUE;
		}
	}
	
	/*if a log file is specified then logging is turned on*/
	if(config.log_file!=NULL)
	{
		config.logging_on=ENGINE_TRUE;
	}
	printf("Resolution: %ix%i\n", config.resolution_x, config.resolution_y);

	fclose(config_file);
	
	return ENGINE_NO_ERROR;
}