#include "camera.h"


Camera::Camera(){
  position_.x = 0.0; position_.y = 0.0; position_.z = -100.0;
  up_.x = 0; up_.y = 1.0; up_.z = 0;
  front_.x = 0.0; front_.y = 0.0; front_.z = 100.0;
  setLookAt(position_, front_, up_);
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up){
  glm::lookAt(eye, center, up);
}

void Camera::render(DisplayList &dl){
  for (int i = 0; i < dl.size(); i++){
    dl.execute();
  }
}

void Camera::cull(){

}