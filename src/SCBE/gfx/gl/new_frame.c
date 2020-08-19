#include "gfx/gfx.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>

#include "general/general.h"

extern GLuint shader_program;

void gfx_new_frame()
{
    /*drawing all primitives*/
    struct model* model_list_entry=gfx_select_first_entry();
    
    while(model_list_entry!=NULL)
    {
        /*using local matrices in vertex shader*/
        
        GLint world_transform_matrix_reference=glGetUniformLocation(shader_program, "world_transformMatrix");
        glUniformMatrix4fv(world_transform_matrix_reference,1,GL_FALSE,&model_list_entry->world_transform_matrix[0][0]);
        
        /*drawing everything*/
        glBindVertexArray(model_list_entry->arrayID);
        glDrawArrays(GL_TRIANGLES,0,model_list_entry->num_vertices);
        
        glBindVertexArray(0);
        
        model_list_entry=gfx_next_entry();
    }
    
    /*swapping the buffer and clearing the screen for the next frame*/
    SDL_GL_SwapWindow(engine_get_window());
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}