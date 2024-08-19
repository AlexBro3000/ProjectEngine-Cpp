#version 460 core

in vec4 a_color;
in vec2 a_texCoord;
out vec4 f_color;

uniform sampler2DArray u_texture;

void main(){
	f_color = a_color * texture(u_texture, vec3(a_texCoord.xy, 0));
}