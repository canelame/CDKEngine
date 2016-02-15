#include "CDK\node.h"
#include "CDK\light.h"

struct Node::Data{
std::vector<std::shared_ptr<Node>> node_list_;
  bool dirty_node_=true;
  std::shared_ptr<Node> parent_;
  vec3 position_;
  vec3 rotation_;
  vec3 scale_;
  mat4 world_transform_;
  mat4 model_mat_;
  std::vector<std::shared_ptr<Light>>lights;
  std::string name_;

};

Node::Node(){
	data_ = new Data;
  data_->scale_ = vec3(1, 1, 1);
}
Node::~Node(){}
std::shared_ptr<Node> Node::getParent(){
  if (data_->parent_ != nullptr) {
    return data_->parent_;
  }
 return nullptr;
}

void Node::setParent(std::shared_ptr<Node>p){
  data_->parent_ = p;
}
void Node::addChild(std::shared_ptr<Node>d){
  if (d == NULL){
    printf("Error:Geometry empty\n");
    return;
  }
  
  if (this != NULL){
    d->data_->parent_ = std::make_shared<Node>(*this);
    data_->node_list_.push_back(d);
  }
  
}
void Node::removeChild(unsigned int index){
  if (!data_->node_list_.empty()){
    if (index >= data_->node_list_.size() || data_ == NULL)return;
    if (this->data_->node_list_[index]->data_ != nullptr){
      if (data_->parent_ != nullptr){
        data_->parent_->addChild(data_->node_list_[index]);
      }else{
        data_->node_list_[index].~shared_ptr();

      }
    }
    data_->node_list_.erase(data_->node_list_.begin() + index);
  }
}
std::shared_ptr<Node> Node::childAt(int index){
  if (index < data_->node_list_.size()){
    return data_->node_list_.at(index);
  }
	

}

void Node::setPosition(vec3 &data){
  if (this == NULL)return;
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

void Node::setName(const char* name){ data_->name_ = name; }
const char * Node::getName(){
  if (this->data_ != nullptr){
    return data_->name_.c_str();
  }
}


void Node::setScale(const float* data){
	data_->scale_.x = data[0];
	data_->scale_.y = data[1];
	data_->scale_.z = data[2];
  calculateModel();
}
void Node::setScale(vec3 &data){
  data_->scale_ = data;
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
  data_->dirty_node_ = true;
  data_->model_mat_ = glm::translate(mat4(), data_->position_);
  data_->model_mat_ = glm::scale(data_->model_mat_, data_->scale_);
  data_->model_mat_ = glm::rotate(data_->model_mat_, data_->rotation_.x, vec3(1.0, 0.0, 0.0));
  data_->model_mat_ = glm::rotate(data_->model_mat_, data_->rotation_.y, vec3(0.0, 1.0, 0.0));
  data_->model_mat_ = glm::rotate(data_->model_mat_, data_->rotation_.z, vec3(0.0, 0.0, 1.0));

}

void Node::setDirtyNode(bool value){
  data_->dirty_node_ = value;
}
bool Node::getDirtyNode(){
  return data_->dirty_node_;
}

void Node::addLight(std::shared_ptr<Light> l){
  data_->lights.push_back(l);
}

std::vector<std::shared_ptr<Light>> Node::getLigths(){
  return data_->lights;
}
int Node::totalLights(){ return data_->lights.size(); }