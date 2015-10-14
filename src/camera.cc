#include "camera.h"

Camera::Camera(){
  b.alloc();
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(){}