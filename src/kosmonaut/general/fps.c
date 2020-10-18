#include <time.h>

#include "general/general.h"
#include "gfx/gfx.h"
#include "maths/maths.h"
#include "gfx/ui/ui.h"
#include "net/net.h"

void engine_fps_count(int toggle_on_screen, int toggle_log)
{
	static clock_t old_time=0;
	static clock_t new_time=0;

	new_time=clock();
	float frame_time_sec=(float)new_time/CLOCKS_PER_SEC-(float)old_time/CLOCKS_PER_SEC;
	old_time=new_time;

	if(toggle_on_screen==ENGINE_TRUE)
	{

		static struct ui_font *font=NULL;
		if(font==NULL)
		{
			font=gfx_ui_load_font("data/textures/bitmapfonts/ConsoleFont.bmp", 256);
		}
		
		static struct model *text=NULL;
		static struct model *text_old=NULL;
		if(text=NULL)
		{
			text=gfx_ui_printf(0, 0, font, 50, "FPS:");
		}

		if(text_old!=NULL)
		{
			gfx_delete_model_entry(text_old);		
		}

		text=gfx_ui_printf(0, 0, font, 60, "FPS: %i", (int)(1/frame_time_sec));
		text_old=text;

	}

	if(toggle_log==ENGINE_TRUE)
	{
		engine_log("FPS: %i\n", (int)(1/frame_time_sec));
	}
}