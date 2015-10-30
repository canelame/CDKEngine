#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;

uniform mat4 u_projection_m;
uniform mat4 u_model_m;
uniform mat4 u_view_m;


out vec2 o_uv;
out vec3 o_normal;
out vec4 o_world_position;



vec3 camera_position = (inverse(u_view_m)*vec4(0.0,0.0,0.0,1.0)).xyz;
void main(){
	o_normal = normal;
	o_uv =uv;
	o_normal = vec3( normalize( u_model_m * vec4( o_normal,0.0) ) );
	o_world_position = u_model_m * vec4(position,1.0);
	gl_Position = u_projection_m*u_view_m*o_world_position;


}