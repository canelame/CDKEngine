#include "CDK/Lights/point_light.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
struct PointLight::Data{
  GLint shadowCube = -1;
  GLint texture_cube_map = -1;
  std::vector<mat4> shadow_matrices;
  
};
PointLight::PointLight(){
  data_ = new Data;
  type = 1;
}
PointLight::~PointLight(){}


void PointLight::init(){

}

void PointLight::setPosition(vec3 p){
  Light::setPosition(p);
  computePerspectiveLight();
}

void PointLight::computePerspectiveLight(){
  GLfloat aspect = 1024.0f / 1024.0f;
  GLfloat near = 1.0f;
  GLfloat far = 50.0f;
  mat4 shadow_projection = glm::perspective(90.0f, aspect, near, far);

  data_->shadow_matrices.clear();

  mat4 temp_mat;
  temp_mat = shadow_projection * glm::lookAt(getPosition(), getPosition() + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
  data_->shadow_matrices.push_back(temp_mat);
  temp_mat = mat4();
  temp_mat = shadow_projection * glm::lookAt(getPosition(), getPosition() + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
  data_->shadow_matrices.push_back(temp_mat);
  temp_mat = mat4();
  temp_mat = shadow_projection * glm::lookAt(getPosition(), getPosition() + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
  data_->shadow_matrices.push_back(temp_mat);
  temp_mat = mat4();
  temp_mat = shadow_projection * glm::lookAt(getPosition(), getPosition() + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
  data_->shadow_matrices.push_back(temp_mat);
  temp_mat = mat4();
  temp_mat = shadow_projection * glm::lookAt(getPosition(), getPosition() + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
  data_->shadow_matrices.push_back(temp_mat);
  temp_mat = mat4();
  temp_mat = shadow_projection * glm::lookAt(getPosition(), getPosition() + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0));
  data_->shadow_matrices.push_back(temp_mat);

}

std::vector<mat4> PointLight::getShadowMatrices(){
  return data_->shadow_matrices;
}
void PointLight::setShadowCubeMapId(int id){
  data_->shadowCube = id;

}

void PointLight::setTextureCubeMap(int id){
  data_->texture_cube_map = id;
}

int PointLight::getShadowCubeMapBuffer(){
  return data_->shadowCube;
}

int PointLight::getShadowCubeMapTexture(){
  return data_->texture_cube_map;
}