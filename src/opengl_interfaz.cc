#include "opengl_interfaz.h"


void OpenGlInterFaz::loadBuffer(std::vector<float> attributes[3], std::vector<unsigned int> &index){
  shadow_attrib_[0] = attributes[0];
  shadow_attrib_[1] = attributes[1];
  shadow_attrib_[2] = attributes[2];
  shadow_index_ = index;
  glGenVertexArrays(1, &shadow_vao_);
  glBindVertexArray(shadow_vao_);

		glGenBuffers(4, shadow_vbo_);
		//Load positions
    glBindBuffer(GL_ARRAY_BUFFER, shadow_vbo_[0]);
    glBufferData(GL_ARRAY_BUFFER, shadow_attrib_[0].size()*sizeof(float), &shadow_attrib_[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//Load normals
    glBindBuffer(GL_ARRAY_BUFFER, shadow_vbo_[1]);
    glBufferData(GL_ARRAY_BUFFER, shadow_attrib_[1].size()*sizeof(float), &shadow_attrib_[1], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glEnableVertexAttribArray(1);
		//Load uvs
    glBindBuffer(GL_ARRAY_BUFFER, shadow_vbo_[2]);
    glBufferData(GL_ARRAY_BUFFER, shadow_attrib_[2].size()*sizeof(float), &shadow_attrib_[2], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
		//Indexes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shadow_vbo_[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shadow_index_.size()*sizeof(unsigned int), &shadow_index_, GL_STATIC_DRAW);
		
		glBindVertexArray(0);	
    glBindVertexArray(shadow_vao_);
}

void OpenGlInterFaz::useGeometry(){
  glBindVertexArray(shadow_vao_);
}
void OpenGlInterFaz::useMaterial(){

  glUseProgram(shadow_program_);
}
void OpenGlInterFaz::loadMaterial(const char*vertex_data, const char*fragment_data){

  shadow_program_ = glCreateProgram();

  shadow_vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  GLint lenght = strlen(vertex_data);
  glShaderSource(shadow_vertex_shader_, 1, &vertex_data, &lenght);
  compileShader(shadow_vertex_shader_);

  //FRAGENT SHADER

  shadow_fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shadow_fragment_shader_, 1, &fragment_data, &lenght);
  compileShader(shadow_fragment_shader_);

  glLinkProgram(shadow_program_);
  GLint program_compiled;
  glGetProgramiv(shadow_program_, GL_COMPILE_STATUS, &program_compiled);


  if (program_compiled == GL_FALSE){
    GLchar info_log[512];
    glGetProgramInfoLog(shadow_program_, 512, NULL, info_log);
    printf("LINKED PROGRAM ERROR: %s\n", info_log);
   
  }

}

void OpenGlInterFaz::useDrawGeometry(){
	glDrawElements(GL_TRIANGLES, shadow_index_.size(),GL_UNSIGNED_INT, &shadow_index_[0]);
}

void OpenGlInterFaz::compileShader(GLuint shader){
  glCompileShader(shader);

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
