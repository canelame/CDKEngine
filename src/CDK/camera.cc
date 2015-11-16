#include "CDK/camera.h"
#include "GLFW\glfw3.h"
#include "CDK/display_list.h"
struct Camera::Data{
  OpenGlInterFaz *interfaz_;
  mat4 proyection_mat_;
  mat4 look_at_mat_;
  vec3 position_;
  vec3 up_;
  vec3 right_;
  vec3 front_;
  std::shared_ptr<DisplayList> dl_cam_;
  bool created_dl = false;
};

Camera::Camera(){
  
  model_scale =  vec3(2.0,2.0,2.0);//Added only to use a first implementation of ImGui

  data_ = new Data;
  data_->interfaz_ = new OpenGlInterFaz();
  data_->position_.x = 0.0; 	data_->position_.y = 0.0; 	data_->position_.z = 10.0;
  position_.x = 0.0; 	position_.y = 0.0; 	position_.z = 10.0;
  data_->up_.x = 0; 	data_->up_.y = 1.0; 	data_->up_.z = 0;
  data_->front_.x = 0.0; 	data_->front_.y = 0.0; 	data_->front_.z = -10.0;
  setLookAt(data_->position_, data_->position_ + data_->front_, data_->up_);
  data_->dl_cam_ = std::make_shared<DisplayList>();
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  data_->proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up){
  data_->look_at_mat_ = glm::lookAt(eye, center, up);
}

void Camera::render(std::shared_ptr<Node>dl){
  if (!data_->created_dl){
    createDisplayList(dl);
    data_->created_dl = true;
    data_->dl_cam_->execute();
  }
  else
  {
    data_->dl_cam_->update();
    data_->dl_cam_->execute();
  }
  

}

void Camera::cull(){

}

 void Camera::runCommand(OpenGlInterFaz &i)const{

   GLfloat radius = 50.0f;
   GLfloat camX = sin(glfwGetTime()) * radius;
   GLfloat camZ = cos(glfwGetTime()) * radius;
   glm::mat4 view;
   view = glm::lookAt(glm::vec3(position_.x, position_.y, position_.z), data_->front_, glm::vec3(0.0, 1.0, 0.0));
   const float  color[]= { 0 };
   i.useUniformUi("u_texture",0);
   //i.useUnifor3f("color_", color);
	 
	
}

 glm::mat4 Camera::getProyection(){
   return data_->proyection_mat_;
 }
 glm::mat4 Camera::getView(){
   return data_->look_at_mat_;
 }

 void Camera::createDisplayList(std::shared_ptr<Node> node){
   std::shared_ptr<Drawable> t_drawable;
   for (int i = 0; i < node->size();i++){

     t_drawable = node->childAt(i);
     data_->dl_cam_.get()->add( std::make_shared<LoadGeometryCommand>(t_drawable->geometry() ));
     data_->dl_cam_.get()->add(std::make_shared<LoadMaterialCommand>(t_drawable->material()  ));
     data_->dl_cam_.get()->add(std::make_shared<LoadTextureCommand>( t_drawable->material() ));

     data_->dl_cam_.get()->add(std::make_shared<UseGeometryCommand>(t_drawable->geometry()));
     data_->dl_cam_.get()->add(std::make_shared<UseTextureComman>(t_drawable->material() ));
		 data_->dl_cam_.get()->add(std::make_shared<UseMaterialCommand>(t_drawable->material()));

		 mat4 model_node;
		 {
			 model_node = glm::rotate(model_node, node->rotation().x, vec3(1.0, 0.0, 0.0));
			 model_node = glm::rotate(model_node, node->rotation().y, vec3(0.0, 1.0, 0.0));
			 model_node = glm::rotate(model_node, node->rotation().z, vec3(0.0, 0.0, 1.0));
			 model_node = glm::scale(model_node, vec3(2.0, 2.0, 2.0));
			 model_node = glm::translate(model_node, node->position());
		 }

		std::shared_ptr<Camera> t_c = std::make_shared<Camera>(*this);
			 data_->dl_cam_.get()->add(std::make_shared<SetupCameraCommand>(t_c,
																(t_drawable->position()),
																(t_drawable->rotation()),
																(t_drawable->scale()),model_node ));
			 data_->dl_cam_.get()->add(std::make_shared<DrawCommand>(t_drawable->geometry()) );
   }


 }

 mat4 Camera::globalModel(){

	 mat4 t_mat_m;
	 return t_mat_m;
	


 }