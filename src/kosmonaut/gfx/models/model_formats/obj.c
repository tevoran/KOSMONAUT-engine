#include "gfx/gfx.h"
#include "maths/maths.h"
#include "general/general.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <assert.h>

/*helper functions*/
static inline GLuint * obj_write_face3(unsigned int face_indices[4], GLuint *index_pointer)
{
	*index_pointer=face_indices[0]-1;
	index_pointer++;
	*index_pointer=face_indices[1]-1;
	index_pointer++;
	*index_pointer=face_indices[2]-1;
	index_pointer++;
	return index_pointer;
}






int model_load_obj_model(
	char *file_location,
	GLfloat **vertices, 
	GLuint *num_vertices,
	GLuint vertex_elements,
	GLuint **indices, 
	GLuint *num_indices)

{
	FILE *model_file=fopen(file_location, "r");
	if(model_file==NULL)
	{
		return GFX_ERROR;
	}

	engine_log("Reading file: %s\n",file_location);
	engine_log("Warning: A possible error might occur when a single line contains more than 1024 characters\n");
	
	/*counting vertices and indices*/
	*num_vertices=0;
	*num_indices=0;

	unsigned int num_tex_coords=0;

	char file_line[1024];

	char *current_token;
	unsigned int current_vertices=0;
	unsigned int current_indices=0;
	unsigned int face[3]={0,0,0};
	while(fgets(file_line, 1024, model_file)!=NULL)
	{
		/*if a vertex is found*/
		if(strstr(file_line, "v ")!=NULL)
		{
			++*num_vertices;
		}

		/*if a texture coordinate is found*/
		if(strstr(file_line, "vt ")!=NULL)
		{
			++num_tex_coords;
		}

		/* if a face is found*/
		if(strstr(file_line, "f ")!=NULL)
		{
			strtok(file_line, " ");
			current_token=strtok(NULL, " ");

			/*walking through the string to calculate the necessary indices*/
			face[0]=0;
			current_vertices=0;
			while(current_token!=NULL)
			{
				int n = sscanf(current_token, "%u", &face[0]);
				assert(n == 1);
				current_vertices++;
				face[0]=0;

				/*getting new token*/
				current_token=strtok(NULL, " ");
			}

			assert(current_vertices >= 3);
			/*calculating additional indices out of the number of vertices per face*/

			*num_indices += 3*current_vertices-6;
		}
		
	}

	engine_log("Number of vertices: %i\n", *num_vertices);
	engine_log("Number of polygons: %i\n", *num_indices/3);

	/*creating a texture coordinates array for using the indices in the .obj file*/
	float *tex_coords_array=malloc(num_tex_coords*sizeof(float)*2);
	float *tex_coords_write=tex_coords_array;

	float u=0, v=0;
	fseek(model_file, 0, SEEK_SET);
	while(fgets(file_line, 1024, model_file)!=NULL)
	{
		if(sscanf(file_line, "vt%*[ ]%f %f", &u, &v) == 2)
		{
			*tex_coords_write=u;
			tex_coords_write++;
			*tex_coords_write=v;
			tex_coords_write++;
		}
	}

	/*creating a vertex array for using the indices in the .obj file*/
	float *vertex_array=malloc(*num_vertices*sizeof(float)*3);
	float *vertex_array_write=vertex_array;

	struct vec3f vertex;
	fseek(model_file, 0, SEEK_SET);
	while(fgets(file_line, 1024, model_file)!=NULL)
	{
		if(sscanf(file_line, "v%*[ ]%f %f %f", &vertex.x, &vertex.y, &vertex.z) == 3)
		{
			*vertex_array_write=vertex.x;
			vertex_array_write++;
			*vertex_array_write=vertex.y;
			vertex_array_write++;
			*vertex_array_write=vertex.z;
			vertex_array_write++;
		}
	}

	/*allocating memory for vertices and indices*/
	*vertices=malloc((*num_vertices)*vertex_elements*sizeof(GLfloat));
	GLfloat *vertices_write=*vertices;

	*indices=malloc((*num_indices)*sizeof(GLuint));
	GLuint *indices_write=*indices;

	
	/*writing vertices from file to memory in an OpenGL conform manner*/
	fseek(model_file, 0, SEEK_SET);
	float *vertex_array_read=vertex_array;
	float *tex_coords_read=tex_coords_array;

	face[0]=0;
	face[1]=0;
	face[2]=0;
	while(fgets(file_line, 1024, model_file)!=NULL)
	{
		if(strstr(file_line, "f ")!=NULL)
		{
			strtok(file_line, " ");
			current_token=strtok(NULL, " ");
			while(current_token!=NULL)
			{
				switch(sscanf(current_token, "%d/%d/%d", &face[0], &face[1], &face[2]))
				{
					/*writing vertices without a known texture*/
					case 1:
						vertex_array_read=vertex_array+(3*(face[0]-1));
						vertices_write=(*vertices+(vertex_elements*(face[0]-1)));

						*vertices_write=*vertex_array_read;
						vertices_write++;
						vertex_array_read++;

						*vertices_write=*vertex_array_read;
						vertices_write++;
						vertex_array_read++;

						*vertices_write=*vertex_array_read;
						vertices_write++;
						vertex_array_read++;		
					break;


					/*writing vertices with a knon texture*/
					case 3:
						vertex_array_read=vertex_array+(3*(face[0]-1));
						vertices_write=(*vertices+(vertex_elements*(face[0]-1)));

						*vertices_write=*vertex_array_read;
						vertices_write++;
						vertex_array_read++;

						*vertices_write=*vertex_array_read;
						vertices_write++;
						vertex_array_read++;

						*vertices_write=*vertex_array_read;
						vertices_write++;
						vertex_array_read++;

						tex_coords_read=tex_coords_array+(2*(face[1]-1));

						*vertices_write=*tex_coords_read;
						vertices_write++;
						tex_coords_read++;

						*vertices_write=*tex_coords_read;
						vertices_write++;
						tex_coords_read++;
					break;
				}

				current_token=strtok(NULL, " ");
			}
		}
	}

	
	/*writing indices from file to memory in an OpenGL conform manner*/
	fseek(model_file, 0, SEEK_SET);

	
	face[0]=0;
	face[1]=0;
	face[2]=0;
	while(fgets(file_line, 1024, model_file)!=NULL)
	{

		/* if a face is found*/
		if(strstr(file_line, "f ")!=NULL)
		{
			
			strtok(file_line, " ");
			current_token=strtok(NULL, " ");

			face[0] = face[1] = face[2] = 0;
			/*getting first vertex for the face*/
			for(int i = 0; i < 2; i++)
			{
				int n = sscanf(current_token, "%u", &face[i]);
				assert(n == 1);
				current_token=strtok(NULL, " ");
				assert(current_token);
			}

			/*looping through the rest of the face for all the other polygons*/
			while(current_token != NULL)
			{
				int n = sscanf(current_token, "%u", &face[2]);
				assert(n == 1);
				indices_write=obj_write_face3(face, indices_write);
				current_token=strtok(NULL, " ");
				face[1] = face[2];
			}
		}
	}
	fclose(model_file);
	
	return GFX_NO_ERROR;
}
