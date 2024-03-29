#include "general.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct config config;

int engine_read_config(char *config_file_location)
{
	FILE *config_file=fopen(config_file_location, "r");

	/*setting standard values, if there is no specification in the config file
	or if there is no config file at all*/
	config.resolution_x=800;
	config.resolution_y=600;
	config.wireframe_mode=ENGINE_FALSE;
	config.fullscreen_mode=ENGINE_FALSE;
	config.viewing_distance=1000;
	config.log_file[0]=0;
	config.logging_on=ENGINE_FALSE;
	config.net_host=ENGINE_FALSE;
	config.net_client=ENGINE_FALSE;
	config.net_port=0;

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
		sscanf(file_line, "viewing_distance=%f", &config.viewing_distance);
		sscanf(file_line, "port=%u", &config.net_port);
		
		if(strstr(file_line, "wireframe")!=NULL)
		{
			config.wireframe_mode=ENGINE_TRUE;
		}

		if(strstr(file_line, "fullscreen")!=NULL)
		{
			config.fullscreen_mode=ENGINE_TRUE;
		}

		if(strstr(file_line, "net_host")!=NULL)
		{
			config.net_host=ENGINE_TRUE;
		}

		if(strstr(file_line, "net_client")!=NULL)
		{
			config.net_client=ENGINE_TRUE;
		}
	}
	
	/*if a log file is specified then logging is turned on*/
	if(config.log_file[0]!=0)
	{
		config.logging_on=ENGINE_TRUE;
	}
	engine_log("Screen resolution: %ix%i\n\n", config.resolution_x, config.resolution_y);

	fclose(config_file);
	
	return ENGINE_NO_ERROR;
}

struct config engine_config_state()
{
	return config;
}