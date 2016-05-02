#include "CDK/opengl_interfaz.h"
#include "GL\glew.h"
#include "CDK/texture.h"
#include "CDK/directional_light.h"
#include "CDK/texture_material.h"
#include  "CDK/point_light.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

OpenGlInterFaz* OpenGlInterFaz::instance_ = nullptr;
OpenGlInterFaz& OpenGlInterFaz::instance(){
  if (instance_ == NULL){
    instance_ = new OpenGlInterFaz();
  }
  return *instance_;
}

struct LightUniforms{

  GLint faces_mat[6];
  GLint direction_s = -1;
  GLint cone_angle_s = -1;
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
  GLint directional_light_u = -1;
  LightUniforms u_lights[10];
  //Camera
  GLint proyec_pos = -1;
  GLint model_pos = -1;
  GLint view_pos = -1;
  //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  GLint mat_d_d = -1;
  GLint mat_s_d = -1;
  GLint mat_a_d = -1;

  
  LightUniforms u_directional_l;
  GLint proyec_pos_d = -1;
  GLint model_pos_d = -1;
  GLint view_pos_d = -1;
  //FrameBuffer
  GLuint shadow_frame_buffer;
  GLuint shadow_fbo_;//FrameBufferObject
  GLuint shadow_texture_frame_buffer;
  GLuint type;

  ///Shadows
  GLint light_space_ = -1;

  ////
  //Point lights uniforms

  GLint mat_point_proy[6];

  //SPot 
  bool uniforms_loaded = false;
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


void OpenGlInterFaz::useMaterial( int program_id){
    glUseProgram(program_id);
}
int OpenGlInterFaz::loadMaterial(Material *mat){

  data_->shadow_program_ = glCreateProgram();
  data_->shadow_vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  const char* vertex_data = mat->vertex_data_.c_str();
  GLint lenght = strlen(vertex_data);
  glShaderSource(data_->shadow_vertex_shader_, 1, &vertex_data, &lenght);
  compileShader(data_->shadow_vertex_shader_);

  //FRAGENT SHADER
  const char * fragment_data = mat->fragment_data_.c_str();
  lenght = strlen(fragment_data);
  data_->shadow_fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(data_->shadow_fragment_shader_, 1, &fragment_data, &lenght);
  compileShader(data_->shadow_fragment_shader_);

  glAttachShader(data_->shadow_program_, data_->shadow_vertex_shader_);
  glAttachShader(data_->shadow_program_, data_->shadow_fragment_shader_);

  GLuint geo_shader = 0;
  if (mat->geometry_data_.size() > 0){
    const char * geo_shader_data = mat->geometry_data_.c_str();
    lenght = strlen(geo_shader_data);
    geo_shader  = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geo_shader, 1, &geo_shader_data, &lenght);
    compileShader(geo_shader);
    glAttachShader(data_->shadow_program_, geo_shader);
  }

  glLinkProgram(data_->shadow_program_);
  GLint program_compiled;
  glGetProgramiv(data_->shadow_program_, GL_LINK_STATUS, &program_compiled);
 
  if (program_compiled == GL_FALSE){
    GLchar info_log[512];
    glGetProgramInfoLog(data_->shadow_program_, 512, NULL, info_log);
    printf("LINKED PROGRAM ERROR: %s\n", info_log);
  }else{ 
    glDeleteShader(data_->shadow_vertex_shader_);
    glDeleteShader(data_->shadow_fragment_shader_);

    GLint num_uniforms;
    glGetProgramiv(data_->shadow_program_, GL_ACTIVE_UNIFORMS, &num_uniforms);
    GLint max_length;
    glGetProgramiv(data_->shadow_program_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
    GLsizei buff_info_size = 0;
    GLint size = 0;
    GLenum type;
    std::unique_ptr<char[]> uniform_name = std::unique_ptr<char[]>(new char[max_length]);
    for (int i = 0; i < num_uniforms; i++){
      glGetActiveUniform(data_->shadow_program_, i, max_length, &lenght, &size, &type, &uniform_name[0]);
      mat->uniforms_names.push_back(std::string(&uniform_name[0]));
      int location = glGetUniformLocation(data_->shadow_program_, &uniform_name[0]);
      mat->uniforms_values.push_back(location);
    }

    //DIFFUSE UNIFORMS
    /*if (data_->proyec_pos_d<0)data_->proyec_pos_d = glGetUniformLocation(data_->shadow_program_, "u_projection_m_d");
    if (data_->model_pos_d<0)data_->model_pos_d = glGetUniformLocation(data_->shadow_program_, "u_model_m_d");
    if (data_->view_pos_d<0)data_->view_pos_d = glGetUniformLocation(data_->shadow_program_, "u_view_m_d");

    if (data_->mat_d_d<0)data_->mat_d_d = glGetUniformLocation(data_->shadow_program_, "u_material_diff_d");
    if (data_->mat_s_d<0)data_->mat_s_d = glGetUniformLocation(data_->shadow_program_, "u_material_specular_d");
    if (data_->mat_a_d<0)data_->mat_a_d = glGetUniformLocation(data_->shadow_program_, "u_material_ambient_d");*/

    return data_->shadow_program_;
  }

}

void OpenGlInterFaz::drawGeometry( int vao,unsigned int indices, int draw_mode){
 
  glBindVertexArray(vao);
  GLenum primitive;
  switch (draw_mode)
  {
  case 0:
    primitive = GL_TRIANGLES;
    break;
  case 1:
    primitive = GL_TRIANGLE_STRIP;
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(400*400);
    indices = (399) * 800 + 399;
    break;
  case 2:
    primitive = GL_POINTS;
    break;
  default:
    primitive = GL_TRIANGLES;
    break;
  }
  
  glDrawElements(primitive, indices, GL_UNSIGNED_INT, (void*)0);
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
    case GL_GEOMETRY_SHADER:
      printf("GEOMETRY SHADER COMPILED ERROR: %s", infoLog);
    }

  }
}


void OpenGlInterFaz::useUnifor3f(int position, const float*data){

	if (position >= 0){
		glUniform3fv(position, 1, data);
	}
}

void OpenGlInterFaz::useUniformMat4(int program,mat4 m){
  glUniformMatrix4fv(program, 1, GL_FALSE, &m[0][0]);
}

void OpenGlInterFaz::useUniformMat3(int program, mat3 m){
  glUniformMatrix3fv(program, 1, GL_FALSE, &m[0][0]);
}


void OpenGlInterFaz::useUniformUi(int position, unsigned int value){

    glUniform1ui(position, value);
  
}

void OpenGlInterFaz::useUniformF(int position, float value){

  glUniform1f(position, value);

}

void OpenGlInterFaz::useUniformI(int position, unsigned int value){
  glUniform1i(position, value);
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

#include "CDK/engine_manager.h"
void OpenGlInterFaz::loadTexture(std::shared_ptr<Texture> m){

    
  int mag_filter = m->getMagFilter();
  int min_filter = m->getMinFilter();

  int s_wrap = m->getWrapCoordinateS();
  int t_wrap = m->getWrapCoordinateT();
  GLuint ok=0;
  glGenTextures(1, &ok);
  glBindTexture(GL_TEXTURE_2D,ok);

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
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 
  }
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
  m->setID(ok);
    
}

void OpenGlInterFaz::useTexture(int position , int texture_id){
  glUniform1i(position, 0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture_id); 

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
      printf("incomplete missing attachment\n");
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

}

void OpenGlInterFaz::renderFrameBuffer(FrameBuffer &fb){

  glBindTexture(GL_TEXTURE_2D, fb.getTexture()->getID());
  glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void OpenGlInterFaz::sendLight(Light *light, Material *mat, int num_light, bool is_directional){
  //Send uniforms
  vec3 position = light->getPosition();
  vec3 diffuse_c = light->getDiffuseColor();
  vec3 specular_c = light->getSpecularColor();
  vec3 ambient_c = light->getAmbientColor();
  float shin = light->getShinenes();
  int type = light->getType();
  if (!is_directional){

    mat->setUniform3fValue(("lights[" + std::to_string(num_light) + "].position").c_str(),
                           position.x, position.y, position.z);
    mat->setUniform3fValue(("lights[" + std::to_string(num_light) + "].ambient_color").c_str(),
                           ambient_c.x, ambient_c.y, ambient_c.z);
    mat->setUniform3fValue(("lights[" + std::to_string(num_light) + "].specular_color").c_str(),
                           specular_c.x, specular_c.y, specular_c.z);
    mat->setUniform3fValue(("lights[" + std::to_string(num_light) + "].diffuse_color").c_str(),
                           diffuse_c.x, diffuse_c.y, diffuse_c.z);
    mat->setUniformFValue(("lights[" + std::to_string(num_light) + "].sh").c_str(),shin);
    mat->setUniformIValue(("lights[" + std::to_string(num_light) + "].type").c_str(),type);
    mat->setUniformIValue("shadow_texture", 2);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ((PointLight*)light)->getShadowCubeMapTexture());

    //DIFFUSE
    if (data_->type == 1){
    /*  if (data_->u_lights_d[num_light].l_pos >= 0){
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
      }*/
    }
  }else{

    DirectionalLight *dir_l = (DirectionalLight*)light;
    int texture_position = mat->getUniformLocation("u_directional_light.depth_map");
    glUniform1i(texture_position, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, dir_l->getShadowMap()->getTexture()->getID());

    mat->setUniform3fValue("u_directional_light.position",position.x, position.y, position.z);
    mat->setUniform3fValue("u_directional_light.ambient_color",ambient_c.x, ambient_c.y, ambient_c.z);
    mat->setUniform3fValue("u_directional_light.specular_color",specular_c.x, specular_c.y, specular_c.z);
    mat->setUniform3fValue("u_directional_light.diffuse_color",diffuse_c.x, diffuse_c.y, diffuse_c.z);
    mat->setUniformFValue("u_directional_light.sh",shin);
    mat->setUniformIValue("u_directional_light.type",type);
    mat->setUniformMat4Value("u_directional_light.ligth_view_proyection", dir_l->getLightProyection());
  }
}



 

void OpenGlInterFaz::createShadoCubeMap(PointLight *pl){
  GLuint id_texture;
  GLuint id_fb;
  glGenFramebuffers(1, &id_fb);

  GLuint id_shadow_m;
  glGenTextures(1, &id_shadow_m);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id_shadow_m);
  for (int i = 0; i < 6; i++){
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  }
  pl->setTextureCubeMap(id_shadow_m);

  glBindFramebuffer(GL_FRAMEBUFFER, id_fb);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id_shadow_m, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  pl->setShadowCubeMapId(id_fb);
  GLenum fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
   if (fb_status != GL_FRAMEBUFFER_COMPLETE) {
    switch (fb_status)
    {
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      printf("Incomplete attachment\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
      printf("Incomplete attachment\n");
      break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      printf("incomplete missing attachment\n");
      break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
      printf("Framebuffer unsuported\n");
      break;
    default:
      break;
    }
    printf("ERROR:: CUBE MAP FRAMEBUFFER:: Framebuffer is not complete!\n");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void OpenGlInterFaz::useDiffuseMaterial(Material * mat){
}


#include "CDK/texture_cache.h"
void OpenGlInterFaz::useTextureMaterial(Material *mat, Material::MaterialSettings *mat_sett,
                                        mat4 cam_view, mat4 cam_proy, mat4 model,
                                        Light *dir_light, std::vector<std::shared_ptr<Light>> lights){

  vec3 color_amb = mat_sett->getAmbientColor();
  vec3 color_diff = mat_sett->getAmbientColor();
  vec3 color_spe = mat_sett->getAmbientColor();
  mat->setUniform3fValue("u_material_ambient", color_amb.x, color_amb.y, color_amb.z);
  mat->setUniform3fValue("u_material_diff", color_diff.x, color_diff.y, color_diff.z);
  mat->setUniform3fValue("u_material_specular", color_spe.x, color_spe.y, color_spe.z);
  mat->setUniformMat4Value("u_view_m", cam_view);
  mat->setUniformMat4Value("u_projection_m", cam_proy);
  mat->setUniformMat4Value("u_model_m", model);

  sendLight(dir_light, mat, 0, true);
  for (int i = 0; i < lights.size(); i++){
   sendLight(lights[i].get(),mat, i, false);
    lights[i]->setLoaded(true);
  }

  //Uses textures

  int num_diffuse_t = 1;
  int num_specular_t = 1;
  TextureMaterial::MaterialSettings *text_mat_s = (TextureMaterial::MaterialSettings*)mat_sett;
  std::vector<std::string> textures = text_mat_s->getTextures();
  for (int i = 0; i < textures.size(); i++){
    std::shared_ptr<Texture> current_texture = TextureCache::instance().getTexture(textures[i].c_str());
    if (!current_texture->getLoaded()){
      OpenGlInterFaz::instance().loadTexture(current_texture);
      current_texture->setLoaded(true);
    }
    std::string type;
    std::string type_name = current_texture->getType();
    std::stringstream ssn;
    if (type_name == "diffuse"){
      type = "u_diffuse_texture";
      ssn << num_diffuse_t;
      num_diffuse_t++;
    }
    else  if (type_name == "specular"){
      type = "u_specular_texture";
      ssn << num_specular_t;
      num_specular_t++;
    }
    OpenGlInterFaz::instance().useTexture(mat->getUniformLocation((type + ssn.str()).c_str()), current_texture->getID());

  }

}

