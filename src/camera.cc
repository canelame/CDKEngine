#include "camera.h"
#include "GLFW\glfw3.h"

struct Camera::Data{
  OpenGlInterFaz *interfaz_;
  mat4 proyection_mat_;
  mat4 look_at_mat_;
  vec3 position_;
  vec3 up_;
  vec3 right_;
  vec3 front_;
};

Camera::Camera(){
  
  model_scale =  vec3(5.0,5.0,5.0);//Added only to use a first implementation of ImGui

  data = new Data;
	data->interfaz_ = new OpenGlInterFaz();
  data->position_.x = 0.0; 	data->position_.y = 0.0; 	data->position_.z = 10.0;
  position_.x = 0.0; 	position_.y = 0.0; 	position_.z = 10.0;
  data->up_.x = 0; 	data->up_.y = 1.0; 	data->up_.z = 0;
  data->front_.x = 0.0; 	data->front_.y = 0.0; 	data->front_.z = -10.0;
  setLookAt(data->position_, data->position_ + data->front_, data->up_);
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  data->proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up){
  data->look_at_mat_ = glm::lookAt(eye, center, up);
}

void Camera::render(DisplayList &dl){

}

void Camera::cull(){

}

 void Camera::runCommand(OpenGlInterFaz &i)const{

   GLfloat radius = 50.0f;
   GLfloat camX = sin(glfwGetTime()) * radius;
   GLfloat camZ = cos(glfwGetTime()) * radius;
   glm::mat4 view;
   view = glm::lookAt(glm::vec3(position_.x, position_.y, position_.z), data->front_, glm::vec3(0.0, 1.0, 0.0));
   const float  color[]= { 0 };
   i.useUniformUi("u_texture",0);
   //i.useUnifor3f("color_", color);
	 i.drawGeometry();
	
}

 glm::mat4 Camera::getModel(){
   mat4 model;
   //view = glm::rotate(view, 0.0, vec3(1.0, 0.0, 0.0));
   model = glm::scale(model, model_scale);
   model = glm::translate(model, vec3(0.0, 0.0, 0.0));
   return model;
 }
 glm::mat4 Camera::getProyection(){
   return data->proyection_mat_; 
 }
 glm::mat4 Camera::getView(){
   return data->look_at_mat_;
 }