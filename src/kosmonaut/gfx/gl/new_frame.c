#include "gfx/gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "general/general.h"

extern GLuint shader_program;

void gfx_new_frame()
{
	/*calculating a single matrix for projection, camera rotation and location*/
	GLfloat cam_shader_matrix[4][4];
	gfx_camera_get_shader_matrix(cam_shader_matrix);
	GLint cam_shader_matrix_reference=glGetUniformLocation(shader_program, "camShaderMatrix");
	glUniformMatrix4fv(cam_shader_matrix_reference,1,GL_FALSE,&cam_shader_matrix[0][0]);


	/*drawing all models*/
	struct model* model_list_entry=gfx_select_first_entry();
	


	GLint world_transform_matrix_reference=glGetUniformLocation(shader_program, "world_transformMatrix");
	GLint rotation_matrix_reference=glGetUniformLocation(shader_program, "rotationMatrix");
	
	while(model_list_entry!=NULL)
	{
		/*using local matrices in vertex shader*/
		glUniformMatrix4fv(world_transform_matrix_reference,1,GL_FALSE,&model_list_entry->world_transform_matrix[0][0]);
		glUniformMatrix4fv(rotation_matrix_reference,1,GL_FALSE,&model_list_entry->rotation_matrix[0][0]);
		
		
		/*drawing everything*/
		/*if no index buffer available*/
		if(model_list_entry->index_bufferID==0)
		{
			glBindTexture(GL_TEXTURE_2D, model_list_entry->textureID);
			glBindVertexArray(model_list_entry->arrayID);
			glDrawArrays(GL_TRIANGLES,0,model_list_entry->num_vertices);
			
			/*unbind buffer*/
			glBindVertexArray(0);
		}
		/*if index buffer is available*/
		if(model_list_entry->index_bufferID!=0)
		{
			glBindTexture(GL_TEXTURE_2D, model_list_entry->textureID);
			glBindVertexArray(model_list_entry->arrayID);
			glBindBuffer(GL_ARRAY_BUFFER, model_list_entry->vertex_bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,model_list_entry->index_bufferID);
			glDrawElements(GL_TRIANGLES, model_list_entry->num_indices, GL_UNSIGNED_INT, NULL);
			
			/*unbind buffer*/
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		
		model_list_entry=gfx_next_entry();
	}
	
	/*swapping the buffer and clearing the screen for the next frame*/
	SDL_GL_SwapWindow(engine_get_window());
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}