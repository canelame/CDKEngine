#include "CDK/material.h"

#include "CDK/task_manager.h"

#include "CDK/public_opengl_library.h"
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

int Material::findUniform(const char * name){
 
  int index = 0;
  while (uniforms_names.size() > index ){
    if (uniforms_names[index] == name){   
      return  uniforms_values[index];
    }
    ++index;
  }
  //If is not at the list, we find at the 
 int position = OpenglInterfazPublic::instace().getUniformLocation(program_,(char*)name);
 if (position >= 0){
   uniforms_names.push_back(name);
   uniforms_values.push_back(position);
   return position;
 }
 return -1;
}

void Material::setUniformMat4Value(const char* uniform_name, mat4 val){
  
  OpenGlInterFaz::instance().useUniformMat4(findUniform(uniform_name), val);
}
/**
*/
void Material::setUniformMat3Value(const char* uniform_name, mat3 val){
  OpenGlInterFaz::instance().useUniformMat3(findUniform(uniform_name), val);
}
/**
*/
void Material::setUniform3fValue(const char* uniform_name, vec3 val){
  float data[3] = { val.x, val.y, val.z };
  OpenGlInterFaz::instance().useUnifor3f(findUniform(uniform_name), data);
}
void Material::setUniform3fValue(const char* uniform_name, float v1, float v2, float v3){
  float data[3] = {v1,v2,v3};
  OpenGlInterFaz::instance().useUnifor3f(findUniform(uniform_name), data);
}

void Material::setUniformUiValue(const char* uniform_name, unsigned int val){
  OpenGlInterFaz::instance().useUniformUi(findUniform(uniform_name),val);
}
/**
*/
void Material::setUniformIValue(const char* uniform_name, int val){
  OpenGlInterFaz::instance().useUniformI(findUniform(uniform_name), val);
}
/**
*/
void Material::setUniformFValue(const char* uniform_name, float val){
  OpenGlInterFaz::instance().useUniformF(findUniform(uniform_name), val);
}

int Material::getUniformLocation(const char*name){
  return findUniform(name);
}