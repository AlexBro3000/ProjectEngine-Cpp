#version 460 core

in vec4  frag_color;
in vec2  frag_texture_coords;
in float frag_texture_id;

out vec4 color;

uniform sampler2DArray u_texture;

void main() {
	color = frag_color * texture(u_texture, vec3(frag_texture_coords.xy, frag_texture_id));
}