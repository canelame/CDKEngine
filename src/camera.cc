#include "camera.h"
#include "GLFW\glfw3.h"

Camera::Camera(){
	interfaz_ = new OpenGlInterFaz();
  position_.x = 0.0; position_.y = 0.0; position_.z = 10.0;
  up_.x = 0; up_.y = 1.0; up_.z = 0;
  front_.x = 0.0; front_.y = 0.0; front_.z = -10.0;
  setLookAt(position_, position_+front_, up_);
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up){
	look_at_mat_=  glm::lookAt(eye, center, up);
}

void Camera::render(DisplayList &dl){
  for (int i = 0; i < dl.size(); i++){
    dl.execute();
  }
}

void Camera::cull(){

}

 void Camera::runCommand(OpenGlInterFaz &i, OpenGlInterFaz &out)const{

   GLfloat radius = 10.0f;
   GLfloat camX = sin(glfwGetTime()) * radius;
   GLfloat camZ = cos(glfwGetTime()) * radius;
   glm::mat4 view;
   view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


	
	mat4 model;
	//view = glm::rotate(view, 0.0, vec3(1.0, 0.0, 0.0));
	model = glm::scale(view, vec3(20.0, 20.0, 20.0));
	model = glm::translate(view, vec3(0.0, 0.0, 0.0));
	i.useUniformMat4("u_model_m", glm::value_ptr(model));
  i.useUniformMat4("u_projection_m", glm::value_ptr(proyection_mat_));
  i.useUniformMat4("u_view_m", glm::value_ptr(look_at_mat_));
  const float  color[3]= { 1.0, 1.0, 0.0 };
  //i.useUnifor3f("color_", color);
	i.useDrawGeometry();
	
	out = i;
}