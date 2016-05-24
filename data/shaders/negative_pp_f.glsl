#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D u_wb_texture;



void main()
{
		color = vec4(1.0 - vec3(texture(u_wb_texture, TexCoords)), 1.0);
}  