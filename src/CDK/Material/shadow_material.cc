#include "CDK/Material/shadow_material.h"
ShadowMapMaterial::ShadowMapMaterial(){
  loadShader("shaders/shadow_v.glsl", "shaders/shadow_f.glsl", "");
  uniforms_.push_back(Material::UniformData("light_screen", kUniformTypesMat4, -1, nullptr));
  uniforms_.push_back(Material::UniformData("u_model_s", kUniformTypesMat4, -1, nullptr));
}