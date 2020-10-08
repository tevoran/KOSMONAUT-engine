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
#define GFX_NO_ERROR 0
#define GFX_ERROR_NULL 0

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
void gfx_create_camera(struct vec3f position, float far_z, float fov);
void gfx_camera_location(struct vec3f position);
void gfx_camera_rotate(float rotation, struct vec3f rot_axis);

void gfx_camera_get_shader_matrix(float shader_matrix[4][4]);


/*models*/
/*management*/
struct model
{
	/*list related members*/
	void *last_entry;
	void *next_entry;

	
	/*OpenGL related members*/
	uint32_t num_vertices;
	uint32_t num_indices;
	GLuint arrayID;
	GLuint vertex_bufferID;
	GLuint index_bufferID;
	GLvoid *index_data;
	
	/*transformation members*/
	GLfloat world_transform_matrix[4][4];
	GLfloat rotation_matrix[4][4];
	GLfloat scaling_matrix[4][4];

	/*texture members*/
	GLuint textureID;
};

struct model* gfx_create_model_entry();
int gfx_select_entry(struct model* entry_address);
struct model* gfx_select_first_entry();
struct model* gfx_next_entry();
void gfx_delete_model_entry(struct model* entry_address);
struct model* gfx_copy_model(struct model* entry_address);

/*transformation*/
void gfx_update_model_location(struct model* model, struct vec3f location);
void gfx_model_rotate(struct model* model, float rotation, struct vec3f rot_axis);
void gfx_model_scale(struct model *model, struct vec3f scaling_values);

/*primitives*/
/*they return a struct model pointer for identification purposes*/
struct model* gfx_create_triangle(
	struct vec3f location,
	struct vec3f corner1, 
	struct vec3f corner2, 
	struct vec3f color);
struct model* gfx_create_cube(
	struct vec3f location, 
	struct vec3f color, 
	float size);
struct model* gfx_load_model(char *file_location, struct vec3f location);
struct model* gfx_create_quad(
	struct vec3f location, 
	struct vec3f corner1, 
	struct vec3f corner2, 
	struct vec3f color);

/*model load functions*/
int model_load_obj_model(
	char *file_location,
	GLfloat **vertices, 
	GLuint *num_vertices, 
	GLuint vertex_elements,
	GLuint **indices, 
	GLuint *num_indices);
void gfx_model_texture_load_bmp(
	char *file_location, 
	GLfloat **texture_data, 
	GLsizei *texture_height, 
	GLsizei *texture_width);

/*texture related functions*/
void gfx_model_load_texture(char *file_location, struct model *model);

#endif