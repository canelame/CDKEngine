#include "CDK/texture_material.h"
#include "CDK/texture_cache.h"


TextureMaterial::TextureMaterial(){
  loadShader("shaders/texture_v.glsl", "shaders/texture_f.glsl","");
  type_ = 0;
  uniforms_.push_back(Material::UniformData("u_material_ambient", kUniformTypes3vFloat,-1, NULL));
  uniforms_.push_back(Material::UniformData("u_material_diff", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_material_specular", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_view_m", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_projection_m", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_model_m", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("shadow_texture", kUniformTypesCubeSampler, 2, NULL));
  uniforms_.push_back(Material::UniformData("u_diffuse_texture1", kUniformTypesSampler2D, 0, NULL));
  

  uniforms_.push_back(Material::UniformData("u_directional_light.position", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.ambient_color", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.specular_color", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.diffuse_color", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.sh", kUniformTypesFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.type", kUniformTypesInt, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.ligth_view_proyection", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.depth_map", kUniformTypesSampler2D, 1, NULL));
  
  for (int i = 0; i < 10; i++){
    uniforms_.push_back( Material::UniformData( (char*)("lights[" + std::to_string(i) + "].position").c_str(), kUniformTypes3vFloat, -1, NULL) );
    uniforms_.push_back(Material::UniformData((char*)("lights[" + std::to_string(i) + "].ambient_color").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights[" + std::to_string(i) + "].specular_color").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights[" + std::to_string(i) + "].diffuse_color").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights[" + std::to_string(i) + "].sh").c_str(), kUniformTypesFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights[" + std::to_string(i) + "].type").c_str(), kUniformTypesInt, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights[" + std::to_string(i) + "].depth_map").c_str(), kUniformTypesSampler2D, 0, NULL));
  }
  
};

int TextureMaterial::MaterialSettings::totalTextures(){
  return texture_.size();
}



const char* TextureMaterial::MaterialSettings::getTextureAt(int i){
  return texture_.at(i).c_str();
}

void TextureMaterial::MaterialSettings::addTexture(const char *name){

  texture_.push_back(name);
  std::shared_ptr<Texture> new_texture = std::make_shared<Texture>();
  new_texture->loadTexture(name,"diffuse");
  TextureCache::instance().addTexture(new_texture);
}
std::vector<std::string> TextureMaterial::MaterialSettings::getTextures(){
  return texture_;
}
