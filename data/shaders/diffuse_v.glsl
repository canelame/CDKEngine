#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 u_projection_m_d;
uniform mat4 u_model_m_d;
uniform mat4 u_view_m_d;


out vec2 o_uv_d;
out vec3 o_normal_d;
out vec4 o_world_position_d;
out vec3 o_cam_pos_d;

vec3 camera_position_d = (inverse(u_view_m_d)*vec4(0.0,0.0,0.0,1.0)).xyz;
void main(){
	o_normal_d = normal;
	o_uv_d =uv;
	o_normal_d = vec3( normalize( u_model_m_d * vec4( o_normal_d,0.0) ) );
	o_world_position_d = u_model_m_d * vec4(position,1.0);
	o_cam_pos_d = camera_position_d;
	gl_Position = u_projection_m_d*u_view_m_d*o_world_position_d;


}