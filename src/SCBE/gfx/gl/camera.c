#include "gfx/gfx.h"

#include "maths/maths.h"
#include <math.h>
#include <GL/glew.h>

#define near_z 0.1 /*near clipping plane*/

extern GLuint shader_program; /*the shader program reference*/


void gfx_create_camera(struct vec3f position, struct vec2f view_direction, float far_z, float fov)
{ 
    /*creating projection matrix and sending it to the vertex shader*/
    GLfloat projection_matrix[4][4]=
    {
        tan(0.5*PI-0.5*fov), 0, 0, 0,
        0,tan(0.5*PI-0.5*fov), 0, 0,
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
