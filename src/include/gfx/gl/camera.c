#include "gfx/gfx.h"

#include "maths/maths.h"

extern GLuint shader_program; /*the shader program reference*/

extern struct vec3f cam_position;
extern struct vec2f cam_direction; /*each axis's offset is in radians*/

void gfx_create_camera(struct vec3f position, struct vec2f view_direction, float far_z)
{
    cam_position=position;
    cam_direction=view_direction;
    
    /*writing to the shader*/
    GLint cam_position_reference=glGetUniformLocation(shader_program, "cam_location");
    glUniform3f(cam_position_reference,(GLfloat)cam_position.x,(GLfloat)cam_position.y,(GLfloat)cam_position.z);
    
    GLint cam_direction_reference=glGetUniformLocation(shader_program, "cam_direction");
    glUniform2f(cam_direction_reference,(GLfloat)view_direction.x,(GLfloat)view_direction.y);
    
    GLint far_z_reference=glGetUniformLocation(shader_program, "far_z");
    glUniform1f(far_z_reference,(GLfloat)(far_z*gfx_get_ws2nds_factor()));
}

void gfx_camera_location(struct vec3f position)
{
    cam_position=position;
    GLint cam_position_reference=glGetUniformLocation(shader_program, "cam_location");
    glUniform3f(cam_position_reference,(GLfloat)cam_position.x,(GLfloat)cam_position.y,(GLfloat)cam_position.z);
}

void gfx_set_camera_rotation(struct vec2f view_direction)
{
    cam_direction=view_direction;
    GLint cam_direction_reference=glGetUniformLocation(shader_program, "cam_direction");
    glUniform2f(cam_direction_reference,(GLfloat)view_direction.x,(GLfloat)view_direction.y);
}