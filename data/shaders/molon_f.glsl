#version 330
in vec2 TexCoords;
out vec4 color;

uniform sampler2D u_pp_texture;
vec2 window_size =vec2(1024,768);

vec2 center = vec2(window_size.x/2.0,window_size.y/2.0);
float radius = 600.0;
float angle = 5.0;

vec4 guapo( ){
	vec2 tw_size = vec2(window_size.x,window_size.y);
	vec2 tc = TexCoords *tw_size;
	tc -=center; 
	float distance = length(tc);
	if(distance<radius){
		float percent = (radius-distance)/radius;
		float theta = percent *percent *angle * 1.0f;
		float s =sin(theta);
		float c = cos(theta);
		tc = vec2(dot(tc,vec2(c,-s)),dot(tc,vec2(s,c)));
	}
	tc+=center;
	vec3 color_ = texture(u_pp_texture,tc/tw_size).rgb;
	return vec4(color_,1.0);
}


void main()
{
    color = guapo();
 }