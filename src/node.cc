#include "CDK\node.h"


struct Node::Data{
	std::vector<std::shared_ptr<Drawable>> node_list_;
	vec3 position_;
	vec3 rotation_;
	vec3 scale_;

};

Node::Node(){
	data_ = new Data;
	
}

void Node::addChild(std::shared_ptr<Drawable>){

}

std::shared_ptr<Drawable> Node::childAt(int index){
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