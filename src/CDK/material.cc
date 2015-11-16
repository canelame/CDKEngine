#include "CDK/material.h"
#include "external/stb_image.h"
#include "CDK/task_manager.h"


Material::Material(TYPE t, std::shared_ptr<TaskManager>tk){

  interfaz_ = new OpenGlInterFaz();
  is_compiled_ = false;
  
  if (t == 0){
    
    tk.get()->addTask(std::make_shared<ReadFile>("shaders/diffuse_v.glsl", vertex_data_));
    tk.get()->addTask(std::make_shared<ReadFile>("shaders/diffuse_f.glsl", fragment_data_));
  
  }
  else{
    tk.get()->addTask(std::make_shared<ReadFile>("shaders/texture_v.glsl",vertex_data_));
    tk.get()->addTask(std::make_shared<ReadFile>("shaders/texture_f.glsl", fragment_data_));
  }
;}

void Material::loadShader(const char *vertex_file, const char* fragment_file){

  vertex_data_ = vertex_file;
  fragment_data_ = fragment_file;
	
}

void Material::runCommand(OpenGlInterFaz &i)const{
 
}



GLuint Material::getProgram(){
  return program_; 
}



std::string Material::getFragmentData(){ 
  return fragment_data_;
}
std::string Material::getVertexData(){ 
  return vertex_data_; 
}

void Material::setTexture(std::shared_ptr<Texture>tx){
   texture_=tx;

}