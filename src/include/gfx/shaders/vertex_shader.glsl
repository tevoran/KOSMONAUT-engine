#version 450

layout(location = 0) in vec3 vertexPosition_worldspace;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;

uniform float world2gl; /*world space to normalized device space factor*/
uniform float fov; /*field of view in radians for the camera*/

void main(){
    /*converting world space to normalized device space*/
    vec3 vertexPosition; /*variable for position after conversion*/
    vertexPosition.xyz = vec3(vertexPosition_worldspace.x*world2gl,vertexPosition_worldspace.y*world2gl,vertexPosition_worldspace.z*world2gl);
    vertexPosition.z = (-1)*vertexPosition.z;
    
    
    /*giving perspective*/
    vec2 tmp_pos;
    tmp_pos.x = vertexPosition.x/vertexPosition.z;
    tmp_pos.y = vertexPosition.y/vertexPosition.z;
    
    vertexPosition.xy = tmp_pos.xy;
    
    /*giving forth the final position of the vertex*/
    gl_Position.xyz = vertexPosition.xyz;
    gl_Position.w = 1;
    
    /*and the color*/
    fragment_color=vertex_color;
}