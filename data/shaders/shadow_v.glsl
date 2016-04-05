#version 330

layout(location=0) in vec3 position;


uniform mat4 light_screen;
uniform mat4 u_model;

out vec2 o_uv;

void main(){
	
	gl_Position = light_screen*u_model*vec4(position,1.0);
}
