#ifndef GFX_H
#define GFX_H

#include "maths/maths.h"
#include <GL/glew.h>
#include <inttypes.h>

/*constants*/
#define PI 3.141593
#define INVALID_HANDLE 0xFFFFFFFF

/*global variables*/
GLuint shader_program; /*the shader program reference*/

/*config variables*/
GLfloat world2opengl_factor; /*the convertion factor between the engine internal world space to opengl handled space*/
float fov;/*the field of view in radians*/

/*camera variables*/
struct vec3f cam_position;
struct vec2f cam_direction;


/*initialising functions*/
int gfx_init();
GLuint gfx_loading_shaders(); /*loads, compiles and links vertex and fragment shaders into one program. its handle is returned as GLuint*/

/*new frame (also clearing screen command)*/
void gfx_new_frame(); /*draws the current frame and clears the buffer for the next frame*/


/*internal config functions*/
    /*world space to normalized device space factor
     * world/nds=factor
     */
    void gfx_set_ws2nds_factor(float factor);
    float gfx_get_ws2nds_factor();
    
    /*camera options*/
    /*field of view angle*/
    void gfx_set_fov(float fov_in); /*field of view is radians*/
    float gfx_get_fov(); /*field of view is in radians*/

/*camera*/
void gfx_create_camera(struct vec3f position, struct vec2f view_direction, float far_z);
void gfx_camera_location(struct vec3f position);
void gfx_set_camera_rotation(struct vec2f view_direction);

/*models*/
uint32_t gfx_create_handle();
/*primitives*/
uint32_t gfx_create_triangle(struct vec3f vertex1, struct vec3f vertex2, struct vec3f vertex3, struct vec3f color); /*returns a uint32_t handle*/

#endif