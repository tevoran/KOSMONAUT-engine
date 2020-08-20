#include "gfx/gfx.h"

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>


//function returns the GLuint program reference
GLuint gfx_loading_shaders()

{
    //data used for the function
    int shader_size;
    FILE *shader_file;
    
    char *vertex_shader_string;
    GLuint vertex_shader_reference;
    
    char *fragment_shader_string;
    GLuint fragment_shader_reference;

    GLuint shader_program_reference;
    
    GLenum error;
    
    //loading vertex shader
    printf("Loading Vertex Shader...");
    
    
    shader_file=fopen("src/SCBE/gfx/shaders/vertex_shader.glsl","r");
    if(shader_file==NULL)//error message if there is an error while reading the vertex shader file
    {
        printf("\n[ERROR] error while reading vertex shader file\n");
        return 1;
    }

        //determining file size for memory allocation
        fseek(shader_file, 0, SEEK_END);
        shader_size=ftell(shader_file);
        fseek(shader_file, 0, SEEK_SET);
        
        //allocating memory
        vertex_shader_string=malloc(shader_size+1);
        fread(vertex_shader_string, shader_size,1,shader_file);
        vertex_shader_string[shader_size] = '\0';
        
        printf("done\n");

    //loading fragment shader
    printf("Loading Fragment Shader...");
    
    shader_file=fopen("src/SCBE/gfx/shaders/fragment_shader.glsl","r");
    if(shader_file==NULL)//error message if there is an error while reading the fragment shader file
    {
        printf("\n[ERROR] error while reading fragment shader file\n");
        return 1;
    }

        //determining file size for memory allocation
        fseek(shader_file, 0, SEEK_END);
        shader_size=ftell(shader_file);
        fseek(shader_file, 0, SEEK_SET);
        
        //allocating memory
        fragment_shader_string=malloc(shader_size+1);
        fread(fragment_shader_string, shader_size,1,shader_file);
        fragment_shader_string[shader_size] = '\0';
        printf("done\n");
        
    //creating shaders
        //vertex shader
        vertex_shader_reference=glCreateShader(GL_VERTEX_SHADER);
        if(vertex_shader_reference==GL_INVALID_ENUM)
        {
            printf("[ERROR] error while creating vertex shader\n");
            return 1;
        }
            
        //fragment shader
        fragment_shader_reference=glCreateShader(GL_FRAGMENT_SHADER);
        if(fragment_shader_reference==GL_INVALID_ENUM)
        {
            printf("[ERROR] error while creating fragment shader\n");
            return 1;
        }

    //shader source will be given to opengl
        //vertex shader
        const GLchar* vertex_const_char = vertex_shader_string;
        glShaderSource(vertex_shader_reference, 1, &vertex_const_char, NULL);
        
        error=glGetError();
        if(error!=GL_NO_ERROR)
        {
            printf("[ERROR] error while giving vertex shader source code to OpenGL\n");
            return 1;
        }
        
        //fragment shader
        const GLchar* fragment_const_char = fragment_shader_string;
        glShaderSource(fragment_shader_reference, 1, &fragment_const_char, NULL);
        
        error=glGetError();
        if(error!=GL_NO_ERROR)
        {
            printf("[ERROR] error while giving fragment shader source code to OpenGL\n");
            return 1;
        }

    
    //compiling shader
        //vertex shader
        glCompileShader(vertex_shader_reference);

        glGetShaderiv(vertex_shader_reference, GL_COMPILE_STATUS, &error);
        
        if(error!=GL_TRUE)
        {
            printf("[ERROR] error while compiling vertex shader\n");
            
            //determining error
            GLint max_length=0;
            glGetShaderiv(vertex_shader_reference, GL_INFO_LOG_LENGTH, &max_length);
            
            
            GLchar error_msg[max_length];
            glGetShaderInfoLog(vertex_shader_reference,max_length,&max_length,&error_msg[0]);
            printf("OPENGL ERROR MSG:\n %s\n",error_msg);
            
            return 1;
        }


        
        //fragment shader
        glCompileShader(fragment_shader_reference);
        
        glGetShaderiv(fragment_shader_reference, GL_COMPILE_STATUS, &error);
        
        if(error!=GL_TRUE)
        {
            printf("[ERROR] error while compiling fragment shader\n");
            
            //determining error
            GLint max_length=0;
            glGetShaderiv(fragment_shader_reference, GL_INFO_LOG_LENGTH, &max_length);
            
            
            GLchar error_msg[max_length];
            glGetShaderInfoLog(fragment_shader_reference,max_length,&max_length,&error_msg[0]);
            printf("OPENGL ERROR MSG:\n %s\n",error_msg);
            
            return 1;
        }

        
        
    //creating shader program
    shader_program_reference=glCreateProgram();
    if(shader_program_reference==0)
    {
        printf("[ERROR] error while creating program\n");
        return 1;
    }

    //attach shaders
        //vertex shader
        glAttachShader(shader_program_reference, vertex_shader_reference);
        
        error=glGetError();
        if(error!=GL_NO_ERROR)
        {
            printf("[ERROR] error while attaching vertex shader\n");
            return 1;
        }
        
        //fragment shader
        glAttachShader(shader_program_reference, fragment_shader_reference);
    
        error=glGetError();
        if(error!=GL_NO_ERROR)
        {
            printf("[ERROR] error while attaching fragment shader\n");
            return 1;
        }

        

    //link program
    glLinkProgram(shader_program_reference);
    

    glGetProgramiv(shader_program_reference, GL_LINK_STATUS, &error);
    
    if(error!=GL_TRUE)
    {
        printf("[ERROR] Program couldn't be linked\n");
        return 1;
    }

        
    //use program
    glUseProgram(shader_program_reference);
    
        error=glGetError();
        if(error!=GL_NO_ERROR)
        {
            printf("[ERROR] error while using program\n");
            return 1;
        }

    
    return shader_program_reference;
}