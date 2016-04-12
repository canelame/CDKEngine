#version 330

in vec4 frag_color;

uniform vec3 light_pos;
uniform float far_plane;

void main(){
	
	float distance_light = length( frag_color.xyz - light_pos );
	distance_light /= far_plane;
	gl_FragDepth = distance_light;
}