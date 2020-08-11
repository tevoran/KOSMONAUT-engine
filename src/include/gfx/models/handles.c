#include "gfx/gfx.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


/*NULL means no object is associated with the handle
 * the first real object gets 1 and so forth
 * but after deleting objects the new handle numbers can become a bit more messy
 */
 
#define END_OF_HANDLE_TABLE 0xFFFFFFFF /*it is put in the handle part of the handle table*/
#define HANDLE_TABLE_SIZE 100 /*the number of elements contained in one handle table*/

struct table_entry
{
    uint32_t handle;
    uint32_t num_vertices;
    void *data_address;
};

struct table_entry *handle_table=NULL; /*the pointer to the first handle table*/
struct table_entry *current_handle_table=NULL; /*the pointer to the current handle table*/

uint32_t current_lowest_handle;
uint32_t current_highest_handle;

uint32_t gfx_create_handle()
{
    uint32_t handle;/*the return value*/
    
    /*checking if initial handle table has been created and if not an empty table will be created*/
    if(handle_table==NULL)
    {
        handle_table=(struct table_entry*)malloc(HANDLE_TABLE_SIZE*sizeof(struct table_entry));
        
        for(int i=0; i<HANDLE_TABLE_SIZE; i++)
        {
            if(i<(HANDLE_TABLE_SIZE-1))
            {
                handle_table[i].handle=0;
                handle_table[i].num_vertices=0;
                handle_table[i].data_address=NULL;
            }
            else
            {
                handle_table[i].handle=END_OF_HANDLE_TABLE;
                handle_table[i].num_vertices=0;
                handle_table[i].data_address=(void*)END_OF_HANDLE_TABLE;
            }
        }
    }
    
    /*checking if new handle table is necessary*/
    /*current_handle_table=handle_table;
    while(current_handle_table[HANDLE_TABLE_SIZE-1].data_address==(void*)END_OF_HANDLE_TABLE)
    {
        printf("last table\n");
        if(current_handle_table[HANDLE_TABLE_SIZE-2].handle!=0 && current_handle_table[HANDLE_TABLE_SIZE-1].handle==END_OF_HANDLE_TABLE)
        {
            
        }
    }
    if(current_handle_table[HANDLE_TABLE_SIZE-2].handle!=0 && current_handle_table[HANDLE_TABLE_SIZE-1].handle==END_OF_HANDLE_TABLE)
        {
        }
         */
    
    /*creating handle*/
    current_lowest_handle=0;
    current_highest_handle=0;
    register uint32_t current_handle;
    
    /*looking for lowest free handle*/
    /*current_handle_table=handle_table;
    for(int i=0; i<HANDLE_TABLE_SIZE; i++)
    {
        
    }*/
    
    /*looking for first free entry in the first table*/
    current_handle_table=handle_table;
    for(int i=0; i<HANDLE_TABLE_SIZE; i++)
    {
        current_handle=current_handle_table[i].handle;
        if(current_handle==0)
        {
            current_highest_handle++;
            current_handle_table[i].handle=current_highest_handle;
            handle=current_highest_handle;
            return handle;
        }
        else
        {
            if(current_handle_table[i].handle>current_highest_handle)
            {
                current_highest_handle=current_handle_table[i].handle;
            }
        }
    }
    
    return handle;
}