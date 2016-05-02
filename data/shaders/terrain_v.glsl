#version 330

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 uvs;

uniform mat4 u_mat_projec;
uniform mat4 u_mat_model;
uniform mat4 u_mat_view;

uniform mat4 u_mat_height_map_scale;

out vec3 o_normal;
out vec4 o_world_position;
out vec2 o_uv;
out vec3 o_camera_position;

vec3 camera_position = (inverse( u_mat_view)* vec4(0.0,0.0,0.0,1.0)).xyz;
void main(){

  vec4 inPositionedScaled  =u_mat_model * vec4(position,1.0);

  o_normal = vec3(normalize(u_mat_model * vec4(o_normal,0.0)));

  o_world_position =u_mat_model * vec4(position,1.0);
  o_uv = uvs;
  o_camera_position = camera_position;
  gl_Position = u_mat_projec * u_mat_view * o_world_position;
}
