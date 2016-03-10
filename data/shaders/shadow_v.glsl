#version 330
 (location = 0) in vec3 position;
 (location = 1) in vec3 normal;
 (location = 2) in vec3 uv;

uniform mat4 light_screen;
uniform mat4 u_model_m;


out vec2 o_uv;
out vec2 o_world_position
void main(){
	o_world_position = u_model_m_d * vec4(position,1.0);
	gl_Position = light_screen*o_world_position;

}
