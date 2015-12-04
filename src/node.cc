#include "CDK\node.h"


struct Node::Data{
std::vector<std::shared_ptr<Node>> node_list_;
  bool dirty_=true;
  std::shared_ptr<Node> parent_;
  vec3 position_;
  vec3 rotation_;
  vec3 scale_;
  mat4 world_transform_;
  mat4 model_mat_;
};

Node::Node(){
	data_ = new Data;
  data_->scale_ = vec3(1, 1, 1);
}
Node::~Node(){}
std::shared_ptr<Node> Node::getParent(){
  return data_->parent_;
}

void Node::setParent(std::shared_ptr<Node>p){
  data_->parent_ = p;
}
void Node::addChild(std::shared_ptr<Node>d){
  d->data_->parent_ = std::make_shared<Node>(*this);
  data_->node_list_.push_back(d);

  
}

std::shared_ptr<Node> Node::childAt(int index){
	return data_->node_list_.at(index);

}

void Node::setPosition(vec3 &data){
  data_->position_ = data;
  calculateModel();
}
void Node::setPosition(const float* data){
	
	data_->position_.x = data[0];
	data_->position_.y = data[1];
	data_->position_.z = data[2];
  calculateModel();
}

void Node::setRotation(vec3 &data){
	data_->rotation_ = data;
  calculateModel();
}
void Node::setRotation(const float* data){
	data_->rotation_.x = data[0];
	data_->rotation_.y = data[1];
	data_->rotation_.z = data[2];
  calculateModel();
}

void Node::setScale(vec3 &data){
	data_->scale_ = data;
  calculateModel();
}
void Node::setScale(const float* data){
	data_->scale_.x = data[0];
	data_->scale_.y = data[1];
	data_->scale_.z = data[2];
  calculateModel();
}



int Node::size(){
	return data_->node_list_.size();
}

vec3 Node::position(){
	return data_->position_;
}
vec3 Node::rotation(){
	return data_->rotation_;
}

vec3 Node::scale(){
	return data_->scale_;
}

void Node::combine(std::shared_ptr<Node> c_v){
  mat4 temp_mat_o;
  if (c_v != nullptr){
    temp_mat_o = glm::rotate(temp_mat_o, c_v->data_->rotation_.x, vec3(1.0, 0.0, 0.0));
    temp_mat_o = glm::rotate(temp_mat_o, c_v->data_->rotation_.y, vec3(0.0, 1.0, 0.0));
    temp_mat_o = glm::rotate(temp_mat_o, c_v->data_->rotation_.z, vec3(0.0, 0.0, 1.0));
    temp_mat_o = glm::scale(temp_mat_o, c_v->data_->scale_);
    temp_mat_o = glm::translate(temp_mat_o, c_v->data_->position_);

    data_->world_transform_ *= temp_mat_o;
  }
 
  
}

mat4 Node::modelMat(){
	return data_->model_mat_;
}
mat4 Node::worldMat(){
  return data_->world_transform_;
}

void Node::setWorldMat(mat4 w_m){
  data_->world_transform_ = w_m;
}
void Node::setModelMat(mat4 w_m){
  data_->model_mat_ = w_m;
}
void  Node::calculateModel(){

  data_->model_mat_ = glm::translate(mat4(), data_->position_);
  data_->model_mat_ = glm::scale(data_->model_mat_, data_->scale_);
  data_->model_mat_ = glm::rotate(data_->model_mat_, data_->rotation_.x, vec3(1.0, 0.0, 0.0));
  data_->model_mat_ = glm::rotate(data_->model_mat_, data_->rotation_.y, vec3(0.0, 1.0, 0.0));
  data_->model_mat_ = glm::rotate(data_->model_mat_, data_->rotation_.z, vec3(0.0, 0.0, 1.0));

 /// data_->world_transform_ *= data_->model_mat_;



}