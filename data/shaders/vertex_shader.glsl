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


void main(){
	vec4 vertexPosition = vec4(vertexPosition_worldspace.xyz, 1.0);
	
	vertexPosition = camShaderMatrix
					* world_transformMatrix 
					* rotationMatrix 
					* vertexPosition;	
	
	/*if vertex is behind the camera, then it is moved out of sight*/
	if(vertexPosition.z<0)
	{
		vertexPosition.xyzw = vec4(10,10,10,1);
	}
	

	/*giving OpenGL the new position*/
	gl_Position = vertexPosition;
	

	/*giving data to the fragment shader*/
	fragment_depth = vertexPosition.z;
	fragment_tex_coord = tex_coord;
}