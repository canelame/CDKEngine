#include "opengl_interfaz.h"


void OpenGlInterFaz::loadBuffer(std::vector<std::vector<float>> attributes, std::vector<unsigned int> &index){
  std::vector<float> temp_p, temp_n, temp_uv;
  
 shadow_attrib_[0]= temp_p = attributes[0];
 shadow_attrib_[1]= temp_n = attributes[1];
 shadow_attrib_[2] =temp_uv = attributes[2];
  shadow_index_ = index;

  GLint postion_size = temp_p.size()*sizeof(float);
  GLint normal_size = temp_n.size()*sizeof(float);
  GLint uv_size = temp_uv.size()*sizeof(float);
  GLint index_size = shadow_index_.size()*sizeof(unsigned int);


  glGenVertexArrays(1, &shadow_vao_);
  glGenBuffers(1, &shadow_vbo_v_);
  glGenBuffers(1, &shadow_vbo_i_);

  glBindVertexArray(shadow_vao_);
  glBindBuffer(GL_ARRAY_BUFFER, shadow_vbo_v_);

 // glBufferData(GL_ARRAY_BUFFER, postion_size,&temp_p[0], GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, postion_size+normal_size+uv_size, NULL, GL_STATIC_DRAW);
 // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*temp_p.size(), &temp_p[0]);
    //Load positions
  if (temp_p.size() != 0){
     glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*temp_p.size(), &temp_p[0]);

  }
  //Load normals
  if (temp_n.size() != 0){
    glBufferSubData(GL_ARRAY_BUFFER, postion_size,normal_size, &temp_n[0]);
    
  }

  //Load uvs
  if (temp_uv.size() != 0){
    glBufferSubData(GL_ARRAY_BUFFER, postion_size+normal_size,uv_size , &temp_uv[0]);
  }
		
  if (shadow_index_.size() != 0){
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shadow_vbo_i_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shadow_index_.size()*sizeof(unsigned int), &shadow_index_[0], GL_STATIC_DRAW);
  }
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)postion_size);
  glEnableVertexAttribArray(1);
	glBindVertexArray(0);	
    
}

void OpenGlInterFaz::useGeometry(){
  glBindVertexArray(shadow_vao_);
}
void OpenGlInterFaz::useMaterial(){
  //printf("Using program:%d", shadow_program_);
   glUseProgram(shadow_program_);
 
}
void OpenGlInterFaz::loadMaterial(const char*vertex_data, const char*fragment_data){

  shadow_program_ = glCreateProgram();

  shadow_vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  GLint lenght = strlen(vertex_data);
  glShaderSource(shadow_vertex_shader_, 1, &vertex_data, &lenght);
  compileShader(shadow_vertex_shader_);

  //FRAGENT SHADER
  lenght = strlen(fragment_data);
  shadow_fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shadow_fragment_shader_, 1, &fragment_data, &lenght);
  compileShader(shadow_fragment_shader_);

  glAttachShader(shadow_program_, shadow_vertex_shader_);
  glAttachShader(shadow_program_, shadow_fragment_shader_);

  glLinkProgram(shadow_program_);
  GLint program_compiled;
  glGetProgramiv(shadow_program_, GL_LINK_STATUS, &program_compiled);


  if (program_compiled == GL_FALSE){
    GLchar info_log[512];
    glGetProgramInfoLog(shadow_program_, 512, NULL, info_log);
    printf("LINKED PROGRAM ERROR: %s\n", info_log);
   
  }
  else{ printf("PROGRAM LINKED"); }

}

void OpenGlInterFaz::useDrawGeometry(){
 // printf("Draw elements: %d indices\n",shadow_index_.size());
	glDrawElements(GL_TRIANGLES, shadow_index_.size(),GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
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


void OpenGlInterFaz::useUnifor3f(const char* name, const float*data){
	GLint pos = glGetUniformLocation(shadow_program_, name);
	if (pos >= 0){
		glUniform3fv(pos, 1, data);
	}
}

void OpenGlInterFaz::useUniformMat4(const char* name,const float *m_data){

	GLint pos = glGetUniformLocation(shadow_program_, name);
	if (pos >= 0){
		glUniformMatrix4fv(pos, 1, GL_FALSE, m_data);
	}

}