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



/*initialising functions*/
int gfx_init();
GLuint gfx_loading_shaders(); /*loads, compiles and links vertex and fragment shaders into one program. its handle is returned as GLuint*/

/*new frame (also clearing screen command)*/
void gfx_new_frame(); /*draws the current frame and clears the buffer for the next frame*/


/*camera*/
void gfx_create_camera(struct vec3f position, struct vec2f view_direction, float far_z, float fov);
void gfx_camera_location(struct vec3f position);


/*models*/
/*management*/
struct entry
{
    /*list related members*/
    void *last_entry;
    void *next_entry;
    
    /*mesh related entry*/
    void *model_data;
    
    /*OpenGL related members*/
    uint32_t num_vertices;
    GLuint arrayID;
    GLuint vertex_bufferID;
};

struct entry* gfx_create_model_entry();
int gfx_select_entry(struct entry* entry_address);
struct entry* gfx_select_first_entry();
struct entry* gfx_next_entry();
void gfx_delete_model_entry(struct entry* entry_address);

/*primitives*/
/*they return a uint32_t handle for identification purposes*/
struct entry* gfx_create_triangle(struct vec3f vertex1, struct vec3f vertex2, struct vec3f vertex3, struct vec3f color);
struct entry* gfx_create_cube(struct vec3f location, struct vec3f color, float size);

#endif