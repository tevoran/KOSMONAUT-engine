#include "gfx/gfx.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <GL/glew.h>


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
    void *data_address; /*is used for marking an entry as used and as a pointer to a new table, if it's the last entry in a table*/
    GLuint arrayID;
    GLuint vertex_bufferID;
};


struct table_entry *handle_table=NULL; /*the pointer to the first handle table*/
struct table_entry *current_handle_table=NULL; /*the pointer to the current handle table*/

uint32_t highest_handle=0;

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

struct table_entry* handles_find_entry(uint32_t handle)
{
    current_handle_table=handle_table;
    for(handle; handle>HANDLE_TABLE_SIZE; handle=handle-HANDLE_TABLE_SIZE)
    {
        current_handle_table=current_handle_table[HANDLE_TABLE_SIZE-1].data_address;
    }
    return &current_handle_table[handle];
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
        if(handle_table==NULL)
        {
            printf("ERROR while allocating memory for initial primitive handle table\n");
            return GFX_ERROR;
        }
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
        
        /*creating new handle table if necessary*/
        if(free_entry_left==HANDLES_FALSE && current_handle_table[HANDLE_TABLE_SIZE-1].data_address==NULL)
            {
                current_handle_table[HANDLE_TABLE_SIZE-1].data_address=(struct table_entry*)malloc(HANDLE_TABLE_SIZE*sizeof(struct table_entry));
                if(current_handle_table[HANDLE_TABLE_SIZE-1].data_address==NULL)
                {
                    printf("error while allocating memory for a new handle table\n");
                    return GFX_ERROR;
                }
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
                current_handle_table[i].data_address=(void*)ENTRY_IS_USED; /*mark entry as used*/
                handle=handle+i;
                if(handle>highest_handle)
                {
                    highest_handle=handle;
                }
                return handle;
            }
    }
    
    return GFX_ERROR;
}

/*checking function if ID is used as a regular entry or if it's a node*/
/*see constants in gfx.h header*/
uint32_t gfx_handle_check(uint32_t handle)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    if(current_entry->data_address==(void*)ENTRY_IS_USED)
    {
        return ENTRY_IS_USED;
    }
    if(current_entry->num_vertices==END_OF_HANDLE_TABLE)
    {
        return ENTRY_IS_A_NODE;
    }
    if(current_entry->num_vertices==0 && current_entry->data_address==NULL)
    {
        return ENTRY_IS_FREE;
    }
    return GFX_ERROR;
}

/*highest handle*/
uint32_t gfx_get_highest_handle()
{
    return highest_handle;
}

/*get and set functions*/
void gfx_set_num_vertices(uint32_t handle, uint32_t num_vertices)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    current_entry->num_vertices=num_vertices;
}

uint32_t gfx_get_num_vertices(uint32_t handle)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    uint32_t num_vertices=current_entry->num_vertices;
    return num_vertices;
}

void gfx_set_arrayID(uint32_t handle,GLuint arrayID)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    current_entry->arrayID=arrayID;
}

GLuint gfx_get_arrayID(uint32_t handle)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    GLuint arrayID=current_entry->arrayID;
    return arrayID;
}

void gfx_set_vertex_bufferID(uint32_t handle,GLuint vertex_bufferID)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    current_entry->vertex_bufferID=vertex_bufferID;
}

GLuint gfx_get_vertex_bufferID(uint32_t handle)
{
    struct table_entry *current_entry=handles_find_entry(handle);
    GLuint vertex_bufferID=current_entry->vertex_bufferID;
    return vertex_bufferID;
}