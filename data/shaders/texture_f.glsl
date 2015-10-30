#version 330

out vec4 color;
in vec2 o_uv;
in vec3 o_normal;
in vec2 o_camera;
in vec4 o_world_position;

uniform sampler2D u_texture;

vec3 oColor  = vec3(1.0,0.0,0.0);
void main(){
	color =texture(u_texture,o_uv);
}