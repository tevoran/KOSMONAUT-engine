#include "gfx.h"

#include <GL/glew.h>


extern GLuint shader_program; /*shader program reference*/

/*world space to normalized device space factor
  * world/nds=factor
  */
extern GLfloat world2opengl_factor;

void gfx_set_ws2nds_factor(float factor)
{
    world2opengl_factor=(GLfloat)factor;
    GLint world2gl_reference=glGetUniformLocation(shader_program, "world2gl");
    glUniform1f(world2gl_reference,(GLfloat)gfx_get_ws2nds_factor());
}

float gfx_get_ws2nds_factor()
{
    return (float)world2opengl_factor;
}

/*camera options*/
/*field of view angle*/
extern float fov;
void gfx_set_fov(float fov_in) /*field of view is radians*/
{
    fov=fov_in;
    GLint fov_reference=glGetUniformLocation(shader_program, "fov");
    glUniform1f(fov_reference,(GLfloat)fov);
}

float gfx_get_fov() /*field of view is in radians*/
{
    return fov;
}