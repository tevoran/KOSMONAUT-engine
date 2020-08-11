#version 450
#define PI 3.141593
#define near_z 1.175494351e-36 /*near cutting plane*/

layout(location = 0) in vec3 vertexPosition_worldspace;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;

uniform float world2gl; /*world space to normalized device space factor*/

/*camera stuff*/
uniform float fov; /*field of view in radians for the camera*/
uniform vec3 cam_location;
uniform vec2 cam_direction; /*camera direction is in radians as offset to the axises*/
uniform float far_z; /*far cutting plane
 * converted to normalized device space in gfx_create_camera()*/ 

void main(){
    vec3 vertexPosition;
    /*subtracting camera_position from vertex_position, to make the camera the center*/
    vertexPosition.xyz = vertexPosition_worldspace.xyz - cam_location.xyz;
    
    /*converting world space to normalized device space*/
    vertexPosition.xyz = vec3(vertexPosition.x*world2gl,vertexPosition.y*world2gl,vertexPosition.z*world2gl);
    vertexPosition.z = (-1)*vertexPosition.z;
    
    
    /*giving perspective*/
    vec3 tmp_pos;
    float alpha; /*temporary angle used for calculations*/
    float length,a,b,c; /*different terms for the calculation*/
    
    alpha = cam_direction.x-atan(vertexPosition.x/vertexPosition.z);
    tmp_pos.z = sqrt(vertexPosition.y*vertexPosition.y+vertexPosition.z*vertexPosition.z)*sin((PI*0.5)-alpha);
    a = sin((PI*0.5)-alpha)*sin(0.5*fov);
    if(tmp_pos.z>near_z && tmp_pos.z<far_z) /*checking if too close to camera, behind the camera or too far, if it is then it is clipped of*/
    {
    tmp_pos.x = sin(alpha)/a;
    
    alpha = cam_direction.y-atan(vertexPosition.y/vertexPosition.z);
    tmp_pos.z = sqrt(vertexPosition.y*vertexPosition.y+vertexPosition.z*vertexPosition.z)*sin((PI*0.5)-alpha);
    a = sin((PI*0.5)-alpha)*sin(0.5*fov);
    if(tmp_pos.z>near_z && tmp_pos.z<far_z) /*checking if too close to camera, behind the camera or too far, if it is then it is clipped of*/
    {
    tmp_pos.y = sin(alpha)/a;
    }
    else
    {
        tmp_pos.xyz = vec3(10, 10, 10); /*placing out of screen*/
    }
    
    }
    else
    {
        tmp_pos.xyz = vec3(10, 10, 10); /*placing out of screen*/
    }
    
    vertexPosition.xyz = tmp_pos.xyz;
    
    /*giving forth the final position of the vertex*/
    gl_Position.xyz = vertexPosition.xyz;
    gl_Position.w = 1;
    
    /*and the color*/
    fragment_color=vertex_color;
}