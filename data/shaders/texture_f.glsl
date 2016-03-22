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
in vec4 o_light_frag;

uniform sampler2D u_diffuse_texture1;
uniform sampler2D shadow_texture;

uniform vec3 u_material_diff;
uniform vec3 u_material_specular;
uniform vec3 u_material_ambient;
uniform float u_shinn;


uniform Light lights[10];


vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir);
vec3 computePointLight(Light l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir);

float computeShadows(vec4 posLightSpace){
	vec3 projectionFrag = posLightSpace.xyz/posLightSpace.w;
	projectionFrag = projectionFrag * 0.5 + 0.5; 
	float depthValue = texture(shadow_texture,projectionFrag.xy).r;
	float currentDepthValue = projectionFrag.z;
	float shadow = currentDepthValue>depthValue ? 1.0 : 0.0;
	return shadow;

}

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

	vec3 ambient = l_dir.ambient_color*u_material_ambient* vec3(texture(u_diffuse_texture1,o_uv));
	vec3 diffuse = l_dir.diffuse_color*diff*u_material_diff* vec3(texture(u_diffuse_texture1,o_uv));
	vec3 specular = l_dir.specular_color *spec*u_material_specular* vec3(texture(u_diffuse_texture1,o_uv));
	float shadow = computeShadows(o_light_frag);
	vec3 lighting = ( ambient + ( 1.0-shadow ) * ( diffuse + specular) );
	return  lighting;


}

vec3 computePointLight(Light l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir){
	vec3 lightDir = normalize(l_dir.position-fragPos);
	float diff =max(dot(normal,lightDir),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),32.0);

	//attenuyuation
	float distance = length(l_dir.position-fragPos);
	float attenuation = 1.0/(1.0f+0.09*distance+0.032*(distance*distance));

	vec3 ambient = (l_dir.ambient_color*u_material_ambient*vec3(texture(u_diffuse_texture1,o_uv))*attenuation);
	vec3 diffuse = (l_dir.diffuse_color*u_material_diff*vec3(texture(u_diffuse_texture1,o_uv))*attenuation);
	vec3 specular = (l_dir.specular_color*u_material_specular * vec3(texture(u_diffuse_texture1,o_uv))*attenuation);

	 return  (ambient+diffuse+specular);

}