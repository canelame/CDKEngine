#version 330

layout(location=0) in vec3 position;
uniform mat4 u_model_sp;
void main(){
	gl_Position = u_model_sp*vec4(position,1.0);
}
