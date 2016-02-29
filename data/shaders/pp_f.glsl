#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D u_pp_texture;


void main()
{
    color = vec4(vec3(1.0 - texture(u_pp_texture, TexCoords)), 1.0);
}  