#include "CDK/material.h"

#include "CDK/task_manager.h"


Material::Material(){

}

void Material::loadShader(const char *vertex_file, const char* fragment_file, const char *geometry_shader){
  std::stringstream temp_vertex_data;
  std::stringstream temp_fragment_data;
  std::string line;

  std::ifstream file_V(vertex_file);
  if (file_V.is_open()){
    temp_vertex_data << file_V.rdbuf();
    file_V.close();
    line = temp_vertex_data.str();
    vertex_data_ = line;

  }
  std::stringstream temp_vertex_data1;
  std::stringstream temp_fragment_data1;
  std::ifstream file_V1(fragment_file);
  if (file_V1.is_open()){
    temp_vertex_data1 << file_V1.rdbuf();
    file_V1.close();
    line = temp_vertex_data1.str();
    fragment_data_ = line;
  }

  std::stringstream temp_vertex_data2;
  std::stringstream temp_fragment_data2;
  std::ifstream file_V2(geometry_shader);
  if (file_V2.is_open()){
    temp_vertex_data2 << file_V2.rdbuf();
    file_V2.close();
    line = temp_vertex_data2.str();
    geometry_data_ = line;
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

