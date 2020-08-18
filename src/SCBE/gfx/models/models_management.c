#include "gfx/gfx.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <GL/glew.h>

/*  the implementation of a doubly linked list to handle the relevant data to different 3d objects
 *  this is crucial for the gfx_new_frame function
 */

#define EOT 0
#define TABLE_ERROR 1
#define TABLE_OK 2


struct entry *initial_entry=NULL;
struct entry *current_entry=NULL;
struct entry *selected_entry=NULL;


struct entry* gfx_create_model_entry()
{
    /*create a new entry if no entry exists yet*/
    if(initial_entry==NULL)
    {
        initial_entry=malloc(sizeof(struct entry));
            /*if an error occured then show a message*/
            if(initial_entry==NULL)
            {
                printf("ERROR: couldn't allocate memory for a model handling table entry\n");
            }
        initial_entry->last_entry=NULL;
        initial_entry->next_entry=NULL;
    }

    current_entry=initial_entry;
    
    /*looking for the last entry*/
    while(current_entry->next_entry!=NULL)
    {
        current_entry=current_entry->next_entry;
    }
    
    
    /*creating a new entry*/
    /*creating a link to the last entry*/
    /*if its not the initial entry*/
    void *last_entry=NULL;
    if(current_entry->last_entry!=NULL)
    {
        last_entry=current_entry;
    }

    current_entry->next_entry=malloc(sizeof(struct entry));
    if(current_entry->next_entry==NULL)
    {
        printf("ERROR: couldn't allocate memory for a new model handling table entry\n");
    }
    
    current_entry=current_entry->next_entry;
    /*marking it as the last entry*/
    current_entry->next_entry=NULL; 
    current_entry->last_entry=last_entry;
    
    return current_entry;
}

int gfx_select_entry(struct entry* entry_address)
{
    selected_entry=entry_address;
    if(selected_entry->next_entry==NULL)
    {
        return EOT;
    }
    return TABLE_OK;
}

struct entry* gfx_select_first_entry()
{
    selected_entry=initial_entry;
    return selected_entry;
}

struct entry* gfx_next_entry()
{
    if(selected_entry->next_entry==NULL)
    {
        return EOT;
    }
    selected_entry=selected_entry->next_entry;
    return selected_entry;
}
