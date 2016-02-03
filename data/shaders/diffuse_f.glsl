#version 330

out vec4 color;
in vec2 o_uv;
in vec3 o_normal;
in vec2 o_camera;
in vec4 o_world_position;
uniform vec3 diffuse_color;
vec3 oColor  = vec3(1.0,0.0,0.0);
void main(){
	color =vec4(o_world_position.xyz,1.0);
}