#version 330
struct Light{
	vec3 position;
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	float sh;
	int type;//0 none 1 pint 2 direction
};
out vec4 color;
in vec2 o_uv;
in vec3 o_normal;
in vec2 o_camera;
in vec4 o_world_position;
in vec3 o_cam_pos;

uniform sampler2D u_diffuse_texture1;
uniform sampler2D u_diffuse_texture2; 

uniform sampler2D u_specular_texture1; 
uniform sampler2D u_specular_texture2;

uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform vec3 ambient_color;
uniform vec3 sh_specular;

uniform Light lights[10];


vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir);
vec3 computePointLight(Light l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir);


void main(){
	vec3 view = normalize(o_cam_pos-o_world_position.xyz);

	
	//color.xyz = vec3(1.0,1.0,1.0f)*vec3(texture(u_diffuse_texture1,o_uv));
	//color.xyz =computeDirectionLight(default_light,o_normal,view);

	for(int i=0;i<10;i++){
		if(lights[i].type == 1){
			color.xyz+= computePointLight(lights[i],o_normal,o_world_position.xyz,view);
		}else if(lights[i].type==2){
			color.xyz+=computeDirectionLight(lights[i],o_normal,view);
		}
	}

}

vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir){
	vec3 lightDir = normalize(-l_dir.position);
	float diff = max(dot(normal,lightDir),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),0.32);

	vec3 ambient = ambient_color* vec3(texture(u_diffuse_texture1,o_uv));
	vec3 diffuse =diffuse_color*diff*vec3(texture(u_diffuse_texture1,o_uv));
	vec3 specular = specular_color *spec* vec3(texture(u_specular_texture1,o_uv));
 return  (ambient+diffuse+specular);


}

vec3 computePointLight(Light l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir){
	vec3 lightDir = normalize(l_dir.position-fragPos);
	float diff =max(dot(normal,lightDir),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),32.0);

	//attenuyuation
	float distance = length(l_dir.position-fragPos);
	vec3 ambient = ambient_color*vec3(texture(u_diffuse_texture1,o_uv));
	vec3 diffuse = diffuse_color*vec3(texture(u_diffuse_texture1,o_uv));
	vec3 specular = specular_color* vec3(texture(u_specular_texture1,o_uv));
	 return  (ambient+diffuse+specular);
}
/*vec3 computeDiffuseColor(){}
vec3 computeSpecularColor(vec3 normal){
	vec3 norm = normalize(normal);

	vec3 specular;
}
vec3 computeAmbientColor(){
	vec3 ambient = diffuse_color
	return ambient;
}*/