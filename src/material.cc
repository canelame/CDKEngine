#include "material.h"
#include "stb_image.h"
void Material::add()const{}

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

int Material::runCommand()const{
  program_ = glCreateProgram();

  vertex_shader_=  glCreateShader(GL_VERTEX_SHADER);
  GLint lenght = strlen(vertex_data_);
  glShaderSource(vertex_shader_, 1, &vertex_data_,&lenght);
  compileShader(vertex_shader_);

  //FRAGENT SHADER

  fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_, 1, &fragment_data_, &lenght);
  compileShader(fragment_shader_);
  
  glLinkProgram(program_);
  GLint program_compiled;
  glGetProgramiv(program_, GL_COMPILE_STATUS, &program_compiled);
  

  if (program_compiled == GL_FALSE){
    GLchar info_log[512];
    glGetProgramInfoLog(program_, 512, NULL, info_log);
    printf("LINKED PROGRAM ERROR: %s\n", info_log);
  }
  return 0;
}


void Material::diffuse(){

}

void Material::diffuseTexture(){
  glGenTextures(1, &mat_attrib_.texture);
  glBindTexture(GL_TEXTURE_2D, mat_attrib_.texture);
  stbi_load

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