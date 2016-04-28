#version 330
struct Light{
	vec3 position;
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	float sh;
	int type;//0 none 1 pint 2 direction 3 spot
	sampler2D depth_map;
	mat4 ligth_view_proyection;
	//Only used to spot lights
	vec3 direction;
	float cone_angle;

};

struct SpotLight{
	vec3 position;
	

	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	float sh;
	int type;//0 none 1 pint 2 direction
	sampler2D depth_map;
	mat4 ligth_view_proyection;
};

struct PointLight{
	vec3 position;
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	float sh;
	int type;//0 none 1 pint 2 direction
	samplerCube depth_map;
};

out vec4 color;
in vec2 o_uv;
in vec3 o_normal;
in vec2 o_camera;
in vec4 o_world_position;
in vec3 o_cam_pos;
in vec4 o_light_frag;

uniform sampler2D u_diffuse_texture1;
uniform samplerCube shadow_texture;


uniform vec3 u_material_diff;
uniform vec3 u_material_specular;
uniform vec3 u_material_ambient;
uniform float u_shinn;


 uniform PointLight lights[10];
 uniform Light u_directional_light;


vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir);
vec3 computePointLight(PointLight l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir);


//Compute point light shadow
float far_plane = 25.0f;



float computePointLightShadow(vec3 fragPos, PointLight light){

	vec3 frag_to_light = fragPos - light.position;
	float depth_value = texture( shadow_texture, frag_to_light ).r;
	depth_value *= far_plane;

	float current_depth_value = length( frag_to_light );
	float bias = 0.05f;
	float shadow = current_depth_value  > depth_value ? 1.0f : 0.0f;
	return shadow;
}

//Compute directional shadow
float computeShadows(vec4 posLightSpace,vec3 normal,vec3 light_dir){
	vec3 projectionFrag = posLightSpace.xyz/posLightSpace.w;
	projectionFrag = projectionFrag * 0.5 + 0.5; 
	float depthValue = texture(u_directional_light.depth_map , projectionFrag.xy).r;
	float currentDepthValue = projectionFrag.z;

    float bias = max(0.05 * (1.0 - dot(normal, light_dir)), 0.005);  
	float shadow = 0.0f ;
	//PFC
	
	vec2 texel_size = 1.0f / textureSize(u_directional_light.depth_map,0);
	for(int x = -1; x <=1 ; ++x){
		for(int y = -1 ; y <= 1; ++y){
			float pfc_depth = texture(u_directional_light.depth_map,projectionFrag.xy + vec2(x,y) * texel_size).r;
			shadow += currentDepthValue - bias > pfc_depth ? 1.0f :0.0f;
		}
	}
	shadow /= 9.0f;
		if(currentDepthValue >1.0){
		return 0.0;
	}

	return shadow;

}



vec3 computeDirectionLight(Light l_dir,vec3 normal,vec3 viewDir){

	vec4 directional_light_proyection = u_directional_light.ligth_view_proyection * o_world_position;

	vec3 lightDir = normalize(-l_dir.position);
	float diff = max(dot(normal,lightDir),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),0.32);

	vec3 ambient = l_dir.ambient_color*u_material_ambient* vec3(texture(u_diffuse_texture1,o_uv));

	vec3 diffuse = l_dir.diffuse_color*diff*u_material_diff* vec3(texture(u_diffuse_texture1,o_uv));
	vec3 specular = l_dir.specular_color *spec*u_material_specular* vec3(texture(u_diffuse_texture1,o_uv));
	float shadow = computeShadows(directional_light_proyection,normal,lightDir);
	vec3 lighting = ( ambient +(1.0-shadow)*  (diffuse + specular));
	return  lighting;


}

vec3 computePointLight(PointLight l_dir,vec3 normal ,vec3 fragPos,vec3 viewDir){

	
	vec3 lightDir = normalize(l_dir.position-fragPos);
	float diff =max(dot(lightDir,normal),0.0);
	vec3 rf = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,rf),0.0),32.0);

	//attenuyuation
	float distance = length(l_dir.position-fragPos);
	float attenuation = 1.0/(1.0f+0.09*distance+0.032*(distance*distance));

	vec3 ambient = (l_dir.ambient_color*u_material_ambient*vec3(texture(u_diffuse_texture1,o_uv))*attenuation);
	vec3 diffuse = (l_dir.diffuse_color*u_material_diff*vec3(texture(u_diffuse_texture1,o_uv))*attenuation);
	vec3 specular = (l_dir.specular_color*u_material_specular * vec3(texture(u_diffuse_texture1,o_uv))*attenuation);

	float shadow  =  computePointLightShadow(fragPos, l_dir);

	 return  ( ambient + ( 1.0f - shadow) * (diffuse+specular) );

}

vec3 computeSpotLight(Light light, vec3 frag_pos, vec3 normal,vec3 view_dir ){
	vec3 light_direction = normalize( light.position - frag_pos);
	float angle_light = dot( light_direction , normalize(-light.direction) );

	if( angle_light > light.cone_angle){

		float diff = max( dot(light_direction,normal) ,0.0);
		vec3 rf = reflect(-light_direction,normal);
		float spec = pow(max(dot(view_dir,rf),0.0),32.0);

		//attenuyuation
		float distance = length(light.position-frag_pos);
		float attenuation = 1.0/(1.0f+0.09*distance+0.032*(distance*distance));

		vec3 ambient = (light.ambient_color*u_material_ambient*vec3(texture(u_diffuse_texture1,o_uv))*attenuation);
		vec3 diffuse = (light.diffuse_color*u_material_diff*vec3(texture(u_diffuse_texture1,o_uv))*attenuation);
		vec3 specular = (light.specular_color*u_material_specular * vec3(texture(u_diffuse_texture1,o_uv))*attenuation);

		//float shadow = computeShadows(light.ligth_view_proyection * o_world_position , normal , light_direction);
		return ambient + ( (1.0f ) * (diffuse+specular) ) ;
	}

}




void main(){
	vec3 view = normalize(o_cam_pos-o_world_position.xyz);
	color.xyz+=computeDirectionLight( u_directional_light,o_normal,view);
	for(int i = 0 ; i< 10;i++){
		color.xyz += computePointLight(lights[i],o_normal ,o_world_position.xyz,view);
	}

}

