#include "CDK/texture_material.h"

TextureMaterial::TextureMaterial(){
  loadShader("shaders/texture_v.glsl", "shaders/texture_f.glsl");
  type_ = 0;
};

int TextureMaterial::MaterialSettings::totalTextures(){
  return texture_.size();
}



const char* TextureMaterial::MaterialSettings::getTextureAt(int i){
  return texture_.at(i).c_str();
}

void TextureMaterial::MaterialSettings::addTexture(const char *name){

  texture_.push_back(name);

}
std::vector<std::string> TextureMaterial::MaterialSettings::getTextures(){
  return texture_;
}
