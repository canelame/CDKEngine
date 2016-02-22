#include "CDK/material.h"

#include "CDK/task_manager.h"


Material::Material(TYPE t){


  
  is_compiled_ = false;

  if (t == 0){

    loadShader("shaders/diffuse_f.glsl", "shaders/diffuse_v.glsl");

  }else{

    loadShader("shaders/texture_f.glsl", "shaders/texture_v.glsl");

  }
;}

void Material::loadShader(const char *vertex_file, const char* fragment_file){
  std::stringstream temp_vertex_data;
  std::stringstream temp_fragment_data;
  std::string line;

  std::ifstream file_V(vertex_file);
  if (file_V.is_open()){
    temp_vertex_data << file_V.rdbuf();
    file_V.close();
    line = temp_vertex_data.str();
    fragment_data_ = line;

  }
  std::stringstream temp_vertex_data1;
  std::stringstream temp_fragment_data1;
  std::ifstream file_V1(fragment_file);
  if (file_V1.is_open()){
    temp_vertex_data1 << file_V1.rdbuf();
    file_V1.close();
    line = temp_vertex_data1.str();
    vertex_data_ = line;
  }


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

void Material::MaterialSettings::addTexture(const char *name){

  texture_.push_back(name);

}
int Material::MaterialSettings::totalTextures(){
  return texture_.size();
}


std::vector<std::string> Material::MaterialSettings::getTextures(){
  return texture_;
}
const char* Material::MaterialSettings::getTextureAt(int i){
  return texture_.at(i).c_str(); 
}

