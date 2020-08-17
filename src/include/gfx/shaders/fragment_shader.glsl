#version 450

in vec3 fragment_color;
in float fragment_depth;

out vec4 color;

void main() {
  color = vec4(vec3(fragment_color),1.0f);
  
  /*giving the depth of the fragment to the z-buffer*/
  gl_FragDepth = fragment_depth;
}