#include "CDK/Material/material_composer.h"
ComposerMaterial::ComposerMaterial(){
  loadShader("shaders/pp_v.glsl","shaders/pp_f.glsl","");
  uniforms_.push_back(UniformData("u_pp_texture0",Material::UniformTypes::kUniformTypesSampler2D,-1,NULL));
  uniforms_.push_back(UniformData("u_pp_texture1", Material::UniformTypes::kUniformTypesSampler2D, -1, NULL));
  uniforms_.push_back(UniformData("u_pp_texture2", Material::UniformTypes::kUniformTypesSampler2D, -1, NULL));
}


ComposerMaterial::~ComposerMaterial(){

}