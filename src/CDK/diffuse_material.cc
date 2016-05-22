#include "CDK/diffuse_material.h"

MaterialDiffuse::MaterialDiffuse(){
  loadShader("shaders/diffuse_v.glsl", "shaders/diffuse_f.glsl", "");
  type_ = 1;
  uniforms_.push_back(Material::UniformData("u_material_ambient_d", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_material_diff_d", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_material_specular_d", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_view_m_d", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_projection_m_d", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_model_m_d", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("shadow_texture", kUniformTypesCubeSampler, -1, NULL));


  uniforms_.push_back(Material::UniformData("u_directional_light.position", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.ambient_color", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.specular_color", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.diffuse_color", kUniformTypes3vFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.sh", kUniformTypesFloat, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.ligth_view_proyection", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_directional_light.depth_map", kUniformTypesSampler2D, -1, NULL));

  for (int i = 0; i < 10; i++){
    uniforms_.push_back(Material::UniformData((char*)("lights_d[" + std::to_string(i) + "].position").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights_d[" + std::to_string(i) + "].ambient_color").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights_d[" + std::to_string(i) + "].specular_color").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights_d[" + std::to_string(i) + "].diffuse_color").c_str(), kUniformTypes3vFloat, -1, NULL));
    uniforms_.push_back(Material::UniformData((char*)("lights_d[" + std::to_string(i) + "].sh").c_str(), kUniformTypesFloat, -1, NULL));

  }

};

MaterialDiffuse::~MaterialDiffuse(){

}