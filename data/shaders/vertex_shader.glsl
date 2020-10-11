#version 450

layout(location = 0) in vec3 vertexPosition_worldspace;
layout(location = 1) in vec2 tex_coord;

out float fragment_depth;
out vec2 fragment_tex_coord;

/*camera stuff*/
uniform mat4 camShaderMatrix;
 
/*model stuff*/
uniform mat4 world_transformMatrix;/*used for conversion of local to world space*/
uniform mat4 rotationMatrix;
uniform mat4 scalingMatrix;

/*render triggers*/
uniform uint uiTrigger;

uint blubb=0;

void main(){
	/*how to draw ui stuff*/
	if(uiTrigger==1)
	{
		vec4 vertexPosition = vec4(vertexPosition_worldspace.xyz, 1.0);
		
		vertexPosition= world_transformMatrix
						* vertexPosition;

		/*giving OpenGL the new position*/
		gl_Position = vertexPosition;
		

		/*giving data to the fragment shader*/
		fragment_depth = -1;
		fragment_tex_coord = tex_coord;
	}
	/*how to draw 3d stuff*/
	if(uiTrigger==0)
	{
		vec4 vertexPosition = vec4(vertexPosition_worldspace.xyz, 1.0);
		
		vertexPosition = camShaderMatrix
						* world_transformMatrix 
						* rotationMatrix
						* scalingMatrix
						* vertexPosition;	

		/*giving OpenGL the new position*/
		gl_Position = vertexPosition;
		

		/*giving data to the fragment shader*/
		fragment_depth = vertexPosition.z;
		fragment_tex_coord = tex_coord;
	}
}