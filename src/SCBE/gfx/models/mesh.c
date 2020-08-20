#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>

/*the functions loads a model from a .obj file and gives the proper struct model pointer handle to the user*/

/*struct model* gfx_load_model(char *file_location, struct vec3f location)
{
    struct model *model_entry=gfx_create_model_entry();
    
    FILE *model_file=fopen(file_location, "r");
    if(model_file==NULL)
    {
        printf("ERROR: an error occured while reading the file:\n%s\nthe file is probably not valid or the location is wrong\n",file_location);
    }
    
    
    /*getting information on how many vertices are in the file*/
/*    int vertices=0;
    char file_line[1024];
    
    while(fgets(file_line,1024, model_file)!=NULL)
    {
        /*counting vertices*/
/*        if(file_line[0]=='v' && file_line[1]!='t' && file_line[1]!='n')
        {
            vertices++;
        }
    }
    printf("Vertices: %i\n", vertices);
    
    /*allocating memory for vertices*/
/*    GLfloat *model_array=malloc(vertices*6*sizeof(GLfloat));
    
    /*reading vertices from file stream*/
/*    fseek(model_file,0,SEEK_SET);
    
    GLfloat *model_write_vertices=model_array;
    
    struct vec3f vertex;
    while(fgets(file_line,1023,model_file)!=NULL)
    {
        if(fscanf(model_file, "v  %f %f %f\n", &vertex.x, &vertex.y, &vertex.z)==3)
        {
            *model_write_vertices++ = (GLfloat)vertex.x;
            *model_write_vertices++ = (GLfloat)vertex.y;
            *model_write_vertices++ = (GLfloat)vertex.z;
        
            for(int i=0; i<3; i++)
            {
                *model_write_vertices++ = 0.9f;
            }
        }
    }
    
    
    /*allocating memory for index list*/
    /*getting number of indices*/
/*    fseek(model_file,0,SEEK_SET);
    
    int indices=0;
    while(fgets(file_line, 1023, model_file)!=NULL)
    {
        if(file_line[0]=='f')
        {
            indices++;
        }
    }
    
    indices=indices*4;
    printf("Indices: %i\n",indices);
    GLuint *model_index_array=malloc(indices*sizeof(GLuint));
    if(model_index_array==NULL)
    {
        printf("ERROR: couldn't allocate memory for model:\n%s\n",file_location);
    }
    GLuint *model_index_write=model_index_array;
    
    
    /*creating index array*/
/*    fseek(model_file,0,SEEK_SET);
    
    GLuint garbage[8];
    GLuint index[4];
    int i=0;
    while(fgets(file_line,1023,model_file)!=NULL)
    {
        if(fscanf(model_file,"f %u/%u/%u %u/%u/%u %u/%u/%u %u/%u/%u\n",
                    &index[0], &garbage[0], &garbage[1],
                    &index[1], &garbage[2], &garbage[3],
                    &index[2], &garbage[4], &garbage[5],
                    &index[3], &garbage[6], &garbage[7])==12)
        {
            i++;
            *model_index_write=(GLuint)index[0]-1;
            printf("i: %i:  i0: %u ",i,*model_index_write);
            model_index_write++;
            *model_index_write=(GLuint)index[1]-1;
            printf("i1: %u ",*model_index_write);
            model_index_write++;
            *model_index_write=(GLuint)index[2]-1;
            printf("i2: %u\n",*model_index_write);
            model_index_write++;
            /**model_index_write=(GLuint)index[3]-1;
            printf("i3: %u\n",*model_index_write);
            model_index_write++;*/
/*        }

        if(fscanf(model_file,"f %u/%u/%u %u/%u/%u %u/%u/%u\n",
                    &index[0], &garbage[0], &garbage[1],
                    &index[1], &garbage[2], &garbage[3],
                    &index[2], &garbage[4], &garbage[5])==9)
        {
            i++;
            *model_index_write=(GLuint)index[0]-1;
            printf("i: %i:  i0: %u ",i,*model_index_write);
            model_index_write++;
            *model_index_write=(GLuint)index[1]-1;
            printf("i1: %u ",*model_index_write);
            model_index_write++;
            *model_index_write=(GLuint)index[2]-1;
            printf("i2: %u\n",*model_index_write);
            model_index_write++;
        }
    }
            
    model_entry->num_vertices=vertices;
    model_entry->num_indices=indices;

    /*saving OpenGL array ID*/
/*    glGenVertexArrays(1, &model_entry->arrayID);

    /*saving OpenGL vertex buffer ID*/
/*    glGenBuffers(1, &model_entry->vertex_bufferID);

    glBindVertexArray(model_entry->arrayID);
    glBindBuffer(GL_ARRAY_BUFFER, model_entry->vertex_bufferID);
    glBufferData(GL_ARRAY_BUFFER,model_entry->num_vertices*sizeof(GLfloat),model_array,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    /*creating index buffer*/
/*    GLuint index_bufferID;
    glGenBuffers(1,&index_bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices*sizeof(GLuint),model_index_array,GL_STATIC_DRAW);
    
    model_entry->index_data=model_index_array;
        model_entry->index_bufferID=index_bufferID;
    
    gfx_update_model_location(model_entry,location);
    
    /*cleaning up*/
/*    free(model_array);
    
    return model_entry;
}*/