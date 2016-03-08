#include "CDK/engine_manager.h"
#include "CDK/camera.h"
#include "GLFW\glfw3.h"
#include "CDK/display_list.h"
#include "CDK/input.h"
#include "CDK/task_manager.h"
#include "CDK/gui_interface.h"
struct Camera::Data{

  mat4 proyection_mat_;
  mat4 look_at_mat_;
  vec3 position_;
  vec3 up_;
  vec3 right_;
  vec3 front_;
  bool first_mouse_ = false;
  float last_x_ = 0.0;
  float last_y_ = 0.0;
  float yaw_fps_ = -90.0f;
  float pitch_fps_ = 0.0f;
  float mouseSpeed = 0.1f;
  std::shared_ptr<DisplayList> dl_cam_;
  std::shared_ptr<DisplayList> dl_copy_;
  std::shared_ptr<UpdateDisplay> last_task;
  bool created_dl = false;
  const float fps_speed_move = 0.2;
  bool loaded=false;
};

Camera::Camera(){
  
  data_ = new Data;
 
  data_->position_.x = 0.0; 	data_->position_.y = 0.0; 	data_->position_.z =105.0;
  data_->up_.x = 0; 	data_->up_.y = 1.0; 	data_->up_.z = 0;
  data_->front_.x = 0.0; 	data_->front_.y = 0.0; 	data_->front_.z = -100.0;
  setLookAt(data_->position_, data_->position_ + data_->front_, data_->up_);
  data_->dl_cam_ = std::make_shared<DisplayList>();
  data_->dl_copy_ = std::make_shared<DisplayList>();
}
void Camera::setPosition(vec3 position){
  data_->position_ = position;
}
void Camera::setFront(vec3 front){
  data_->front_ = front;
}

void Camera::setPerspective(float fov, float aspect, float near, float far){
  data_->proyection_mat_ = glm::perspective(fov, aspect, near, far);
}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up){
  data_->look_at_mat_ = glm::lookAt(eye, center, up);
}

void Camera::render(std::shared_ptr<Node>node){
  if (EngineManager::instance().window_size_modified_){
   
    setPerspective(45.0f, EngineManager::instance().width() / EngineManager::instance().height(), 0.1, 10000.0f);
    EngineManager::instance().setWindowModified(false);
  }
  std::shared_ptr<UpdateDisplay> update_task = std::make_shared<UpdateDisplay>(data_->dl_copy_.get(), node, data_->proyection_mat_,data_->look_at_mat_,data_->loaded);

     TaskManager::instance().addTask(update_task);
     if (data_->last_task.get() != nullptr){
       TaskManager::instance().waitTask(*data_->last_task.get());
     }


     data_->last_task = update_task;
    data_->dl_cam_->execute();
     data_->dl_cam_->clear();
     data_->dl_cam_.swap(data_->dl_copy_);
     // GuInterface::instance().draw(node);

 
}
void Camera::FpsCameraUpdate(){
  //KEyboard

  vec3 current_position = data_->position_;
  if (Input::instance().pressKeyA() == true){
    vec3 temp_vector;
    temp_vector = glm::cross(data_->front_, data_->up_);
    temp_vector = glm::normalize(temp_vector);
    temp_vector = temp_vector * data_->fps_speed_move;
    current_position = current_position - temp_vector;
    data_->position_ = current_position;
  }
  if (Input::instance().pressKeyS() == true){
    vec3 temp_vector;
    temp_vector = data_->front_*data_->fps_speed_move;
    current_position = current_position - temp_vector;
    data_->position_ = current_position;
  }

  if (Input::instance().pressKeyD() == true){
    vec3 temp_vector;
    temp_vector = glm::cross(data_->front_, data_->up_);
    temp_vector = glm::normalize(temp_vector);
    temp_vector = temp_vector * data_->fps_speed_move;
    current_position = current_position + temp_vector;
    data_->position_ = current_position;
  }

  if (Input::instance().pressKeyW() == true){
    vec3 temp_vector;
    temp_vector = data_->front_*data_->fps_speed_move;
    current_position = current_position + temp_vector;
    data_->position_ = current_position;

  }
  if (Input::pressSpace()){
    controlMouse();
  }
  setLookAt(data_->position_, data_->position_ + data_->front_, data_->up_);
}

void Camera::controlMouse(){
  //Mouse
  float mx = Input::instance().getMouseX();
  float my = Input::instance().getMouseY();

  if (data_->first_mouse_){
    data_->last_x_ = mx;
    data_->last_y_ = my;
    data_->first_mouse_ = false;
  }

  float x_offset = mx - data_->last_x_;
  float y_offset = my - data_->last_y_;
  data_->last_x_ = mx;
  data_->last_y_ = my;
  x_offset *= data_->mouseSpeed;
  y_offset *= data_->mouseSpeed;

  data_->yaw_fps_ += x_offset;
  data_->pitch_fps_ += y_offset;
  if (data_->pitch_fps_ > 89.0f)
    data_->pitch_fps_ = 89.0f;
  if (data_->pitch_fps_ < -89.0f)
    data_->pitch_fps_ = -89.0f;
  vec3 front;
  front.x = cos(glm::radians(data_->yaw_fps_))*cos(glm::radians(data_->pitch_fps_));
  front.y = -sin(glm::radians(data_->pitch_fps_));
  front.z = sin(glm::radians(data_->yaw_fps_))*cos(glm::radians(data_->pitch_fps_));
  data_->front_ = glm::normalize(front);
 setLookAt(data_->position_, data_->position_ + data_->front_, data_->up_);
}
 glm::mat4 Camera::getProyection(){
   return data_->proyection_mat_;
 }
 glm::mat4 Camera::getView(){
   return data_->look_at_mat_;
 }

 void Camera::setLoaded(bool value){
   data_->loaded = value;
 }

 bool Camera::getLoaded(){
   return data_->loaded;
 }
