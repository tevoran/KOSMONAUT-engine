#include "gfx/gfx.h"
#include "maths/maths.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>


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

	char file_line[256];

	unsigned int face[4]={0,0,0,0};

	while(fgets(file_line, 256, model_file)!=NULL)
	{
		if(strstr(file_line, "v ")!=NULL)
		{
			*num_vertices=*num_vertices+1;
		}

		/*format "f v1 v2 v3 v4"*/
		switch(sscanf(file_line, "f%*[ ]%u%*[ ]%u%*[ ]%u%*[ ]%u", &face[0], &face[1], &face[2], &face[3]))
		{
			case 3:
				*num_indices=*num_indices+3;
				break;

			case 4:
				*num_indices=*num_indices+6; 
				break;
		}

		/*format "f v1/vt1 v2/vt2 v3/vt3 v4/vt4"*/
		switch(sscanf(file_line, "f%*[ ]%u/%*u%*[ ]%u/%*u%*[ ]%u/%*u%*[ ]%u/%*u", &face[0], &face[1], &face[2], &face[3]))
		{
			case 3:
				*num_indices=*num_indices+3;
				break;

			case 4:
				*num_indices=*num_indices+6; 
				break;
		}

		/*format "f v1//n1 v2//n2 v3//n3 v4//n4"*/
		switch(sscanf(file_line, "f%*[ ]%u//%*u%*[ ]%u//%*u%*[ ]%u//%*u%*[ ]%u//%*u", &face[0], &face[1], &face[2], &face[3]))
		{
			case 3:
				*num_indices=*num_indices+3;
				break;

			case 4:
				*num_indices=*num_indices+6; 
				break;
		}

		/*format "f v1/vt1/n1 v2/vt2/n2 v3/vt3/n3 v4/vt4/n4"*/
		switch(sscanf(file_line, "f%*[ ]%u/%*u/%*u%*[ ]%u/%*u/%*u%*[ ]%u/%*u/%*u%*[ ]%u/%*u/%*u", &face[0], &face[1], &face[2], &face[3]))
		{
			case 3:
				*num_indices=*num_indices+3;
				break;

			case 4:
				*num_indices=*num_indices+6; 
				break;
		}

	}
	printf("vertices: %i\nindices: %i\n", *num_vertices, *num_indices);

	/*allocating memory for vertices and indices*/
	*vertices=malloc((*num_vertices)*vertex_elements*sizeof(GLfloat));
	GLfloat *vertices_write=*vertices;
	
	*indices=malloc((*num_indices)*sizeof(GLuint));
	GLuint *indices_write=*indices;
	
	/*writing vertices from file to memory in an OpenGL conform manner*/
	fseek(model_file, 0, SEEK_SET);

	struct vec3f vertex;
	
	while(fgets(file_line, 256, model_file)!=NULL)
	{
		if(strstr(file_line, "v ")!=NULL)
		{
			sscanf(
				file_line,
				"v%*[ ]%f %f %f\n",
				&vertex.x,
				&vertex.y,
				&vertex.z);
				
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
	
	while(fgets(file_line, 256, model_file)!=NULL)
	{
		if(strstr(file_line, "f ")!=NULL)
		{

			/*format "f v1 v2 v3 v4"*/
			switch(sscanf(file_line, "f%*[ ]%u%*[ ]%u%*[ ]%u%*[ ]%u", &face[0], &face[1], &face[2], &face[3]))
			{
				case 3:
					indices_write=obj_write_face3(face, indices_write);
					break;

				case 4:
					indices_write=obj_write_face4(face, indices_write);
					break;
			}

			/*format "f v1/vt1 v2/vt2 v3/vt3 v4/vt4"*/
			switch(sscanf(file_line, "f%*[ ]%u/%*u%*[ ]%u/%*u%*[ ]%u/%*u%*[ ]%u/%*u", &face[0], &face[1], &face[2], &face[3]))
			{
				case 3:
					indices_write=obj_write_face3(face, indices_write);
					break;

				case 4:
					indices_write=obj_write_face4(face, indices_write);
					break;
			}

			/*format "f v1//n1 v2//n2 v3//n3 v4//n4"*/
			switch(sscanf(file_line, "f%*[ ]%u//%*u%*[ ]%u//%*u%*[ ]%u//%*u%*[ ]%u//%*u", &face[0], &face[1], &face[2], &face[3]))
			{
				case 3:
					indices_write=obj_write_face3(face, indices_write);
					break;

				case 4:
					indices_write=obj_write_face4(face, indices_write);
					break;
			}

			/*format "f v1/vt1/n1 v2/vt2/n2 v3/vt3/n3 v4/vt4/n4"*/
			switch(sscanf(file_line, "f%*[ ]%u/%*u/%*u%*[ ]%u/%*u/%*u%*[ ]%u/%*u/%*u%*[ ]%u/%*u/%*u", &face[0], &face[1], &face[2], &face[3]))
			{
				case 3:
					indices_write=obj_write_face3(face, indices_write);
					break;

				case 4:
					indices_write=obj_write_face4(face, indices_write);
					break;
			}
			/*if(sscanf(
				file_line,
				"f%*[ ]%u/%u/%u %u/%u/%u %u/%u/%u %u/%u/%u\n",
				&index[0], &garbage[0], &poop[0],
				&index[1], &garbage[1], &poop[1],
				&index[2], &garbage[2], &poop[2],
				&index[3], &garbage[3], &poop[3])==12)
				{
					/*decrementing by one for meeting OpenGL requirements*/
			/*		*indices_write=index[0]-1;
					indices_write++;
			
					*indices_write=index[1]-1;
					indices_write++;
			
					*indices_write=index[2]-1;
					indices_write++;
			
					*indices_write=index[2]-1;
					indices_write++;

					*indices_write=index[3]-1;
					indices_write++;
		
					*indices_write=index[0]-1;
					indices_write++;
				}
				
			if(sscanf(
				file_line,
				"f %u//%u %u//%u %u//%u %u//%u\n",
				&index[0], &poop[0],
				&index[1], &poop[1],
				&index[2], &poop[2],
				&index[3], &poop[3])==8)
				{
					/*decrementing by one for meeting OpenGL requirements*/
			/*		*indices_write=index[0]-1;
					indices_write++;
			
					*indices_write=index[1]-1;
					indices_write++;
			
					*indices_write=index[2]-1;
					indices_write++;
			
					*indices_write=index[2]-1;
					indices_write++;

					*indices_write=index[3]-1;
					indices_write++;
		
					*indices_write=index[0]-1;
					indices_write++;
				}
			*/	
			
		}
	}
	
	fclose(model_file);
	
	return GFX_NO_ERROR;
}
