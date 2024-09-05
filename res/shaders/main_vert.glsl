#version 460 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec2 vert_texture_coords;
layout (location = 2) in int  vert_texture_id;

out vec4  frag_color;
out vec2  frag_texture_coords;
out float frag_texture_id;

uniform mat4 model;
uniform mat4 projview;

void main() {
	frag_color          = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	gl_Position = projview * model * vec4(vert_position, 1.0);

	frag_texture_coords = vert_texture_coords;
	frag_texture_id     = float(vert_texture_id);
}