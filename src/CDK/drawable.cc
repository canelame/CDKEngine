#include "CDK/drawable.h"
struct Drawable::Data{
	std::shared_ptr<Geometry> drawable_geometry_;
	std::shared_ptr<Material> drawable_material_;
	vec3 position_;
	vec3 rotation_;
	vec3 scale_;
};
Drawable::Drawable(){
	data_ = new Data;
}

void Drawable::setGeometry(std::shared_ptr<Geometry>geo){
	data_->drawable_geometry_ = geo;
}
void Drawable::setMaterial(std::shared_ptr<Material>mat){
	data_->drawable_material_ = mat;
}

void Drawable::setPosition(vec3 &data){
	data_->position_ = data;
}
void Drawable::setPosition(const float* data){
	data_->position_.x = data[0];
	data_->position_.y = data[1];
	data_->position_.z = data[2];
}

void Drawable::setRotation(vec3 &data){
	data_->rotation_ = data;
}
void Drawable::setRotation(const float* data){
	data_->rotation_.x = data[0];
	data_->rotation_.y = data[1];
	data_->rotation_.z = data[2];
}

void Drawable::setScale(vec3 &data){
	data_->scale_ = data;
}
void Drawable::setScale(const float* data){
	data_->scale_.x = data[0];
	data_->scale_.y = data[1];
	data_->scale_.z = data[2];
}