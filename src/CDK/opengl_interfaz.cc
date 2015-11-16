#include "CDK/opengl_interfaz.h"

struct OpenGlInterFaz::Data{
   GLuint shadow_texture_;
  //For materials
  GLuint shadow_program_;
  GLuint shadow_vertex_shader_;
  GLuint shadow_fragment_shader_;

  //For geometries
  GLuint shadow_vao_;
  GLuint shadow_vbo_v_;
  GLuint shadow_vbo_i_;
  std::vector<std::vector<float>> shadow_attrib_;
  std::vector<unsigned int > shadow_index_;

  };

OpenGlInterFaz::OpenGlInterFaz(){
  data_ = new Data;
};

void OpenGlInterFaz::loadBuffer(std::shared_ptr<Buffer>buff){
  std::vector<float> temp_p, temp_n, temp_uv;
  data_->shadow_attrib_ = buff->getAttributes();
  data_->shadow_index_ = buff->getIndexes();

  GLint postion_size = data_->shadow_attrib_[0].size()*sizeof(float);
  GLint normal_size = data_->shadow_attrib_[1].size()*sizeof(float);
  GLint uv_size = data_->shadow_attrib_[2].size()* sizeof(float);
  GLint index_size = data_->shadow_index_.size()*sizeof(unsigned int);

  temp_p = data_->shadow_attrib_[0];
  temp_n = data_->shadow_attrib_[1];
  temp_uv = data_->shadow_attrib_[2];

  glGenVertexArrays(1, &data_->shadow_vao_);
  glGenBuffers(1, &data_->shadow_vbo_v_);
  glGenBuffers(1, &data_->shadow_vbo_i_);

  glBindVertexArray(data_->shadow_vao_);
  glBindBuffer(GL_ARRAY_BUFFER, data_->shadow_vbo_v_);

 // glBufferData(GL_ARRAY_BUFFER, postion_size,&temp_p[0], GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, postion_size+normal_size+uv_size, NULL, GL_STATIC_DRAW);
 // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*temp_p.size(), &temp_p[0]);
    //Load positions
  if (temp_p.size() != 0){
     glBufferSubData(GL_ARRAY_BUFFER, 0, postion_size, &temp_p[0]);

  }
  //Load normals
  if (temp_n.size() != 0){
    glBufferSubData(GL_ARRAY_BUFFER, postion_size,normal_size, &temp_n[0]);
    
  }

  if (temp_uv.size() != 0){
    glBufferSubData(GL_ARRAY_BUFFER, postion_size+normal_size, uv_size, &temp_uv[0]);

  }
  //Load uvs
  if (temp_uv.size() != 0){
    glBufferSubData(GL_ARRAY_BUFFER, postion_size+normal_size,uv_size , &temp_uv[0]);
  }
		
  if (data_->shadow_index_.size() != 0){
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->shadow_vbo_i_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_->shadow_index_.size()*sizeof(unsigned int), &data_->shadow_index_[0], GL_STATIC_DRAW);
  }
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)postion_size);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(postion_size+normal_size));
  glEnableVertexAttribArray(2);

	glBindVertexArray(0);	
  glDeleteBuffers(1, &data_->shadow_vbo_i_);
  glDeleteBuffers(1, &data_->shadow_vbo_v_);
  buff->setVAO(data_->shadow_vao_);
}

void OpenGlInterFaz::useGeometry(GLuint vao){
  glBindVertexArray(vao);;
}
void OpenGlInterFaz::useMaterial(){
  //printf("Using program:%d", shadow_program_);
  glUseProgram(data_->shadow_program_);

 
}
void OpenGlInterFaz::loadMaterial(const char*vertex_data, const char*fragment_data){

  data_->shadow_program_ = glCreateProgram();

  data_->shadow_vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  GLint lenght = strlen(vertex_data);
  glShaderSource(data_->shadow_vertex_shader_, 1, &vertex_data, &lenght);
  compileShader(data_->shadow_vertex_shader_);

  //FRAGENT SHADER
  lenght = strlen(fragment_data);
  data_->shadow_fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(data_->shadow_fragment_shader_, 1, &fragment_data, &lenght);
  compileShader(data_->shadow_fragment_shader_);

  glAttachShader(data_->shadow_program_, data_->shadow_vertex_shader_);
  glAttachShader(data_->shadow_program_, data_->shadow_fragment_shader_);

  glLinkProgram(data_->shadow_program_);
  GLint program_compiled;
  glGetProgramiv(data_->shadow_program_, GL_LINK_STATUS, &program_compiled);


  if (program_compiled == GL_FALSE){
    GLchar info_log[512];
    glGetProgramInfoLog(data_->shadow_program_, 512, NULL, info_log);
    printf("LINKED PROGRAM ERROR: %s\n", info_log);
   
  }
  else{ 
    glDeleteShader(data_->shadow_vertex_shader_);
    glDeleteShader(data_->shadow_fragment_shader_);
    printf("PROGRAM LINKED");
  }

}

void OpenGlInterFaz::drawGeometry(std::vector<unsigned int> indices){
 // printf("Draw elements: %d indices\n",shadow_index_.size());
 

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
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
  GLint pos = glGetUniformLocation(data_->shadow_program_, name);
	if (pos >= 0){
		glUniform3fv(pos, 1, data);
	}
}

void OpenGlInterFaz::useUniformMat4(const char* name,const float *m_data){

  GLint pos = glGetUniformLocation(data_->shadow_program_, name);
	if (pos >= 0){
		glUniformMatrix4fv(pos, 1, GL_FALSE, m_data);
	}

}

void OpenGlInterFaz::useUniformUi(const char *name, int value){
  int p = glGetUniformLocation(data_->shadow_program_, name);
  const int t = { 0 };
  if (p >= 0){
  //  glUniform1iv(data_->shadow_program_, 1, t);
  }
}

void OpenGlInterFaz::loadTexture(std::shared_ptr<Material> m){

    
    glGenTextures(1, &data_->shadow_texture_);
    glBindTexture(GL_TEXTURE_2D, data_->shadow_texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m->getTexture()->getWidth(),
									m->getTexture()->getHeigth(), 0, GL_RGB, GL_UNSIGNED_BYTE,m->getTexture()->getData() );
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
		m->getTexture()->setID(data_->shadow_texture_);
}

void OpenGlInterFaz::useTexture(std::shared_ptr<Material>m){
  int tex_i = glGetUniformLocation(m->getProgram(), "u_texture");
  glActiveTexture(GL_TEXTURE0 + tex_i);
  glBindTexture(GL_TEXTURE_2D, m->getTexture()->getID());
}