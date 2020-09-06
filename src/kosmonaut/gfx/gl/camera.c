#include "gfx/gfx.h"


#include "general/general.h"
#include "maths/maths.h"
#include <math.h>
#include <GL/glew.h>

#define near_z 0.1 /*near clipping plane*/

extern GLuint shader_program; /*the shader program reference*/

/*camera variables*/

GLfloat cam_rotation_matrix[4][4]=
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};



void gfx_create_camera(struct vec3f position, float far_z, float fov)
{ 
	/*get current config state*/
	struct config config=engine_config_state();
	float aspect_ratio=(float)config.resolution_x/(float)config.resolution_y;

	/*creating projection matrix and sending it to the vertex shader*/
	GLfloat projection_matrix[4][4]=
	{
		tan(0.5*PI-0.5*fov), 0, 0, 0,
		0,aspect_ratio*tan(0.5*PI-0.5*fov), 0, 0,
		0, 0, (1-near_z)/(far_z-near_z), 1,
		0, 0, 0, 0
	};
	
	GLint projection_matrix_reference=glGetUniformLocation(shader_program, "projectionMatrix");
	glUniformMatrix4fv(projection_matrix_reference,1,GL_FALSE,&projection_matrix[0][0]);
	
	/*creating the camera translation matrix*/
	GLfloat cam_translation_matrix[4][4]=
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-position.x, -position.y, -position.z, 1
	};
	
	GLint cam_translation_matrix_reference=glGetUniformLocation(shader_program, "cam_translationMatrix");
	glUniformMatrix4fv(cam_translation_matrix_reference,1,GL_FALSE,&cam_translation_matrix[0][0]);

	/*sending an identity matrix as an initial rotatation matrix*/
	GLint cam_rotation_matrix_reference=glGetUniformLocation(shader_program, "camRotationMatrix");
	glUniformMatrix4fv(cam_rotation_matrix_reference, 1, GL_FALSE, &cam_rotation_matrix[0][0]);
}



void gfx_camera_location(struct vec3f position)
{
	GLfloat cam_translation_matrix[4][4]=
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-position.x, -position.y, -position.z, 1
	};
	
	GLint cam_translation_matrix_reference=glGetUniformLocation(shader_program, "cam_translationMatrix");
	glUniformMatrix4fv(cam_translation_matrix_reference,1,GL_FALSE,&cam_translation_matrix[0][0]);
}



void gfx_camera_rotate(float rotation, struct vec3f rot_axis)
{
	/*reversing camera rotation, as the world has to be moved, instead of the camera*/
	rotation=-rotation;

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

	GLfloat new_rotation_matrix[4][4];
	
	/*calculating the new rotation matrix that is sent to the shader*/
	matrix_multiplication4x4(current_rotation_matrix, cam_rotation_matrix, new_rotation_matrix);

	/*saving the rotation matrix*/
	for(int ix=0,iy=0; iy<4; ix++)
	{
		cam_rotation_matrix[ix][iy]=new_rotation_matrix[ix][iy];
		if(ix==3)
		{
			ix=-1;
			iy++;
		}
	}

	GLint cam_rotation_matrix_reference=glGetUniformLocation(shader_program, "camRotationMatrix");
	glUniformMatrix4fv(cam_rotation_matrix_reference, 1, GL_FALSE, &cam_rotation_matrix[0][0]);
}