#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <assert.h>

/*helper functions*/
GLuint * obj_write_face3(unsigned int face_indices[4], GLuint *index_pointer)
{
	*index_pointer=face_indices[0]-1;
	index_pointer++;
	*index_pointer=face_indices[1]-1;
	index_pointer++;
	*index_pointer=face_indices[2]-1;
	index_pointer++;
	return index_pointer;
}

GLuint * obj_write_face4(unsigned int face_indices[4], GLuint *index_pointer)
{
	/*first triangle*/
	*index_pointer=face_indices[0]-1;
	index_pointer++;
	*index_pointer=face_indices[1]-1;
	index_pointer++;
	*index_pointer=face_indices[2]-1;
	index_pointer++;

	/*second triangle*/
	*index_pointer=face_indices[2]-1;
	index_pointer++;
	*index_pointer=face_indices[3]-1;
	index_pointer++;
	*index_pointer=face_indices[0]-1;
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

	
	/*counting vertices and indices*/
	*num_vertices=0;
	*num_indices=0;

	char file_line[1024];

	char *current_token;
	unsigned int current_vertices=0;
	unsigned int current_indices=0;
	unsigned int face[4]={0,0,0,0};
	while(fgets(file_line, 1024, model_file)!=NULL)
	{
		/*if a vertex is found*/
		if(strstr(file_line, "v ")!=NULL)
		{
			++*num_vertices;
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
	printf("vertices: %i\nindices: %i\npolygons: %i\n", *num_vertices, *num_indices, *num_indices/3);

	/*allocating memory for vertices and indices*/
	*vertices=malloc((*num_vertices)*vertex_elements*sizeof(GLfloat));
	GLfloat *vertices_write=*vertices;
	
	*indices=malloc((*num_indices)*sizeof(GLuint));
	GLuint *indices_write=*indices;
	
	/*writing vertices from file to memory in an OpenGL conform manner*/
	fseek(model_file, 0, SEEK_SET);

	struct vec3f vertex;
	
	while(fgets(file_line, 1024, model_file)!=NULL)
	{
		if(strstr(file_line, "v ")!=NULL)
		{
			int n = sscanf(
				file_line,
				"v%*[ ]%f %f %f\n",
				&vertex.x,
				&vertex.y,
				&vertex.z);
			assert(n == 3);
				
			*vertices_write=vertex.x;
			vertices_write++;
			*vertices_write=vertex.y;
			vertices_write++;
			*vertices_write=vertex.z;
			vertices_write++;
			
			/*write color as well*/
			for(int i=0; i<3; i++)
			{
				*vertices_write=0.9f;
				vertices_write++;
			}
		}
	}

	
	/*writing indices from file to memory in an OpenGL conform manner*/
	fseek(model_file, 0, SEEK_SET);
	
	GLuint index[4];
	GLuint garbage[4];
	GLuint poop[4];
	
	face[0]=0;
	face[1]=0;
	face[2]=0;
	face[3]=0;
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
	assert(indices_write - *indices == *num_indices);
	printf("%u, %zu\n", *num_vertices, vertices_write - *vertices);
	assert((vertices_write - *vertices) / 6 == *num_vertices);
	fclose(model_file);
	
	return GFX_NO_ERROR;
}
