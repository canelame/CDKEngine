#include "terrain_mat.h"

TerrainMaterial::TerrainMaterial(){
  loadShader("shaders/terrain_v.glsl", "shaders/terrain_f.glsl", "");
  uniforms_.push_back(Material::UniformData("u_mat_projec", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_mat_model", kUniformTypesMat4, -1, NULL));
  uniforms_.push_back(Material::UniformData("u_mat_view", kUniformTypesMat4, -1, NULL));

  uniforms_.push_back(Material::UniformData("terrain_texture1", kUniformTypesSampler2D, -1, NULL));
  uniforms_.push_back(Material::UniformData("terrain_texture2", kUniformTypesSampler2D, -1, NULL));
  uniforms_.push_back(Material::UniformData("terrain_texture3", kUniformTypesSampler2D, -1, NULL));

}

TerrainMaterial::~TerrainMaterial(){

}

