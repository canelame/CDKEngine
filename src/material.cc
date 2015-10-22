#include "material.h"
#include "stb_image.h"


Material::Material(TYPE t){
  interfaz_ = new OpenGlInterFaz();
  is_compiled_ = false;
  
  t == 0 ? loadShader("../../shaders/diffuse_v.glsl","shaders/diffuse_f.glsl") : loadShader("texture_v.glsl","texture_f.glsl");
};

void Material::loadShader(const char *vertex_file, const char* fragment_file){

  std::stringstream temp_vertex_data;
  std::string line;

  std::ifstream file_V(vertex_file);
  if (file_V.is_open()){
    temp_vertex_data << file_V.rdbuf();
    file_V.close();
    line = temp_vertex_data.str();
    vertex_data_ = line.c_str();
  }
  
  std::ifstream file_F(vertex_file);
  if (file_F.is_open()){
    temp_vertex_data << file_F.rdbuf();
    file_F.close();
    line = temp_vertex_data.str();
    fragment_data_ = line.c_str();
  }
  


}

void Material::runCommand()const{
  if (!is_compiled_){

    interfaz_->loadMaterial(vertex_data_, fragment_data_);
  }
  interfaz_->useMaterial( );
 
}



GLuint Material::getProgram(){ return program_; }