#version 450

in float fragment_depth;
in vec2 fragment_tex_coord;

uniform sampler2D fragment_texture;

out vec4 color;

void main() {
  color = texture(fragment_texture, fragment_tex_coord);
  
  /*giving the depth of the fragment to the z-buffer*/
  gl_FragDepth = fragment_depth;
}