#include "gfx/gfx.h"
#include "maths/maths.h"
#include <math.h>

#include <GL/glew.h>


void gfx_update_model_location(struct model* model, struct vec3f location)
{
	/*calculating world transform matrix*/
	GLfloat world_matrix[4][4]=
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		location.x, location.y, location.z, 1
	};
	
	/*saving the translation matrix in the model struct for the new_frame command
	 * to put it into the shader*/
	for(int ix=0,iy=0; iy<4; ix++)
	{
		model->world_transform_matrix[ix][iy]=world_matrix[ix][iy];
		if(ix==3)
		{
			ix=-1;
			iy++;
		}
	}
}

void gfx_model_rotate(struct model *model, float rotation, struct vec3f rot_axis)
{
	/*calculating quaternions*/
	struct vec4f q;
		q.x=rot_axis.x*sin(rotation/2);
		q.y=rot_axis.y*sin(rotation/2);
		q.z=rot_axis.z*sin(rotation/2);
		q.w=cos(rotation/2);

	q=normalize4f(q);
	
	GLfloat current_rotation_matrix[4][4]=
	{
		1-2*(q.y*q.y+q.z*q.z), 2*(q.x*q.y+q.z*q.w), 2*(q.x*q.z-q.y*q.w), 0,
		2*(q.x*q.y-q.w*q.z), 1-2*(q.x*q.x+q.z*q.z), 2*(q.y*q.z+q.x*q.w), 0,
		2*(q.x*q.z+q.y*q.w), 2*(q.y*q.z-q.x*q.w), 1-2*(q.x*q.x+q.y*q.y), 0,
		0, 0, 0, 1
	};
	
	float new_rotation_matrix[4][4];
	
	/*calculating the new rotation matrix that is sent to the shader*/
	matrix_multiplication4x4(current_rotation_matrix, model->rotation_matrix, new_rotation_matrix);

	
	/*saving the rotation matrix in the model struct for the new_frame command
	 * to put it into the shader*/
	for(int ix=0,iy=0; iy<4; ix++)
	{
		model->rotation_matrix[ix][iy]=new_rotation_matrix[ix][iy];
		if(ix==3)
		{
			ix=-1;
			iy++;
		}
	}
}

void gfx_model_scale(struct model *model, struct vec3f scaling_values)
{
	model->scaling_matrix[0][0]=scaling_values.x;
	model->scaling_matrix[1][1]=scaling_values.y;
	model->scaling_matrix[2][2]=scaling_values.z;
}