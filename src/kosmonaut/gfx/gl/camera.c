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

GLfloat projection_matrix[4][4]=
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 1,
	0, 0, 0, 0
};

GLfloat cam_translation_matrix[4][4]=
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

GLfloat cam_matrix_for_shader[4][4]=
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

void gfx_create_camera(struct vec3f position, float fov)
{ 
	/*get current config state*/
	struct config config=engine_config_state();
	float aspect_ratio=(float)config.resolution_x/(float)config.resolution_y;

	/*creating projection matrix and sending it to the vertex shader*/

	projection_matrix[0][0]=tan(0.5*PI-0.5*fov);
	projection_matrix[1][1]=aspect_ratio*tan(0.5*PI-0.5*fov);
	projection_matrix[2][2]=(1-near_z)/(config.viewing_distance-near_z);
	
	
	/*creating the camera translation matrix*/
	cam_translation_matrix[3][0]=-position.x;
	cam_translation_matrix[3][1]=-position.y;
	cam_translation_matrix[3][2]=-position.z;
}



void gfx_camera_location(struct vec3f position)
{
	cam_translation_matrix[3][0]=-position.x;
	cam_translation_matrix[3][1]=-position.y;
	cam_translation_matrix[3][2]=-position.z;
}

struct vec3f gfx_camera_get_location()
{
	struct vec3f location;
	location.x=-cam_translation_matrix[3][0];
	location.y=-cam_translation_matrix[3][1];
	location.z=-cam_translation_matrix[3][2];
	return location;
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
}

void gfx_camera_look_at(struct vec3f position, struct vec3f up)
{
	struct vec3f cam_location=gfx_camera_get_location();
	cam_location=vec3f_scale(-1, cam_location);
	struct vec3f forward=vec3f_add(position, cam_location);
	forward=normalize3f(forward);
	up=normalize3f(up);
	struct vec3f left=cross_product(up, forward);
	left=normalize3f(left);

	/*saving the rotation matrix*/
	cam_rotation_matrix[0][0]=left.x;
	cam_rotation_matrix[1][0]=left.y;
	cam_rotation_matrix[2][0]=left.z;
	cam_rotation_matrix[3][0]=0;

	cam_rotation_matrix[0][1]=up.x;
	cam_rotation_matrix[1][1]=up.y;
	cam_rotation_matrix[2][1]=up.z;
	cam_rotation_matrix[3][1]=0;

	cam_rotation_matrix[0][2]=forward.x;
	cam_rotation_matrix[1][2]=forward.y;
	cam_rotation_matrix[2][2]=forward.z;
	cam_rotation_matrix[3][2]=0;

	cam_rotation_matrix[0][3]=0;
	cam_rotation_matrix[1][3]=0;
	cam_rotation_matrix[2][3]=0;
	cam_rotation_matrix[3][3]=1;
}


/*calculates the the matrix for the shader out of the projection matrix, the camera translation and
its rotation matrix*/
void gfx_camera_get_shader_matrix(float shader_matrix[4][4])
{
	GLfloat interim_result[4][4];
	matrix_multiplication4x4(cam_translation_matrix, cam_rotation_matrix, interim_result);
	matrix_multiplication4x4(interim_result, projection_matrix, cam_matrix_for_shader);

	for(int ix=0,iy=0; iy<4; ix++)
	{
		shader_matrix[ix][iy]=cam_matrix_for_shader[ix][iy];
		if(ix==3)
		{
			ix=-1;
			iy++;
		}
	}
}