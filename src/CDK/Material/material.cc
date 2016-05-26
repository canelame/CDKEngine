#include "GL\glew.h"
#include "glm\glm.hpp"
#include "CDK/Material/material.h"
#include "CDK/Core/task_manager.h"
#include "CDK/Misc/public_opengl_library.h"
#include <string>
Material::Material(){
  uniforms_loaded_ = false;
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

Material::UniformData* Material::findUniform(const char * name){
 
  int index = 0;
  while (uniforms_.size() > index ){
    if (uniforms_[index].name_ == name){   
      if (uniforms_[index].location_ < 0){
        int loc = OpenglInterfazPublic::instace().getUniformLocation(program_,(char*)name);
        uniforms_[index].location_ = loc;
      }
      return  &uniforms_[index];
    }
    ++index;
  }
  //If is not at the list, we find at the 
 //int position = OpenglInterfazPublic::instace().getUniformLocation(program_,(char*)name);
  int i = OpenGlInterFaz::instance().getUniformIndex(program_, name);
  if (i >= 0){
   GLint num_uniforms;
   Material::UniformTypes t_u;
   std::string name;
   int location = -1;
   OpenGlInterFaz::instance().getUniformInfo(program_,i, name, location, t_u);

   Material::UniformData temp_uniform;
   temp_uniform.name_ = name;
   temp_uniform.location_ = location;
   temp_uniform.type_ = t_u;
   uniforms_.push_back(temp_uniform);
   return &uniforms_[uniforms_.size()-1];
 }
 //If is not at the opengl active uniforms, we search by name

 return nullptr;
}

void Material::setUniformMat4Value(const char* uniform_name, mat4 *val){

  UniformData * uniform_ptr = findUniform(uniform_name);
  if (uniform_ptr != nullptr){
    uniform_ptr->data_ = (val);
  }
}

void Material::setUniformMat3Value(const char* uniform_name, mat3 *val){

  UniformData * uniform_ptr = findUniform(uniform_name);
  if (uniform_ptr != nullptr){
    uniform_ptr->data_ = (val);
  }
}

void Material::setUniform3fValue(const char* uniform_name, vec3 *val){

  UniformData * uniform_ptr = findUniform(uniform_name);
  if (uniform_ptr != nullptr){
    uniform_ptr->data_ = (val);
  }

 }


void Material::setUniformUiValue(const char* uniform_name, unsigned int *val){
  UniformData * uniform_ptr = findUniform(uniform_name);
  if (uniform_ptr != nullptr){
    uniform_ptr->data_ = (val);
  }
}

void Material::setUniformIValue(const char* uniform_name, int *val){
  UniformData * uniform_ptr = findUniform(uniform_name);
  if (uniform_ptr != nullptr){
    uniform_ptr->data_ = (val);
  }
}

void Material::setUniformFValue(const char* uniform_name, float *val){
  UniformData * uniform_ptr = findUniform(uniform_name);
  if (uniform_ptr != nullptr){
    uniform_ptr->data_ = (val);
  }
}

int Material::getUniformLocation(const char*name){
  Material::UniformData *t_ud = findUniform(name);
  if (t_ud != nullptr){
    int location = t_ud->location_;
    if (location >= 0) return location;
  }
  return -1;
}
