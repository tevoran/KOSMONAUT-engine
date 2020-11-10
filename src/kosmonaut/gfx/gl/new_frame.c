#include "gfx/gfx.h"
#include "gfx/ui/ui.h"
#include "general/general.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "general/general.h"

extern GLuint shader_program;

void gfx_new_frame()
{
	GLfloat resolution[2]={(GLfloat)engine_config_state().resolution_x, (GLfloat)engine_config_state().resolution_y};
	GLint resolution_reference=glGetUniformLocation(shader_program, "resolution");
	glUniform2f(resolution_reference, resolution[0], resolution[1]);

	/*updating stuff*/
	/*skybox location*/
	gfx_update_skybox_location();

	/*calculating a single matrix for projection, camera rotation and location*/
	GLfloat cam_shader_matrix[4][4];
	gfx_camera_get_shader_matrix(cam_shader_matrix);
	GLint cam_shader_matrix_reference=glGetUniformLocation(shader_program, "camShaderMatrix");
	glUniformMatrix4fv(cam_shader_matrix_reference,1,GL_FALSE,&cam_shader_matrix[0][0]);

	/*drawing all models*/
	struct model* model_list_entry=gfx_select_first_entry();
	
	GLint world_transform_matrix_reference=glGetUniformLocation(shader_program, "world_transformMatrix");
	GLint rotation_matrix_reference=glGetUniformLocation(shader_program, "rotationMatrix");
	GLint scaling_matrix_reference=glGetUniformLocation(shader_program, "scalingMatrix");
	
	GLint ui_trigger_reference=glGetUniformLocation(shader_program, "uiTrigger");

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	while(model_list_entry!=NULL)
	{
		/*setting ui_trigger*/
		glUniform1ui(ui_trigger_reference, model_list_entry->ui_element);
		if(model_list_entry->ui_element==GFX_TRUE)
		{
			glDisable(GL_DEPTH_TEST);
		}

		/*drawing models*/
			/*using local matrices in vertex shader*/
			glUniformMatrix4fv(world_transform_matrix_reference,1,GL_FALSE,&model_list_entry->world_transform_matrix[0][0]);
			glUniformMatrix4fv(rotation_matrix_reference,1,GL_FALSE,&model_list_entry->rotation_matrix[0][0]);
			glUniformMatrix4fv(scaling_matrix_reference,1,GL_FALSE,&model_list_entry->scaling_matrix[0][0]);		
			
			/*drawing everything*/
			/*if no index buffer available*/
			if(model_list_entry->index_bufferID==0)
			{
				glBindTexture(GL_TEXTURE_2D, model_list_entry->textureID);
				glBindVertexArray(model_list_entry->arrayID);
				glDrawArrays(GL_TRIANGLES,0,model_list_entry->num_vertices);
			}
			/*if index buffer is available*/
			if(model_list_entry->index_bufferID!=0)
			{
				glBindTexture(GL_TEXTURE_2D, model_list_entry->textureID);
				glBindVertexArray(model_list_entry->arrayID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,model_list_entry->index_bufferID);
				glDrawElements(GL_TRIANGLES, model_list_entry->num_indices, GL_UNSIGNED_INT, NULL);
			}


		if(model_list_entry->ui_element==GFX_TRUE)
		{
			glEnable(GL_DEPTH_TEST);
		}
		
		model_list_entry=gfx_next_entry();
	}
	
	/*drawing GUI*/
	glDisable(GL_DEPTH_TEST);
	glUniform1ui(ui_trigger_reference, 1);

	GLuint window_size_reference=glGetUniformLocation(shader_program, "window_size");
	GLuint window_pos_reference=glGetUniformLocation(shader_program, "window_pos");

	struct ui_window *window=gfx_ui_window_select_first_element();

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	GLfloat test_matrix[]=
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	while(window!=NULL)
	{
		/*render window*/
		glUniform2f(window_size_reference, (GLfloat)window->size_x, (GLfloat)window->size_y);
		glUniform2f(window_pos_reference, (GLfloat)window->pos_x, (GLfloat)window->pos_y);
		glUniformMatrix4fv(world_transform_matrix_reference, 1, GL_FALSE, test_matrix);
		glBindTexture(GL_TEXTURE_2D, window->textureID);
		glBindVertexArray(window->arrayID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, window->index_bufferID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		window=gfx_ui_window_select_next_element();
	}

	glUniform1ui(ui_trigger_reference, 0);
	glEnable(GL_DEPTH_TEST);

	/*swapping the buffer and clearing the screen for the next frame*/
	SDL_GL_SwapWindow(engine_get_window());
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}