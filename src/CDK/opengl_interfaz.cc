#include "CDK/opengl_interfaz.h"
#include "CDK/display_list.h"
#include "CDK/material.h"
#include "CDK/texture.h"

OpenGlInterFaz* OpenGlInterFaz::instance_ = nullptr;
OpenGlInterFaz& OpenGlInterFaz::instance(){
  if (instance_ == NULL){
    instance_ = new OpenGlInterFaz();
  }
  return *instance_;
}

struct LightUniforms{

  GLint l_pos = -1;
  GLint l_ac = -1;
  GLint l_sc = -1;
  GLint l_dc = -1;
  GLint l_sh = -1;
  GLint l_t = -1;
};
struct OpenGlInterFaz::Data{
   GLuint shadow_texture_;

  //For geometries
  GLuint shadow_vao_;
  GLuint shadow_vbo_v_;
  GLuint shadow_vbo_i_;
  //For materials
  GLuint shadow_program_;
  GLuint shadow_vertex_shader_;
  GLuint shadow_fragment_shader_;

  GLint mat_d = -1;
  GLint mat_s = -1;
  GLint mat_a = -1;
  //Lights
  LightUniforms u_lights[10];
  //Camera
  GLint proyec_pos = -1;
  GLint model_pos = -1;
  GLint view_pos = -1;
  //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  GLint mat_d_d = -1;
  GLint mat_s_d = -1;
  GLint mat_a_d = -1;
  LightUniforms u_lights_d[10];

  GLint proyec_pos_d = -1;
  GLint model_pos_d = -1;
  GLint view_pos_d = -1;
  //FrameBuffer
  GLuint shadow_frame_buffer;
  GLuint shadow_fbo_;//FrameBufferObject
  GLuint shadow_texture_frame_buffer;
  GLuint type;

  ///Shadows
  GLint shadow_map_texture;
  GLint shadow_model_= -1;
  GLint light_space_ = -1;
  };

OpenGlInterFaz::OpenGlInterFaz(){
  data_ = new Data;
};

void OpenGlInterFaz::loadBuffer(Buffer *buff){

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
 
}
void OpenGlInterFaz::useMaterial( Material &mat,vec3 color_amb, vec3 color_diff, vec3 color_spe){
  data_->type = mat.type_;
    glUseProgram(mat.getProgram());
    if (mat.type_ == 0){
      if (data_->mat_a > -1)glUniform3f(data_->mat_a, color_amb.x, color_amb.y, color_amb.z);
      if (data_->mat_d > -1) glUniform3f(data_->mat_d, color_diff.x, color_diff.y, color_diff.z);
      if (data_->mat_s > -1)glUniform3f(data_->mat_s, color_spe.x, color_spe.y, color_spe.z);
    }
    if (mat.type_ == 1){
      if (data_->mat_a_d > -1)glUniform3f(data_->mat_a_d, color_amb.x, color_amb.y, color_amb.z);
      if (data_->mat_d_d > -1)glUniform3f(data_->mat_d_d, color_diff.x, color_diff.y, color_diff.z);
      if (data_->mat_s_d > -1)glUniform3f(data_->mat_s_d, color_spe.x, color_spe.y, color_spe.z);
    }
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
    //TEXTURE_UNIFORMS
    if (data_->proyec_pos<0)data_->proyec_pos = glGetUniformLocation(data_->shadow_program_, "u_projection_m");
    if (data_->model_pos<0)data_->model_pos = glGetUniformLocation(data_->shadow_program_, "u_model_m");
    if (data_->view_pos<0)data_->view_pos = glGetUniformLocation(data_->shadow_program_, "u_view_m");

    if (data_->mat_d<0)data_->mat_d = glGetUniformLocation(data_->shadow_program_, "u_material_diff");
    if (data_->mat_s<0)data_->mat_s = glGetUniformLocation(data_->shadow_program_, "u_material_specular");
    if (data_->mat_a<0)data_->mat_a = glGetUniformLocation(data_->shadow_program_, "u_material_ambient");
    //DIFFUSE UNIFORMS
    if (data_->proyec_pos_d<0)data_->proyec_pos_d = glGetUniformLocation(data_->shadow_program_, "u_projection_m_d");
    if (data_->model_pos_d<0)data_->model_pos_d = glGetUniformLocation(data_->shadow_program_, "u_model_m_d");
    if (data_->view_pos_d<0)data_->view_pos_d = glGetUniformLocation(data_->shadow_program_, "u_view_m_d");

    if (data_->mat_d_d<0)data_->mat_d_d = glGetUniformLocation(data_->shadow_program_, "u_material_diff_d");
    if (data_->mat_s_d<0)data_->mat_s_d = glGetUniformLocation(data_->shadow_program_, "u_material_specular_d");
    if (data_->mat_a_d<0)data_->mat_a_d = glGetUniformLocation(data_->shadow_program_, "u_material_ambient_d");
    //SHADOWS
    if (data_->shadow_model_<0)data_->shadow_model_ = glGetUniformLocation(data_->shadow_program_, "u_model");
    if (data_->light_space_<0)data_->light_space_ = glGetUniformLocation(data_->shadow_program_, "light_screen");
    return data_->shadow_program_;
  }

}

void OpenGlInterFaz::drawGeometry( int vao,unsigned int indices){
 // printf("Draw elements: %d indices\n",shadow_index_.size());
  glBindVertexArray(vao);
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

void OpenGlInterFaz::useUniformMat4(mat4 m){

  glUniformMatrix4fv(data_->shadow_model_, 1, GL_FALSE, &m[0][0]);

}

void OpenGlInterFaz::useUniformUi(const char *name, int value){
  int p = glGetUniformLocation(data_->shadow_program_, name);
  const int t = { 0 };
  if (p >= 0){
    glUniform1iv(data_->shadow_program_, 1, t);
  }
}


void OpenGlInterFaz::bindFrameBuffer(int fb_id,FrameBuffer::kFramebufferBindType type){
  GLenum type_binding;
  switch (type)
  {
  case FrameBuffer::kFramebufferBindType_FrameBuffer:
    type_binding = GL_FRAMEBUFFER;
    break;
  case FrameBuffer::kFramebufferBindType_Draw:
    type_binding = GL_DRAW_FRAMEBUFFER;
    break;
  case FrameBuffer::kFramebufferBindType_Read:
    type_binding = GL_READ_FRAMEBUFFER;
    break;
  case FrameBuffer::kFramebufferBindType_None:
    type_binding = GL_NONE;
    break;
  default:
    type_binding = GL_FRAMEBUFFER;
    break;
  }
  glBindFramebuffer(type_binding,fb_id);

}

void OpenGlInterFaz::useCamera(mat4 proyection, mat4 model, mat4 view){
  
  if (data_->type == 0){
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

  if (data_->type == 1){
    //DIFFUSe
    if (data_->proyec_pos_d >= 0){
      glUniformMatrix4fv(data_->proyec_pos_d, 1, GL_FALSE, glm::value_ptr(proyection));

    }


    if (data_->model_pos_d >= 0){
      glUniformMatrix4fv(data_->model_pos_d, 1, GL_FALSE, glm::value_ptr(model));
    }


    if (data_->view_pos_d >= 0){
      glUniformMatrix4fv(data_->view_pos_d, 1, GL_FALSE, glm::value_ptr(view));
    }
  }
}
#include "CDK/engine_manager.h"
void OpenGlInterFaz::loadTexture(std::shared_ptr<Texture> m){

    
  int mag_filter = m->getMagFilter();
  int min_filter = m->getMinFilter();

  int s_wrap = m->getWrapCoordinateS();
  int t_wrap = m->getWrapCoordinateT();

  glGenTextures(1, &data_->shadow_texture_);
  glBindTexture(GL_TEXTURE_2D, data_->shadow_texture_);

  switch (mag_filter)
  {
  case 0:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    break;
  case 1:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    break;
  default:
    break;
  }

  switch (min_filter)
  {
  case 0:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    break;
  case 1:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    break;

  }

  switch (t_wrap)
  {
  case 0:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    break;
  case 1:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    break;
  case 2:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    break;
  case 3:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    break;
  default:
    break;
  }

  switch (s_wrap)
  {
  case 0:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    break;
  case 1:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    break;
  case 2:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    break;
  case 3:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    break;
  default:
    break;
  }

  Texture::kTextureFormat format = m->getFormat();
  GLenum t_format;
  switch (format)
  {
  case Texture::kTextureFormat_Rgb:
    t_format = GL_RGB;
    break;
  case Texture::kTextureFormat_Rgba:
    t_format = GL_RGBA;
    break;
  case Texture::kTextureFormat_Depth:
    t_format = GL_DEPTH_COMPONENT;
    break;
  case Texture::kTextureFormat_Depth_Stencil:
    t_format = GL_DEPTH_STENCIL;
    break;
  default:
    t_format = GL_RGBA;
    break;
  }
  Texture::kTexturePixelType pixel_t = m->getPixelType();
  GLenum pixel_type;
  switch (pixel_t)
  {
  case Texture::kTexturePixelType_UByte:
    pixel_type = GL_UNSIGNED_BYTE;
    break;
  case Texture::kTexturePixelType_Byte:
    pixel_type = GL_BYTE;
    break;
  case Texture::kTexturePixelType_UInt:
    pixel_type = GL_UNSIGNED_INT;
    break;
  case Texture::kTexturePixelType_Int:
    pixel_type = GL_INT;
    break;
  case Texture::kTexturePixelType_Float:
    pixel_type = GL_FLOAT;
    break;
  default:
    pixel_type = GL_UNSIGNED_BYTE;
    break;
  }

  if (strcmp(m->getType(), "fb") == 0){

    glTexImage2D(GL_TEXTURE_2D, 0, t_format,1024,
      1024, 0, t_format, pixel_type, NULL);
  
  }
  else{
    int w = m->getWidth();
    int h = m->getHeigth();
    unsigned char * d = m->getData();
    glTexImage2D(GL_TEXTURE_2D, 0, t_format, w,
      h, 0, t_format, pixel_type,
      d);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  m->setID(data_->shadow_texture_);
    
}

void OpenGlInterFaz::useTexture(int pro,int n_text,std::string u_name,int texture_id){
 
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id);  
}

void OpenGlInterFaz::loadLight(int num_light){

    if (data_->u_lights[num_light].l_pos < 0)data_->u_lights[num_light].l_pos = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].position").c_str());
    if (data_->u_lights[num_light].l_ac < 0)data_->u_lights[num_light].l_ac = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].ambient_color").c_str());
    if (data_->u_lights[num_light].l_sc < 0)data_->u_lights[num_light].l_sc = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].specular_color").c_str());
    if (data_->u_lights[num_light].l_dc < 0)data_->u_lights[num_light].l_dc = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].diffuse_color").c_str());
    if (data_->u_lights[num_light].l_sh < 0)data_->u_lights[num_light].l_sh = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].sh").c_str());
    if (data_->u_lights[num_light].l_t < 0)data_->u_lights[num_light].l_t = glGetUniformLocation(data_->shadow_program_, ("lights[" + std::to_string(num_light) + "].type").c_str());
    //DIFFUSE
    if (data_->u_lights_d[num_light].l_pos < 0)data_->u_lights_d[num_light].l_pos = glGetUniformLocation(data_->shadow_program_, ("lights_d[" + std::to_string(num_light) + "].position").c_str());
    if (data_->u_lights_d[num_light].l_ac < 0)data_->u_lights_d[num_light].l_ac = glGetUniformLocation(data_->shadow_program_, ("lights_d[" + std::to_string(num_light) + "].ambient_color").c_str());
    if (data_->u_lights_d[num_light].l_sc < 0)data_->u_lights_d[num_light].l_sc = glGetUniformLocation(data_->shadow_program_, ("lights_d[" + std::to_string(num_light) + "].specular_color").c_str());
    if (data_->u_lights_d[num_light].l_dc < 0)data_->u_lights_d[num_light].l_dc = glGetUniformLocation(data_->shadow_program_, ("lights_d[" + std::to_string(num_light) + "].diffuse_color").c_str());
    if (data_->u_lights_d[num_light].l_sh < 0)data_->u_lights_d[num_light].l_sh = glGetUniformLocation(data_->shadow_program_, ("lights_d[" + std::to_string(num_light) + "].sh").c_str());
    if (data_->u_lights_d[num_light].l_t < 0)data_->u_lights_d[num_light].l_t = glGetUniformLocation(data_->shadow_program_, ("lights_d[" + std::to_string(num_light) + "].type").c_str());
  
}
void OpenGlInterFaz::createFrameBuffer(FrameBuffer &fb,bool use_render_buffer){

  //Create Program for frameBuffer

  loadTexture(fb.getTexture());
  FrameBuffer::kFrameBufferAttachment attachment = fb.getAttachment();
  GLenum fb_attach;
  switch (attachment)
  {
  case FrameBuffer::kFrameBufferAttachment_ColorAttachment:
    fb_attach = GL_COLOR_ATTACHMENT0;
    break;
  case FrameBuffer::kFrameBufferAttachment_DepthAttachment:
    fb_attach = GL_DEPTH_ATTACHMENT;
    break;
  case FrameBuffer::kFrameBufferAttachment_StencilAttachment:
    fb_attach = GL_STENCIL_ATTACHMENT;
    break;
  case FrameBuffer::kFrameBufferAttachment_DepthStencilAttachment:
    fb_attach = GL_DEPTH_STENCIL_ATTACHMENT;
    break;
  case FrameBuffer::kFrameBufferAttachment_None:
    printf("Error, framebuffer not attachment\n.");
    return;
    break;
  default:
    break;
  }
  GLuint ok=0;
  //Create FramebBuffer
  glGenFramebuffers(1, &ok);
  glBindFramebuffer(GL_FRAMEBUFFER,ok);

  //glGenRenderbuffers(1, &data_->shadow_fbo_);
// glBindRenderbuffer(GL_RENDERBUFFER, data_->shadow_fbo_);
 // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, EngineManager::instance().width(),EngineManager::instance().height());
 // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, data_->shadow_fbo_);
  //Load texture TODO
  glFramebufferTexture2D(GL_FRAMEBUFFER, fb_attach, GL_TEXTURE_2D, fb.getTexture()->getID(),0);
  GLenum fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    switch (fb_status)
    {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      printf("Incomplete attachment\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
      printf("Incomplete attachment\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      printf("Incoplete mission attachment\n");
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      printf("Framebuffer unsuported\n");
      break;
    default:
      break;
    }
    printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
  }else{
    fb.setId(ok);
    fb.setLoaded(true);
    
  }

  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGlInterFaz::renderFrameBuffer(FrameBuffer &fb){

  glBindTexture(GL_TEXTURE_2D, fb.getTexture()->getID());
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
void OpenGlInterFaz::sendLight( Light *light,int num_light){
  vec3 position = light->getPosition();
  vec3 diffuse_c = light->getDiffuseColor();
  vec3 specular_c = light->getSpecularColor();
  vec3 ambient_c = light->getAmbientColor();
  float shin = light->getShinenes();
  int type = light->getType();
  if (data_->type == 0){
    if (data_->u_lights[num_light].l_pos >= 0){
      glUniform3f(data_->u_lights[num_light].l_pos, position.x, position.y, position.z);
    }


    if (data_->u_lights[num_light].l_ac >= 0){
      glUniform3f(data_->u_lights[num_light].l_ac, ambient_c.x, ambient_c.y, ambient_c.z);
    }


    if (data_->u_lights[num_light].l_sc >= 0){

      glUniform3f(data_->u_lights[num_light].l_sc, specular_c.x, specular_c.y, specular_c.z);
    }


    if (data_->u_lights[num_light].l_dc >= 0){
      glUniform3f(data_->u_lights[num_light].l_dc, diffuse_c.x, diffuse_c.y, diffuse_c.z);
    }


    if (data_->u_lights[num_light].l_sh >= 0){
      glUniform1f(data_->u_lights[num_light].l_sh, shin);
    }


    if (data_->u_lights[num_light].l_t >= 0){
      glUniform1i(data_->u_lights[num_light].l_t, type);
    }
  }
  //DIFFUSE
  if (data_->type == 1){
    if (data_->u_lights_d[num_light].l_pos >= 0){
      glUniform3f(data_->u_lights_d[num_light].l_pos, position.x, position.y, position.z);
    }

    if (data_->u_lights_d[num_light].l_ac >= 0){
      glUniform3f(data_->u_lights_d[num_light].l_ac, ambient_c.x, ambient_c.y, ambient_c.z);
    }


    if (data_->u_lights_d[num_light].l_sc >= 0){

      glUniform3f(data_->u_lights_d[num_light].l_sc, specular_c.x, specular_c.y, specular_c.z);
    }


    if (data_->u_lights_d[num_light].l_dc >= 0){
      glUniform3f(data_->u_lights_d[num_light].l_dc, diffuse_c.x, diffuse_c.y, diffuse_c.z);
    }

    if (data_->u_lights_d[num_light].l_sh >= 0){
      glUniform1f(data_->u_lights_d[num_light].l_sh, shin);
    }

    if (data_->u_lights_d[num_light].l_t >= 0){
      glUniform1i(data_->u_lights_d[num_light].l_t, type);
    }
  }
}
void OpenGlInterFaz::setDrawBuffer(int fb_id){

  glNamedFramebufferDrawBuffer(fb_id, GL_NONE);
}
void OpenGlInterFaz::setReadBuffer(int fb_id){
  glNamedFramebufferReadBuffer(fb_id, GL_NONE);
}

void OpenGlInterFaz::renderShadows(int program,mat4 light){
  glUseProgram(program);
  glUniformMatrix4fv(data_->light_space_, 1, GL_FALSE, &light[0][0]);
}