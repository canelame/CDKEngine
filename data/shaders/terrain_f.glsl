#version 330
out vec4 color;
in vec3 o_normal;
in vec4 o_world_position;
in vec2 o_uv;
in vec3 o_camera_position;


uniform sampler2D terrain_texture1;
uniform sampler2D terrain_texture2;
uniform sampler2D terrain_texture3;


void main(){

  //color = texture2D(terrain_texture,o_uv);
  color = vec4(1.0,0.0,0.0,1.0);
}
