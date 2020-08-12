#include "gfx/gfx.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/* means no object is associated with the handle
 * the first real object gets 0 and the second one gets 1 so forth
 */
 
#define END_OF_HANDLE_TABLE 0xFFFFFFFF /*it is put in the handle part of the handle table*/
#define HANDLE_TABLE_SIZE 100 /*the number of elements contained in one handle table*/
#define HANDLES_TRUE 1
#define HANDLES_FALSE 0

struct table_entry
{
    uint32_t num_vertices;
    void *data_address;
};


struct table_entry *handle_table=NULL; /*the pointer to the first handle table*/
struct table_entry *current_handle_table=NULL; /*the pointer to the current handle table*/

/*
 * helper functions
 * 
 * */
void handles_create_handle_table(struct table_entry *current_handle_table)
{
    for(int i=0; i<HANDLE_TABLE_SIZE; i++)
    {
        if(i<(HANDLE_TABLE_SIZE-1))
        {
            current_handle_table[i].num_vertices=0;
            current_handle_table[i].data_address=NULL;
        }
        else
        {
            current_handle_table[i].num_vertices=END_OF_HANDLE_TABLE;
            current_handle_table[i].data_address=NULL;
        }
    }
}


/*
 * real gfx functions
 * 
 * */
uint32_t gfx_create_handle()
{
    uint32_t handle=0;/*the return value*/
    
    /*checking if initial handle table has been created and if not an empty table will be created*/
    if(handle_table==NULL)
    {
        handle_table=(struct table_entry*)malloc(HANDLE_TABLE_SIZE*sizeof(struct table_entry));
        handles_create_handle_table(handle_table);
    }

    /*checking if new handle table is necessary*/
    current_handle_table=handle_table; /*using the first table as a start point*/
    int free_entry_left=HANDLES_FALSE;
    while(free_entry_left==HANDLES_FALSE)
    {
        /*check for free entries*/
        for(int i=0; i<(HANDLE_TABLE_SIZE-1); i++)
        {
            if(current_handle_table[i].data_address==NULL)
            {
                free_entry_left=HANDLES_TRUE;
                i=HANDLE_TABLE_SIZE; /*end condition for for-loop*/
            }
        }
        
        /*creating new handle table is necessary*/
        if(free_entry_left==HANDLES_FALSE && current_handle_table[HANDLE_TABLE_SIZE-1].data_address==NULL)
            {
                current_handle_table[HANDLE_TABLE_SIZE-1].data_address=(struct table_entry*)malloc(HANDLE_TABLE_SIZE*sizeof(struct table_entry));
                current_handle_table=current_handle_table[HANDLE_TABLE_SIZE-1].data_address;/*switching to new table*/
                handle=handle+HANDLE_TABLE_SIZE;
                handles_create_handle_table(current_handle_table);
                free_entry_left=HANDLES_TRUE;
            }
            
        /*switching to new table if a new table is found*/
        if(free_entry_left==HANDLES_FALSE && current_handle_table[HANDLE_TABLE_SIZE-1].data_address!=NULL)
            {
                current_handle_table=current_handle_table[HANDLE_TABLE_SIZE-1].data_address;
                handle=handle+HANDLE_TABLE_SIZE;
            }
    }
    
    /*looking for empty entry*/
    for(int i=0; i<(HANDLE_TABLE_SIZE); i++)
    {
        if( current_handle_table[i].num_vertices==0 &&
            current_handle_table[i].data_address==NULL)
            {
                current_handle_table[i].data_address=malloc(100);
                return handle=handle+i;
            }
    }
    
    return GFX_ERROR;
}

