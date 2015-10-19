#include "camera.h"


Camera::Camera(){
  up_.x = 0; up_.y = 1.0; up_.z = 0;
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up){
  glm::lookAt(eye, center, up);
}

void Camera::render(DisplayList &dl){
  for (int i = 0; i < dl.size(); i++){
    dl.execute();
  }
}

void Camera::cull(){

}