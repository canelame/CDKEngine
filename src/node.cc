#include "CDK\node.h"


struct Node::Data{
	std::vector<std::shared_ptr<Node>> node_list_;
	vec3 position_;
	vec3 rotation_;
	vec3 scale_;
  bool dirty_=true;
  mat4 world_transform_;
  std::shared_ptr<Node> parent_;
};
struct Node::Transform{
  Transform(){
    d = std::make_unique < Data >() ;
  }
  Data combine(Transform &transform_m){
    transform_m.d.get()->world_transform_ = glm::rotate(transform_m.d.get()->world_transform_,
                                            transform_m.d.get()->rotation_.x, vec3(1.0, 0.0, 0.0));
    transform_m.d.get()->world_transform_ = glm::rotate(transform_m.d.get()->world_transform_,
                                            transform_m.d.get()->rotation_.y, vec3(0.0, 1.0, 0.0));
    transform_m.d.get()->world_transform_ = glm::rotate(transform_m.d.get()->world_transform_,
                                            transform_m.d.get()->rotation_.z, vec3(0.0, 0.0, 1.0));
    transform_m.d.get()->world_transform_ = glm::scale(transform_m.d.get()->world_transform_,
                                             transform_m.d.get()->scale_);
    transform_m.d.get()->world_transform_ = glm::translate(transform_m.d.get()->world_transform_, 
                                            transform_m.d.get()->position_);
    return  *transform_m.d.get();
  }
  std::unique_ptr<Data> d;
};
Node::Node(){
	data_ = new Data;
	
}
Node::~Node(){}
std::shared_ptr<Node> Node::getParent(){
  return data_->parent_;
}

void Node::setParent(std::shared_ptr<Node>p){
  data_->parent_ = p;
}
void Node::addChild(std::shared_ptr<Node>d){
 
  data_->node_list_.push_back(d);
  data_->parent_ = std::make_shared<Node>(*this);
  
}

std::shared_ptr<Node> Node::childAt(int index){
	return data_->node_list_.at(index);

}

void Node::setPosition(vec3 &data){
	data_->position_ = data;
}
void Node::setPosition(const float* data){
	data_->position_.x = data[0];
	data_->position_.y = data[1];
	data_->position_.z = data[2];
}

void Node::setRotation(vec3 &data){
	data_->rotation_ = data;
}
void Node::setRotation(const float* data){
	data_->rotation_.x = data[0];
	data_->rotation_.y = data[1];
	data_->rotation_.z = data[2];
}

void Node::setScale(vec3 &data){
	data_->scale_ = data;
}
void Node::setScale(const float* data){
	data_->scale_.x = data[0];
	data_->scale_.y = data[1];
	data_->scale_.z = data[2];
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