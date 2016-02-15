#include "CDK/material.h"

#include "CDK/task_manager.h"

struct Material::MaterialSettings::Data{

  std::vector<std::string > texture_;
  vec3 diffuse_color;
  vec3 ambient_color;
  vec3 specular_color;
  float sh = 32.0f;//default;
};
float Material::MaterialSettings::getShinenes(){
  return data_->sh;
}
void Material::MaterialSettings::setShinenes(float value){
 data_->sh=value;
}
Material::Material(TYPE t){
  mat_settings_ = std::make_shared<MaterialSettings>();
  is_compiled_ = false;
  if (t == 0){
    std::stringstream temp_vertex_data;
    std::stringstream temp_fragment_data;
    std::string line;

    std::ifstream file_V("shaders/diffuse_f.glsl");
    if (file_V.is_open()){
      temp_vertex_data << file_V.rdbuf();
      file_V.close();
      line = temp_vertex_data.str();
      fragment_data_ = line;

    }
    std::stringstream temp_vertex_data1;
    std::stringstream temp_fragment_data1;
    std::ifstream file_V1("shaders/diffuse_v.glsl");
    if (file_V1.is_open()){
      temp_vertex_data1 << file_V1.rdbuf();
      file_V1.close();
      line = temp_vertex_data1.str();
      vertex_data_ = line;

    } 
  }else{

    std::stringstream temp_vertex_data;
    std::stringstream temp_fragment_data;
    std::string line;

    std::ifstream file_V("shaders/texture_f.glsl");
    if (file_V.is_open()){
      temp_vertex_data << file_V.rdbuf();
      file_V.close();
      line = temp_vertex_data.str();
      fragment_data_ = line;

    }
    std::stringstream temp_vertex_data1;
    std::stringstream temp_fragment_data1;
    std::ifstream file_V1("shaders/texture_v.glsl");
    if (file_V1.is_open()){
      temp_vertex_data1 << file_V1.rdbuf();
      file_V1.close();
      line = temp_vertex_data1.str();
      vertex_data_ = line;
    }

    printf("");
  }
;}

void Material::loadShader(const char *vertex_file, const char* fragment_file){

  vertex_data_ = vertex_file;
  fragment_data_ = fragment_file;
}


void Material::setProgram(int value){
  program_ = value;
}

unsigned int Material::getProgram(){
  return program_; 
}

Material::MaterialSettings& Material::getMaterialSettings(){
  return *mat_settings_.get();
}

std::string Material::getFragmentData(){ 
  return fragment_data_;
}
std::string Material::getVertexData(){ 
  return vertex_data_; 
}

void Material::MaterialSettings::addTexture(const char *name){

  data_->texture_.push_back(name);

}
int Material::MaterialSettings::totalTextures(){
  return data_->texture_.size();
}


std::string Material::MaterialSettings::getTextureAt(int index){
  return data_->texture_[index];
}

Material::MaterialSettings::MaterialSettings(){
  data_ = new Data;
}
Material::MaterialSettings::~MaterialSettings(){}

void Material::MaterialSettings::setDiffuseColor(vec3 diff_color){
  data_->diffuse_color = diff_color;
}
void Material::MaterialSettings::setSpecularColor(vec3 spe_color){
  data_->specular_color = spe_color;
}
void Material::MaterialSettings::setAmbientColor(vec3 amb_color){
  data_->ambient_color = amb_color;
}
vec3 Material::MaterialSettings::getAmbientColor(){
  return data_->diffuse_color;
}
vec3 Material::MaterialSettings::getSpecularColor(){
  return data_->specular_color;
}
vec3 Material::MaterialSettings::getAmbienColor(){
  return data_->ambient_color;
}
