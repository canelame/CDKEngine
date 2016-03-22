#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 light_screen;
uniform mat4 u_model;

out vec2 o_uv;

void main(){
	o_uv = uv;
	gl_Position = light_screen*u_model*vec4(position,1.0);
}
