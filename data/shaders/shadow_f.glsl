#version 330

in vec2 o_uv;
in vec2 o_world_position;

uniform sampler2D depth_texture;
out vec4 color;

void main(){
	float depth = texture(depth_texture,o_uv).r;
	
	color = vec4(vec3depth)1.0);

}