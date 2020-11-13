#ifndef KOSMONAUT_GFX_H
#define KOSMONAUT_GFX_H

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

	/*usage members*/
	GLuint visible;
	GLuint ui_element;
};

/*initialising functions*/
int gfx_init();
GLuint gfx_loading_shaders(); /*loads, compiles and links vertex and fragment shaders into one program. its handle is returned as GLuint*/
	GLuint gfx_return_shader(); /*returns global shader ID*/

/*new frame (also clearing screen command)*/
void gfx_new_frame(); /*draws the current frame and clears the buffer for the next frame*/


/*camera*/
void gfx_create_camera(struct vec3f position, float fov);
void gfx_camera_location(struct vec3f position);
void gfx_camera_rotate(float rotation, struct vec3f rot_axis);
void gfx_camera_look_at(struct vec3f position, struct vec3f up);

void gfx_camera_get_shader_matrix(float shader_matrix[4][4]);
struct vec3f gfx_camera_get_location();

/*models*/
/*management*/
struct model* gfx_create_model_entry();
int gfx_select_entry(struct model* entry_address);
struct model* gfx_select_first_entry();
struct model* gfx_next_entry();
void gfx_delete_model_entry(struct model* entry_address);
struct model* gfx_copy_model(struct model* entry_address);
void gfx_model_list_cleanup(); /*destroys all entries in the model list*/

/*transformation*/
void gfx_update_model_location(struct model* model, struct vec3f location);
void gfx_model_rotate_euler(struct model *model, float rotation, char axis);
void gfx_model_rotate(struct model* model, float rotation, struct vec3f rot_axis);
void gfx_model_scale(struct model *model, struct vec3f scaling_values);
struct vec3f gfx_model_vector_rotate(struct model *model, struct vec3f rotated_vector);

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

/*texture related functions*/
void gfx_model_load_texture(char *file_location, struct model *model);

/*speacial gfx*/
void gfx_create_skybox(
	char *file_location_front,
	char *file_location_right, 
	char *file_location_back, 
	char *file_location_left, 
	char *file_location_top, 
	char *file_location_bottom);

	void gfx_update_skybox_location();

#endif