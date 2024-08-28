#version 460 core

layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec4 vert_color;

out vec4 frag_color;

uniform mat4 model;
uniform mat4 projview;


void main(){
	frag_color  = vert_color;
	gl_Position = projview * model * vec4(vert_position, 1.0);
}