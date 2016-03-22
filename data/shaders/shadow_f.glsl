#version 330
out vec4 color;
in vec2 o_uv;
uniform sampler2D depth_texture;

void main(){
	float depth_value = texture(depth_texture,o_uv).r;
	color = vec4(vec3(depth_value),1.0f);
}