#include "CDK/cube_shadowmap_material.h"

CubeShadowMaterial::CubeShadowMaterial(){
  loadShader("shaders/point_shadow_v.glsl", "shaders/point_shadow_f.glsl", "shaders/point_shadow_geo.glsl");
  for (int i = 0; i < 6; i++){
   uniforms_.push_back( Material::UniformData( (char*)("shadow_matrices[" + std::to_string(i) + "]").c_str(),kUniformTypesMat4,-1,nullptr));
  }
  uniforms_.push_back(Material::UniformData("far_plane",kUniformTypesFloat,-1,nullptr) );
  uniforms_.push_back(Material::UniformData("light_pos", kUniformTypes3vFloat, -1, nullptr));

}
