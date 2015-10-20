#include "material.h"
#include "stb_image.h"


Material::Material(TYPE t){
  t == 0 ? diffuse() : diffuseTexture();
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
 
 
}


void Material::diffuse(){

}

void Material::diffuseTexture(){
  glGenTextures(1, &mat_attrib_.texture);
  glBindTexture(GL_TEXTURE_2D, mat_attrib_.texture);


}

void Material::compileShader(GLuint shader)const{
  glCompileShader(vertex_shader_);

  GLint is_compiled;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE){
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    GLint shader_type;
    glGetShaderiv(shader, GL_SHADER_TYPE, &shader_type);
    switch (shader_type)
    {
    default:
    case GL_VERTEX_SHADER:
      printf("VERTEX SHADER COMPILED ERROR: %s", infoLog);
      break;
    case GL_FRAGMENT_SHADER:
      printf("FRAGMENT SHADER COMPILED ERROR: %s", infoLog);
    }
    
  }
}

GLuint Material::getProgram(){ return program_; }