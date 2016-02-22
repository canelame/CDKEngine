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
in vec2 o_uv_d;
in vec3 o_normal_d;
in vec2 o_camera_d;
in vec4 o_world_position_d;
in vec3 o_cam_pos_d;


uniform vec3 u_material_diff_d;
uniform vec3 u_material_specular_d;
uniform vec3 u_material_ambient_d;
uniform float u_shinn_d;


uniform Light lights_d[10];

vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir);
vec3 computePointLight(Light l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir);

void main(){
	vec3 view = normalize(o_cam_pos_d-o_world_position_d.xyz);


	for(int i=0;i<10;i++){
		if(lights_d[i].type == 1){
			color.xyz+= computePointLight(lights_d[i],o_normal_d,o_world_position_d.xyz,view);
		}else if(lights_d[i].type==2){
			
			color.xyz+=computeDirectionLight(lights_d[i],o_normal_d,view);
		}
		
	}

}

vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir){
	vec3 lightDir = normalize(-l_dir.position);
	float diff = max(dot(normal,lightDir),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),0.32);

	vec3 ambient = l_dir.ambient_color*u_material_ambient_d;
	vec3 diffuse = l_dir.diffuse_color*diff*u_material_diff_d;
	vec3 specular = l_dir.specular_color *spec*u_material_specular_d;
 return  (ambient+diffuse+specular);


}

vec3 computePointLight(Light l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir){
	vec3 lightDir = normalize(l_dir.position-fragPos);
	float diff =max(dot(normal,lightDir),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),32.0);

	//attenuyuation
	float distance = length(l_dir.position-fragPos);
	vec3 ambient = l_dir.ambient_color*u_material_ambient_d;
	vec3 diffuse = l_dir.diffuse_color*u_material_diff_d;
	vec3 specular = l_dir.specular_color*u_material_specular_d ;
	 return  (ambient+diffuse+specular);



}