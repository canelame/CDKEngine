#version 330 core

layout(triangles) in;
layout(triangle_strip,max_vertices=18) out;
uniform mat4 shadow_matrices[6];

out vec4 frag_color;

void main(){
	for(int i = 0 ; i < 6 ; i++){
		gl_Layer = i;
		for(int j = 0 ; j < 3 ; j++){
			frag_color = gl_in[j].gl_Position;
			gl_Position = shadow_matrices[i] * frag_color;
			EmitVertex();
		}
		EndPrimitive();
	}
}
