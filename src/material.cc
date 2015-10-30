#include "material.h"
#include "stb_image.h"


Material::Material(TYPE t){
  interfaz_ = new OpenGlInterFaz();
  is_compiled_ = false;
  texture_ = std::make_unique<Texture>();
  if (t == 0){
    loadShader("shaders/diffuse_v.glsl", "shaders/diffuse_f.glsl");
  }
  else{
    loadShader("shaders/texture_v.glsl", "shaders/texture_f.glsl");
    is_texture_ = true;
  }
};

void Material::loadShader(const char *vertex_file, const char* fragment_file){

  std::stringstream temp_vertex_data;
  std::stringstream temp_fragment_data;
  std::string line;

  std::ifstream file_V(vertex_file);
  if (file_V.is_open()){
    temp_vertex_data << file_V.rdbuf();
    file_V.close();
    line = temp_vertex_data.str();
    vertex_data_ = line.c_str();
  }

  line.clear();
  temp_vertex_data.clear();

  std::ifstream file_F(fragment_file);
  if (file_F.is_open()){
	  temp_fragment_data << file_F.rdbuf();
    file_F.close();
	line = temp_fragment_data.str();
    fragment_data_ = line.c_str();
  }
  


}

void Material::runCommand(OpenGlInterFaz &i)const{
  if (!is_compiled_){

    i.loadMaterial(vertex_data_.c_str(), fragment_data_.c_str());
	  is_compiled_ = true;
  }
  if (is_texture_){
    if (!texture_.get()->getLoaded()){
      i.loadTexture(texture_name_.c_str());
      texture_.get()->setLoaded(true);
    } else{
      i.useTexture();
    }
  }
  i.useMaterial( );

  
 
}



GLuint Material::getProgram(){ return program_; }

void Material::loadTexture(const char*file_name){
  texture_name_ = file_name;
}