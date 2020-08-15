#include "gfx/gfx.h"

#include <GL/glew.h>


extern GLuint shader_program; /*shader program reference*/

/*camera options*/
/*field of view angle*/
extern float fov;

/*to be activated after the function call, the camera has to be created*/
void gfx_set_fov(float fov_in) /*field of view is radians*/
{
    fov=fov_in;
}

float gfx_get_fov() /*field of view is in radians*/
{
    return fov;
}