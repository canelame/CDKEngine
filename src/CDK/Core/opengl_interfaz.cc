#include "CDK/Core/opengl_interfaz.h"
#include "GL\glew.h"
#include "CDK/Resources/texture.h"
#include "CDK/Lights/directional_light.h"
#include "CDK/Material/texture_material.h"
#include "CDK/Lights/point_light.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "CDK/Core/engine_manager.h"
#include "CDK/Core/texture_cache.h"

const int texture_direction_light = 0;
const int texture_point_light = 1;
const int texture_pmaterial_i = 2;
const int material_texture = 10;
const int material_diffuse = 20;

OpenGlInterFaz* OpenGlInterFaz::instance_ = nullptr;
OpenGlInterFaz& OpenGlInterFaz::instance(){
  if (instance_ == NULL){
    instance_ = new OpenGlInterFaz();
  }
  return *instance_;
}

OpenGlInterFaz::OpenGlInterFaz(){};

////////////////////////////////////////////////////////
////// MATERIAL FUNCTIONS
////////////////////////////////////////////////////////
int OpenGlInterFaz::loadMaterial(Material *mat){

  GLuint shadow_vertex_shader_;
  GLuint shadow_fragment_shader_;
  GLuint shadow_program_;

  shadow_program_ = glCreateProgram();
  shadow_vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
  const char* vertex_data = mat->vertex_data_.c_str();
  GLint lenght = strlen(vertex_data);
  glShaderSource(shadow_vertex_shader_, 1, &vertex_data, &lenght);
  compileShader(shadow_vertex_shader_);

  //FRAGENT SHADER
  const char * fragment_data = mat->fragment_data_.c_str();
  lenght = strlen(fragment_data);
  shadow_fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shadow_fragment_shader_, 1, &fragment_data, &lenght);
  compileShader(shadow_fragment_shader_);

  glAttachShader(shadow_program_, shadow_vertex_shader_);
  glAttachShader(shadow_program_, shadow_fragment_shader_);

  GLuint geo_shader = 0;
  if (mat->geometry_data_.size() > 0){
    const char * geo_shader_data = mat->geometry_data_.c_str();
    lenght = strlen(geo_shader_data);
    geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geo_shader, 1, &geo_shader_data, &lenght);
    compileShader(geo_shader);
    glAttachShader(shadow_program_, geo_shader);
  }

  glLinkProgram(shadow_program_);
  GLint program_compiled;
  glGetProgramiv(shadow_program_, GL_LINK_STATUS, &program_compiled);

  if (program_compiled == GL_FALSE){
    GLchar info_log[512];
    glGetProgramInfoLog(shadow_program_, 512, NULL, info_log);
    printf("LINKED PROGRAM ERROR: %s\n", info_log);
  }
  else{
    glDeleteShader(shadow_vertex_shader_);
    glDeleteShader(shadow_fragment_shader_);
    int location = 0;
    GLint num_uniforms;
    Material::UniformTypes t_u;
    std::string name;
    glGetProgramiv(shadow_program_, GL_ACTIVE_UNIFORMS, &num_uniforms);
    for (int i = 0; i < num_uniforms; i++){
      getUniformInfo(shadow_program_, i, name, location, t_u);
      Material::UniformData *t_uni = mat->findUniform(name.c_str());
      if (t_uni != nullptr){
        t_uni->location_ = location;
      }
      else{
        Material::UniformData uniform;
        uniform.name_ = name;
        uniform.type_ = t_u;
        uniform.location_ = location;
        mat->uniforms_.push_back(uniform);
      }

    }
    mat->is_compiled_ = true;
    mat->setProgram( shadow_program_);
    return shadow_program_;
  }

}

void OpenGlInterFaz::useMaterial(Material* mat){
  glUseProgram(mat->getProgram());
}

void OpenGlInterFaz::useMaterialUniforms(Material *material){
  for (int i = 0; i < material->uniforms_.size(); i++){
    int location = material->uniforms_[i].location_;
    switch (material->uniforms_[i].type_)
    {
    case Material::UniformTypes::kUniformTypes3vFloat:
    {
      vec3 *data = (vec3*)material->uniforms_[i].data_;
      if (data == nullptr)break;
      OpenGlInterFaz::instance().useUnifor3f(location, *data);
    }
    break;

    case Material::UniformTypes::kUniformTypesFloat:
    {
      float *data = (float*)material->uniforms_[i].data_;
      if (data == nullptr)break;
      OpenGlInterFaz::instance().useUniformF(location, *data);
      break;
    }
    case Material::UniformTypes::kUniformTypesInt:
    {
      int *data = (int*)material->uniforms_[i].data_;
      if (data == nullptr)break;
      if (location >= 0){
        OpenGlInterFaz::instance().useUniformI(location, *data);
      }

      break;
    }
    case Material::UniformTypes::kUniformTypesMat3:
    {
      mat3 *data = (mat3*)material->uniforms_[i].data_;
      if (data == nullptr)break;
      OpenGlInterFaz::instance().useUniformMat3(location, *data);
      break;
    }
    case Material::UniformTypes::kUniformTypesMat4:
    {
      mat4 * data = (mat4*)material->uniforms_[i].data_;
      if (data == nullptr)break;
      OpenGlInterFaz::instance().useUniformMat4(location, *data);
      break;
    }
    case Material::UniformTypes::kUniformTypesUInt:
    {
      unsigned int *data = (unsigned int*)material->uniforms_[i].data_;
      if (data == nullptr)break;
      OpenGlInterFaz::instance().useUniformUi(location, *data);
      break;
    }
    default:
      break;
    }
  }


}
void OpenGlInterFaz::useDiffuseMaterial(Material *mat, Material::MaterialSettings *mat_sett,
  mat4 cam_view, mat4 cam_proy, mat4 model, Light *dir_light, std::vector<std::shared_ptr<Light>> lights){

  if (!mat->uniforms_loaded_){
    mat->setUniform3fValue("u_material_ambient_d", &mat_sett->getAmbientColor());
    mat->setUniform3fValue("u_material_diff_d", &mat_sett->getDiffuseColor());
    mat->setUniform3fValue("u_material_specular_d", &mat_sett->getSpecularColor());
    //mat->setUniformFValue("u_shinn_d", &mat_sett->sh_);
    mat->setUniformMat4Value("u_view_m_d", &cam_view);
    mat->setUniformMat4Value("u_projection_m_d", &cam_proy);
    mat->setUniformMat4Value("u_model_m_d", &model);
    mat->setUniformIValue("enable_shadow", &EngineManager::instance().enable_shadows_);
    //Directional uniforms
    DirectionalLight * dir_l = (DirectionalLight*)dir_light;
    mat4  light_proyection = dir_l->getLightProyection();
    mat->setUniform3fValue("u_directional_light.position", &dir_light->getPosition());
    mat->setUniform3fValue("u_directional_light.ambient_color", &dir_light->getAmbientColor());
    mat->setUniform3fValue("u_directional_light.diffuse_color", &dir_light->getDiffuseColor());
    mat->setUniform3fValue("u_directional_light.specular_color", &dir_light->getSpecularColor());
    mat->setUniformMat4Value("u_directional_light.ligth_view_proyection", &light_proyection);


    //dir light
    int loc_d = mat->getUniformLocation("u_directional_light.depth_map");
    OpenGlInterFaz::instance().useUniformI(loc_d, texture_direction_light);
    glActiveTexture(GL_TEXTURE0 + texture_direction_light);
    glBindTexture(GL_TEXTURE_2D, dir_l->getShadowMap()->getTexture()->getID());

    //Points
    for (int l = 0; l < lights.size(); l++){
      mat->setUniform3fValue(("lights_d[" + std::to_string(l) + "].position").c_str(), &lights[l]->getPosition());
      mat->setUniform3fValue(("lights_d[" + std::to_string(l) + "].ambient_color").c_str(), &lights[l]->getAmbientColor());
      mat->setUniform3fValue(("lights_d[" + std::to_string(l) + "].specular_color").c_str(), &lights[l]->getSpecularColor());
      mat->setUniform3fValue(("lights_d[" + std::to_string(l) + "].diffuse_color").c_str(), &lights[l]->getDiffuseColor());
      int loc_s = mat->getUniformLocation("shadow_texture");
      if (loc_s >= 0){
        OpenGlInterFaz::instance().useUniformI(loc_s, texture_point_light + l);
        glActiveTexture(GL_TEXTURE0 + texture_point_light + l);
        PointLight * p_l = (PointLight*)lights[l].get();
        glBindTexture(GL_TEXTURE_CUBE_MAP, p_l->getShadowCubeMapTexture());

      }
    }
    mat->uniforms_loaded_ = false;
  }

  useMaterialUniforms(mat);

}

void OpenGlInterFaz::useTextureMaterial(Material *mat, Material::MaterialSettings *mat_sett,
  mat4 cam_view, mat4 cam_proy, mat4 model,  Light *dir_light, std::vector<std::shared_ptr<Light>> lights){

  if (!mat->uniforms_loaded_){
    mat->setUniform3fValue("u_material_ambient", &mat_sett->getAmbientColor());
    mat->setUniform3fValue("u_material_diff", &mat_sett->getDiffuseColor());
    mat->setUniform3fValue("u_material_specular", &mat_sett->getSpecularColor());
    mat->setUniformMat4Value("u_view_m", &cam_view);
    mat->setUniformMat4Value("u_projection_m", &cam_proy);
    mat->setUniformMat4Value("u_model_m", &model);
    mat->setUniformIValue("enable_shadow", &EngineManager::instance().enable_shadows_);
    //Directional uniforms
    DirectionalLight * dir_l = (DirectionalLight*)dir_light;
    mat4  light_proyection = dir_l->getLightProyection();
    mat->setUniform3fValue("u_directional_light.position", &dir_light->getPosition());
    mat->setUniform3fValue("u_directional_light.ambient_color", &dir_light->getAmbientColor());
    mat->setUniform3fValue("u_directional_light.diffuse_color", &dir_light->getDiffuseColor());
    mat->setUniform3fValue("u_directional_light.specular_color", &dir_light->getSpecularColor());
    mat->setUniformMat4Value("u_directional_light.ligth_view_proyection", &light_proyection);

    //dir light
    int loc_d = mat->getUniformLocation("u_directional_light.depth_map");
    OpenGlInterFaz::instance().useUniformI(loc_d, texture_direction_light);
    glActiveTexture(GL_TEXTURE0 + texture_direction_light);
    glBindTexture(GL_TEXTURE_2D, dir_l->getShadowMap()->getTexture()->getID());

    //Points
    for (int l = 0; l < lights.size(); l++){
      mat->setUniform3fValue(("lights[" + std::to_string(l) + "].position").c_str(), &lights[l]->getPosition());
      mat->setUniform3fValue(("lights[" + std::to_string(l) + "].ambient_color").c_str(), &lights[l]->getAmbientColor());
      mat->setUniform3fValue(("lights[" + std::to_string(l) + "].specular_color").c_str(), &lights[l]->getSpecularColor());
      mat->setUniform3fValue(("lights[" + std::to_string(l) + "].diffuse_color").c_str(), &lights[l]->getDiffuseColor());
      int loc_s = mat->getUniformLocation("shadow_texture");
      if (loc_s >= 0){
        OpenGlInterFaz::instance().useUniformI(loc_s, texture_point_light);
        glActiveTexture(GL_TEXTURE0 + texture_point_light);
        PointLight * p_l = (PointLight*)lights[l].get();
        glBindTexture(GL_TEXTURE_CUBE_MAP, p_l->getShadowCubeMapTexture());

      }
    }
    mat->uniforms_loaded_ = false;
  }

  useMaterialUniforms(mat);


  /////////////////////////////////////////
  //  MATERIAL TEXTURES
  /////////////////////////////////////////

  int num_diffuse_t = 1;
  int num_specular_t = 1;
  TextureMaterial::MaterialSettings *text_mat_s = (TextureMaterial::MaterialSettings*)mat_sett;
  std::vector<std::string> textures = text_mat_s->getTextures();

  for (int i = 0; i < textures.size(); i++){

    std::shared_ptr<Texture> current_texture = TextureCache::instance().getTexture(textures[i].c_str());
    if (current_texture.get() == NULL)return;

    if (!current_texture->getLoaded()){
      OpenGlInterFaz::instance().loadTexture(current_texture);
      current_texture->setLoaded(true);
    }
    //Use texture
    int loc_d = mat->getUniformLocation("u_diffuse_texture1");
    OpenGlInterFaz::instance().useUniformI(loc_d, texture_pmaterial_i + i);
    glActiveTexture(GL_TEXTURE0 + texture_pmaterial_i + i);

    glBindTexture(GL_TEXTURE_2D, current_texture->getID());

  }



}

////////////////////////////////////////////////////////
////// GEOMETRY FUNCTIONS
////////////////////////////////////////////////////////
void OpenGlInterFaz::loadBuffer(Buffer *buff){

  GLuint shadow_vao_;
  GLuint shadow_vbo_v_;
  GLuint shadow_vbo_i_;

  GLint position_size = buff->vertexSize() * sizeof(float);
  GLint normal_size = buff->normalSize() * sizeof(float);
  GLint uv_size = buff->uvSize() * sizeof(float);
  GLint tan_size = buff->tangentSize()*sizeof(float);
  GLint bitan_size = buff->bitangentSize() * sizeof(float);
  GLint index_size = buff->indiceSize() * sizeof(unsigned int);

  glGenVertexArrays(1, &shadow_vao_);
  glGenBuffers(1, &shadow_vbo_v_);
  glGenBuffers(1, &shadow_vbo_i_);
  glBindVertexArray(shadow_vao_);
  glBindBuffer(GL_ARRAY_BUFFER, shadow_vbo_v_);
  glBufferData(GL_ARRAY_BUFFER, position_size + normal_size + uv_size, NULL, GL_STATIC_DRAW);

  //Load positions
  glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, &buff->getData()[0]);

  //Load normals
  int a = strlen(buff->getData());
  glBufferSubData(GL_ARRAY_BUFFER, position_size, normal_size, &buff->getData()[position_size]);
  
  glBufferSubData(GL_ARRAY_BUFFER, position_size + normal_size, uv_size, &buff->getData()[position_size + normal_size]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shadow_vbo_i_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, &buff->getData()[position_size + normal_size + uv_size + tan_size + bitan_size], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)position_size);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(position_size + normal_size));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
  buff->setVAO(shadow_vao_, shadow_vbo_v_, shadow_vbo_i_);

}

void OpenGlInterFaz::drawGeometry(int vao,unsigned int buffer_indeces ,unsigned int indices){
  // assert(vao && indices <= 0 && indices % 3 != 0);
  glBindVertexArray(vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indeces);
  glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, (void*)0);
  glBindVertexArray(0);
}
////////////////////////////////////////////////////////
////// FRAMEBUFFER FUNCTIONS
////////////////////////////////////////////////////////
void OpenGlInterFaz::bindFrameBuffer(int fb_id, FrameBuffer::kFramebufferBindType type){
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
  glBindFramebuffer(type_binding, fb_id);

}

void OpenGlInterFaz::createFrameBuffer(FrameBuffer &fb){

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
  GLuint ok = 0;
  //Create FramebBuffer
  glGenFramebuffers(1, &ok);
  glBindFramebuffer(GL_FRAMEBUFFER, ok);
  //Load texture TODO
  glFramebufferTexture2D(GL_FRAMEBUFFER, fb_attach, GL_TEXTURE_2D, fb.getTexture()->getID(), 0);
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
  }
  else{
    fb.setId(ok);
    fb.setLoaded(true);
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


////////////////////////////////////////////////////////
////// SHADER FUNCTIONS
////////////////////////////////////////////////////////
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

void OpenGlInterFaz::getUniformInfo(int program, int index, std::string &name, int &out_location, Material::UniformTypes &out_type){

  GLint max_length;

  if (program < 0)return;
  glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
  GLsizei buff_info_size = 0;
  GLint size = 0;
  GLint lenght = 0;
  GLenum type;
  int location = 0;
  if (max_length <= 0)return;
  std::unique_ptr<char[]> uniform_name = std::unique_ptr<char[]>(new char[max_length]);
  Material::UniformTypes value_type_ = Material::UniformTypes(0);

  glGetActiveUniform(program, index, max_length, &lenght, &size, &type, &uniform_name[0]);
  //Set uniform type
  switch (type)
  {
  case GL_FLOAT:
    value_type_ = Material::kUniformTypesFloat;
    break;
  case GL_UNSIGNED_INT:
    value_type_ = Material::kUniformTypesUInt;
    break;
  case GL_INT:
    value_type_ = Material::kUniformTypesInt;
    break;
  case GL_FLOAT_MAT4:
    value_type_ = Material::kUniformTypesMat4;
    break;
  case GL_FLOAT_MAT3:
    value_type_ = Material::kUniformTypesMat3;
    break;
  case GL_FLOAT_VEC3:
    value_type_ = Material::kUniformTypes3vFloat;
  case GL_SAMPLER_CUBE:
    value_type_ = Material::kUniformTypesCubeSampler;
    break;
  case GL_SAMPLER_2D:
    value_type_ = Material::kUniformTypesSampler2D;
    break;
  default:
    printf("Uniform not type\n");
    break;
    break;
  }
  location = glGetUniformLocation(program, &uniform_name[0]);
  out_location = location;
  out_type = value_type_;
  name = &uniform_name[0];
}

int OpenGlInterFaz::getUniformIndex(int program, const char*name){
  const char *name_u[1] = { name };
  GLuint index = 0;
  glGetUniformIndices(program, 1, name_u, &index);
  if (index != GL_INVALID_INDEX){
    return index;
  }
  return -1;

}
////////////////////////////////////////////////////////
////// UNIFORM FUNCTIONS
////////////////////////////////////////////////////////

void OpenGlInterFaz::useUnifor3f(int position, vec3 data){

	if (position >= 0){
		glUniform3f(position, data.x , data.y , data.z);
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

////////////////////////////////////////////////////////
////// TEXTURE FUNCTIONS
////////////////////////////////////////////////////////


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

void OpenGlInterFaz::useTexture(int active_texture , int texture_id){

  glActiveTexture(GL_TEXTURE0 + active_texture);
  glBindTexture(GL_TEXTURE_2D, texture_id); 

}








