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


struct model *initial_entry=NULL;
struct model *current_entry=NULL;
struct model *selected_entry=NULL;


struct model* gfx_create_model_entry()
{
    /*create a new entry if no entry exists yet*/
    if(initial_entry==NULL)
    {
        initial_entry=malloc(sizeof(struct model));
            /*if an error occured then show a message*/
            if(initial_entry==NULL)
            {
                printf("ERROR: couldn't allocate memory for a model handling table entry\n");
            }
            
        /*initializing data*/
        initial_entry->last_entry=NULL;
        initial_entry->next_entry=NULL;
        initial_entry->index_bufferID=0;
        
        /*create identity rotation matrix*/
        for(int iy=0; iy<4; iy++)
        {
            for(int ix=0; ix<4; ix++)
            {
                if(ix==iy)
                {
                    initial_entry->rotation_matrix[ix][iy]=1;
                }
                else
                {
                    initial_entry->rotation_matrix[ix][iy]=0;
                }
            }
        }

        return initial_entry;
    }

    current_entry=initial_entry;
    
    /*looking for the last entry*/
    while(current_entry->next_entry!=NULL)
    {
        current_entry=current_entry->next_entry;
    }
    
    
    /*creating a new entry*/
    current_entry->next_entry=malloc(sizeof(struct model));
    if(current_entry->next_entry==NULL)
    {
        printf("ERROR: couldn't allocate memory for a new model handling table entry\n");
    }
    
    void* last_entry=current_entry;
    
    /*initializing data*/
    current_entry=current_entry->next_entry;
    /*marking it as the last entry*/
    current_entry->next_entry=NULL; 
    current_entry->last_entry=last_entry;
    current_entry->index_bufferID=0;
    
    /*create identity rotation matrix*/
    for(int iy=0; iy<4; iy++)
    {
        for(int ix=0; ix<4; ix++)
        {
            if(ix==iy)
            {
                current_entry->rotation_matrix[ix][iy]=1;
            }
            else
            {
                current_entry->rotation_matrix[ix][iy]=0;
            }
        }
    }
    
    return current_entry;
}

int gfx_select_entry(struct model* entry_address)
{
    selected_entry=entry_address;
    if(selected_entry->next_entry==NULL)
    {
        return EOT;
    }
    return TABLE_OK;
}

struct model* gfx_select_first_entry()
{
    selected_entry=initial_entry;
    return selected_entry;
}

struct model* gfx_next_entry()
{
    if(selected_entry->next_entry==NULL)
    {
        return EOT;
    }
    selected_entry=selected_entry->next_entry;
    return selected_entry;
}

void gfx_delete_model_entry(struct model* entry_address)
{
    current_entry=entry_address;
    struct model *previous_entry;
    struct model *next_entry;
    
    /*if this is the only entry*/
    if(current_entry->last_entry==NULL && current_entry->next_entry==NULL)
    {
        initial_entry=NULL;
        free(current_entry);
        return;
    }
    
    /*if this is simply the first entry*/
    if(current_entry->last_entry==NULL && current_entry->next_entry!=NULL)
    {
        initial_entry=current_entry->next_entry;
        current_entry=current_entry->next_entry;
        free(current_entry->last_entry);
        current_entry->last_entry=NULL;
        return;
    }
    
    /*if this is an entry in the middle*/
    if(current_entry->last_entry!=NULL && current_entry->next_entry!=NULL)
    {
        previous_entry=current_entry->last_entry;
        previous_entry->next_entry=current_entry->next_entry;
        
        next_entry=current_entry->next_entry;
        next_entry->last_entry=current_entry->last_entry;
        
        free(current_entry);
        return;
    }
    
    /*if this is the last entry in the list*/
    if(current_entry->last_entry!=NULL && current_entry->next_entry==NULL)
    {
        previous_entry=current_entry->last_entry;
        previous_entry->next_entry=NULL;
        free(current_entry);
        return;
    }
}
