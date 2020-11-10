#include "gfx/ui/ui.h"

#include <GL/glew.h>



struct ui_window *ui_initial_entry=NULL;
struct ui_window *ui_current_entry=NULL;
struct ui_window *ui_selected_entry=NULL;

struct ui_window* gfx_ui_create_window_list_element()
{
	/*first entry*/
	if(ui_initial_entry==NULL)
	{
		ui_initial_entry=malloc(sizeof(struct ui_window));
		ui_initial_entry->next_entry=NULL;
		ui_initial_entry->previous_entry=NULL;

		/*initialize data*/
		gfx_ui_window_list_init_data(ui_initial_entry);

		return ui_initial_entry;
	}

	/*additional entry*/
	/*looking for last entry*/
	ui_current_entry=ui_initial_entry;
	while(ui_current_entry->next_entry!=NULL)
	{
		ui_current_entry=ui_current_entry->next_entry;
	}
	ui_current_entry->next_entry=malloc(sizeof(struct ui_window));
	void *previous_entry=ui_current_entry;
	ui_current_entry=ui_current_entry->next_entry;
	ui_current_entry->next_entry=NULL;
	ui_current_entry->previous_entry=previous_entry;

	/*initialize data*/
	gfx_ui_window_list_init_data(ui_current_entry);

	return ui_current_entry;
}

struct ui_window* gfx_ui_window_select_first_element()
{
	ui_selected_entry=ui_initial_entry;
	return ui_selected_entry;
}

struct ui_window* gfx_ui_window_select_next_element()
{
	if(ui_selected_entry->next_entry!=NULL)
	{
		ui_selected_entry=ui_selected_entry->next_entry;
	}
	else
	{
		return NULL;
	}
	return ui_selected_entry;
}

void gfx_ui_window_remove_window(struct ui_window *window)
{
	/*if there is only one entry*/
	if(window->previous_entry==NULL && window->next_entry==NULL)
	{
		free(window);
		ui_initial_entry=NULL;
	}

	/*the first entry*/
	if(window->previous_entry==NULL && window->next_entry!=NULL)
	{
		ui_initial_entry=window->next_entry;
		ui_initial_entry->previous_entry=NULL;
		free(window);
	}

	/*entry in the middle*/
	if(window->previous_entry!=NULL && window->next_entry!=NULL)
	{
		struct ui_window *last_window=window->previous_entry;
		last_window->next_entry=window->next_entry;
		free(window);
	}

	/*last entry*/
	if(window->previous_entry!=NULL && window->next_entry==NULL)
	{
		struct ui_window *last_window=window->previous_entry;
		last_window->next_entry=NULL;
		free(window);
	}
	return;
}

void gfx_ui_window_list_init_data(struct ui_window *window)
{
	window->subelements=NULL;
	window->pos_x=0;
	window->pos_y=50;
	window->size_x=500;
	window->size_y=100;
	window->scale.x=1;
	window->scale.y=1;
}