#include "CDK/opengl_interfaz.h"
#include "CDK/display_list.h"
#include "CDK/material.h"
struct OpenGlInterFaz::Data{
   GLuint shadow_texture_;
  //For materials
  GLuint shadow_program_;
  GLuint shadow_vertex_shader_;
  GLuint shadow_fragment_shader_;
  GLint mat_d = -1;
  GLint mat_s= -1;
  GLint mat_a = -1;

  //For geometries
  GLuint shadow_vao_;
  GLuint shadow_vbo_v_;
  GLuint shadow_vbo_i_;
  //For lights
  GLint l_pos=-1;
  GLint l_ac = -1;
  GLint l_sc = -1;
  GLint l_dc = -1;
  GLint l_sh = -1;
  GLint l_t = -1;
  GLint proyec_pos = -1;
  GLint model_pos = -1;
  GLint view_pos = -1;
  };

OpenGlInterFaz::OpenGlInterFaz(){
  data_ = new Data;


};

void OpenGlInterFaz::loadBuffer(std::shared_ptr<Buffer>buff){


  GLint position_size =buff->vertexSize() * sizeof(float);
  GLint normal_size = buff->normalSize() * sizeof(float);
  GLint uv_size = buff->uvSize() * sizeof(float);
  GLint tan_size = buff->tangentSize()*sizeof(float);
  GLint bitan_size = buff->bitangentSize() * sizeof(float);
  GLint index_size = buff->indiceSize() * sizeof(unsigned int);


  glGenVertexArrays(1, &data_->shadow_vao_);
  glGenBuffers(1, &data_->shadow_vbo_v_);
  glGenBuffers(1, &data_->shadow_vbo_i_);

  glBindVertexArray(data_->shadow_vao_);
  glBindBuffer(GL_ARRAY_BUFFER, data_->shadow_vbo_v_);

  glBufferData(GL_ARRAY_BUFFER, position_size+normal_size+uv_size, NULL, GL_STATIC_DRAW);
 
    //Load positions

     glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, &buff->getData()[0]);

  //Load normals
     int a = strlen(buff->getData());
    glBufferSubData(GL_ARRAY_BUFFER, position_size, normal_size, &buff->getData()[position_size]);
    glBufferSubData(GL_ARRAY_BUFFER, position_size+normal_size, uv_size, &buff->getData()[position_size+normal_size]);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data_->shadow_vbo_i_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, &buff->getData()[position_size + normal_size+uv_size+tan_size+bitan_size], GL_STATIC_DRAW);
  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),0);
    glEnableVertexAttribArray(0);
  
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)position_size);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(position_size+normal_size));
    glEnableVertexAttribArray(2);

	  glBindVertexArray(0);	
    glDeleteBuffers(1, &data_->shadow_vbo_i_);
    glDeleteBuffers(1, &data_->shadow_vbo_v_);
    buff->setVAO(data_->shadow_vao_);
}

void OpenGlInterFaz::useGeometry(GLuint vao){
  glBindVertexArray(vao);
}
void OpenGlInterFaz::useMaterial( Material &mat,vec3 color_amb, vec3 color_diff, vec3 color_spe){
  //printf("Using program:%d", shadow_program_);
  glUseProgram(mat.getProgram());
  glUniform3f(data_->mat_a, color_amb.x, color_amb.y, color_amb.z);
  glUniform3f(data_->mat_d, color_diff.x, color_diff.y, color_diff.z);
  glUniform3f(data_->mat_s, color_spe.x, color_spe.y, color_spe.z);


 
}
int OpenGlInterFaz::loadMaterial(const char*vertex_data, const char*fragment_data){

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

    if (data_->proyec_pos<0)data_->proyec_pos = glGetUniformLocation(data_->shadow_program_, "u_projection_m");
    if (data_->model_pos<0)data_->model_pos = glGetUniformLocation(data_->shadow_program_, "u_model_m");
    if (data_->view_pos<0)data_->view_pos = glGetUniformLocation(data_->shadow_program_, "u_view_m");

    if (data_->mat_d<0)data_->mat_d = glGetUniformLocation(data_->shadow_program_, "u_material_diff");
    if (data_->mat_s<0)data_->mat_s = glGetUniformLocation(data_->shadow_program_, "u_material_specular");
    if (data_->mat_a<0)data_->mat_a = glGetUniformLocation(data_->shadow_program_, "u_material_ambient");
    return data_->shadow_program_;
  }

}

void OpenGlInterFaz::drawGeometry(unsigned int indices){
 // printf("Draw elements: %d indices\n",shadow_index_.size());
	glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, (void*)0);

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
    glUniform1iv(data_->shadow_program_, 1, t);
  }
}

void OpenGlInterFaz::loadCamera(){

}

void OpenGlInterFaz::useCamera(mat4 proyection, mat4 model, mat4 view){
  
  

  if (data_->proyec_pos >= 0){
    glUniformMatrix4fv(data_->proyec_pos, 1, GL_FALSE, glm::value_ptr(proyection));
  }

  
  if (data_->model_pos >= 0){
    glUniformMatrix4fv(data_->model_pos, 1, GL_FALSE, glm::value_ptr(model));
  }

  
  if (data_->view_pos >= 0){
    glUniformMatrix4fv(data_->view_pos, 1, GL_FALSE, glm::value_ptr(view));
  }

}
void OpenGlInterFaz::loadTexture(std::shared_ptr<Texture> m){

    
    glGenTextures(1, &data_->shadow_texture_);
    glBindTexture(GL_TEXTURE_2D, data_->shadow_texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int w = m->getWidth();
    int h = m->getHeigth();
    unsigned char * d = m->getData();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,
									h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                  d);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
		m->setID(data_->shadow_texture_);
    
}

void OpenGlInterFaz::useTexture(int pro,int n_text,std::string u_name,int texture_id){
  glActiveTexture(GL_TEXTURE0 + n_text);

  //int tex_i = glGetUniformLocation(pro,u_name.c_str());
  GLuint i = texture_id;
  glBindTexture(GL_TEXTURE_2D, i);
}

void OpenGlInterFaz::loadLight(int num_light){
  if (data_->l_pos<0)data_->l_pos = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].position").c_str());
  if (data_->l_ac<0)data_->l_ac = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].ambient_color").c_str());
  if (data_->l_sc<0)data_->l_sc = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].specular_color").c_str());
  if (data_->l_dc<0)data_->l_dc = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].diffuse_color").c_str());
  if (data_->l_sh<0)data_->l_sh = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].sh").c_str());
  if (data_->l_t<0)data_->l_t = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].type").c_str());
}
void OpenGlInterFaz::createFrameBuffer(){

}
void OpenGlInterFaz::sendLight( Light *light){
  vec3 position = light->getPosition();
  vec3 diffuse_c = light->getDiffuseColor();
  vec3 specular_c = light->getSpecularColor();
  vec3 ambient_c = light->getDiffuseColor();
  float shin = light->getShinenes();
  int type = light->getType();
 
   if (data_->l_pos >= 0){
     glUniform3f(data_->l_pos, position.x, position.y, position.z);
  }
   
   
  if (data_->l_ac >= 0){
    glUniform3f(data_->l_ac, ambient_c.x, ambient_c.y, ambient_c.z);
  }

  
  if (data_->l_sc >= 0){

glUniform3f(data_->l_sc, specular_c.x, specular_c.y, specular_c.z);
  }

  
  if (data_->l_dc >= 0){
    glUniform3f(data_->l_dc, diffuse_c.x, diffuse_c.y, diffuse_c.z);
  }

 
  if (data_->l_sh >= 0){
    glUniform1f(data_->l_sh, shin);
  }

 
  if (data_->l_t >= 0){
    glUniform1i(data_->l_t, type);
  }


}