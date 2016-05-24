#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D u_pp_texture0;
uniform sampler2D u_pp_texture1;
//uniform sampler2D u_pp_texture2;w
uniform int total;


void main()
{
	//if(total == 1){
		//color = vec4(vec3(texture(u_pp_texture0, TexCoords)), 1.0);
	//}else if(total == 2){
		color = vec4(vec3( texture(u_pp_texture0, TexCoords)), 1.0);
		color += vec4(vec3( texture(u_pp_texture1, TexCoords)), 1.0);
	//	}
	//}else if(total == 3){
		//color = vec4(vec3(texture(u_pp_texture0, TexCoords)), 1.0);
		//color += vec4(vec3(texture(u_pp_texture1, TexCoords)), 1.0);
		//color += vec4(vec3(texture(u_pp_texture2, TexCoords)), 1.0);
	//}
    
}  