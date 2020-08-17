#version 450

layout(location = 0) in vec3 vertexPosition_worldspace;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;
out float fragment_depth;

/*camera stuff*/
uniform mat4 projectionMatrix;  /*it is used for mapping the visible vertices to the normalized device space*/
uniform mat4 cam_translationMatrix; /*this matrix is used for making the camera the center of the world
 * and the world becomes relative to the camera*/

void main(){
    vec4 vertexPosition = vec4(vertexPosition_worldspace.xyz, 1.0);
    
    
    vertexPosition = projectionMatrix * cam_translationMatrix * vertexPosition;
    
    /*if vertex is behind the camera, then it is moved out of sight*/
    if(vertexPosition.z<0)
    {
        vertexPosition.xyzw = vec4(10,10,10,1);
    }
    

    /*giving OpenGL the new position*/
    gl_Position = vertexPosition;
    

    /*giving data to the fragment shader*/
    fragment_depth = vertexPosition.z;
    fragment_color = vertex_color;
    
}