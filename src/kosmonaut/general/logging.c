#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static FILE *log_file=NULL;


void engine_log(char *logged_text, ...)
{
	struct config config=engine_config_state();
	if(config.logging_on==ENGINE_FALSE)
	{
		return;
	}

	if(log_file==NULL)
	{
		log_file=fopen(config.log_file, "w");		
	}

	va_list args;
	va_start(args, logged_text);
	vfprintf(log_file, logged_text, args);
	va_end(args);
	return;
}