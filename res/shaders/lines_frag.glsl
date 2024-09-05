#version 460 core

in vec4  frag_color;

out vec4 color;

uniform sampler2DArray u_texture;

void main() {
	color = frag_color;
}