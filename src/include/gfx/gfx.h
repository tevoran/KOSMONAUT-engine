#ifndef GFX_H
#define GFX_H

#include "maths/maths.h"
#include <GL/glew.h>
#include <inttypes.h>

/*constants*/
#define PI 3.141593
#define GFX_TRUE 1
#define GFX_FALSE 0
#define GFX_ERROR 0xFFFFFFFF

/*constants for handle handling*/
#define ENTRY_IS_A_NODE 0xFFFFFFFE
#define ENTRY_IS_USED 0xFFFFFFFD
#define ENTRY_IS_FREE 0xFFFFFFFC

/*global variables*/
GLuint shader_program; /*the shader program reference*/

/*config variables*/
float fov;/*the field of view in radians*/

/*camera variables*/
struct vec2f cam_direction;


/*initialising functions*/
int gfx_init();
GLuint gfx_loading_shaders(); /*loads, compiles and links vertex and fragment shaders into one program. its handle is returned as GLuint*/

/*new frame (also clearing screen command)*/
void gfx_new_frame(); /*draws the current frame and clears the buffer for the next frame*/


/*internal config functions*/    
    /*camera options*/
    /*field of view angle*/
    void gfx_set_fov(float fov_in); /*field of view is radians*/
    float gfx_get_fov(); /*field of view is in radians*/

/*camera*/
void gfx_create_camera(struct vec3f position, struct vec2f view_direction, float far_z);
void gfx_camera_location(struct vec3f position);
void gfx_set_camera_rotation(struct vec2f view_direction);

/*models*/
/*handles*/
uint32_t gfx_create_handle();

uint32_t gfx_handle_check(uint32_t handle);

void gfx_set_num_vertices(uint32_t handle, uint32_t num_vertices);
uint32_t gfx_get_num_vertices(uint32_t handle);

void gfx_set_arrayID(uint32_t handle,GLuint arrayID);
GLuint gfx_get_arrayID(uint32_t handle);

void gfx_set_vertex_bufferID(uint32_t handle,GLuint vertex_bufferID);
GLuint gfx_get_vertex_bufferID(uint32_t handle);

uint32_t gfx_get_highest_handle();

/*primitives*/
uint32_t gfx_create_triangle(struct vec3f vertex1, struct vec3f vertex2, struct vec3f vertex3, struct vec3f color); /*returns a uint32_t handle*/

#endif