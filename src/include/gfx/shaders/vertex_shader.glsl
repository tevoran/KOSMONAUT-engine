#version 450

layout(location = 0) in vec3 vertexPosition_worldspace;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;

/*camera stuff*/
uniform mat4 projectionMatrix;

uniform vec3 cam_location;
uniform vec2 cam_direction; /*camera direction is in radians as offset to the axises*/

void main(){
    vec4 vertexPosition = vec4(vertexPosition_worldspace.xyz, 1.0);
    
    
    
    vertexPosition = projectionMatrix * vertexPosition;
    
    /*if vertex is behind the camera, then it is moved out of sight*/
    if(vertexPosition.z<0)
    {
        vertexPosition.xyzw = vec4(10,10,10,1);
    }
    
    gl_Position = vertexPosition;
    
    /*and the color*/
    fragment_color=vertex_color;
}