#include "CDK/light.h"

struct Light::Data{

  vec3 position_;
  vec3 direction_;
  vec3 difusse_color_;
  vec3 specular_color_;
  vec3 ambient_color_;
  float sh_;
  LightType l_type;
  bool loaded;
};
Light::Light(){
  data_ = new Data;
  data_->l_type = T_DIRECTION_LIGHT;
  data_->sh_ = 32.0f;
  data_->loaded = false;
}
Light::~Light(){

}
Light::Light(const Light& l){
  *this = l;
}

void Light::setPosition(vec3 position){
  data_->position_ = position;
}

void Light::setDifusseColor(vec3 df){
  data_->difusse_color_ = df;
}

void Light::setSpecularColor(vec3 df){
  data_->specular_color_ = df;
}

void Light::setAmbientColor(vec3 ac){
  data_->ambient_color_ = ac;
}

void Light::setTypeLight(Light::LightType lt){
  data_->l_type = lt;
}

vec3 Light::getPosition(){
  return data_->position_;
}


vec3 Light::getDirection(){
  return data_->direction_;
}

vec3 Light::getDiffuseColor(){
  return data_->difusse_color_;
}

vec3 Light::getAmbientColor(){
  return data_->ambient_color_;
}

vec3 Light::getSpecularColor(){
  return data_->specular_color_;
}

float Light::getShinenes(){
  return data_->sh_;
}

Light::LightType Light::getType(){
  return data_->l_type;
}
void Light::setLoaded(bool value){
  data_->loaded = value;
}

bool Light::getLoaded(){
  return data_->loaded;
}