#include "CDK/material.h"

#include "CDK/task_manager.h"

struct Material::MaterialSettings{
  Light material_lights_[10];
  std::vector<std::string > texture_;
  vec3 diffuse_color_;
};

Material::Material(TYPE t){


  material_settings_ = new MaterialSettings;
  is_compiled_ = false;
  material_settings_->diffuse_color_ = vec3(0.0f, 0.0, 0.0f);
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



std::string Material::getFragmentData(){ 
  return fragment_data_;
}
std::string Material::getVertexData(){ 
  return vertex_data_; 
}

void Material::addTexture(const char *name){

  material_settings_->texture_.push_back(name);

}
int Material::totalTextures(){
  return material_settings_->texture_.size();
}


std::vector<std::string> Material::getTextures(){
  return material_settings_->texture_;
}
const char* Material::getTextureAt(int i){ 
  return material_settings_->texture_.at(i).c_str(); 
}

int Material::getTotalLights(){
  return 10;
};

Light Material::lightAt(int i){
 return  material_settings_->material_lights_[i];
}
void Material::setColor(vec3 color){
  material_settings_->diffuse_color_ = color;
}

vec3 Material::getColor(){
  return material_settings_->diffuse_color_;
}