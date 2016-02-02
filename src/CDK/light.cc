#include "CDK/light.h"


Light::Light(){
  l_type = T_DIRECTION_LIGHT;
  sh_ = 32.0f;
}
Light::~Light(){

}
Light::Light(const Light& l){
  *this = l;
}

void Light::setPosition(vec3 position){
  position_ = position;
}

void Light::setDifusseColor(vec3 df){
  difusse_color_ = df;
}

void Light::setSpecularColor(vec3 df){
  specular_color_ = df;
}

void Light::setAmbientColor(vec3 ac){
  ambient_color_ = ac;
}

void Light::setTypeLight(Light::LightType lt){
  l_type = lt;
}

vec3 Light::getPosition(){
  return position_;
}


vec3 Light::getDirection(){
  return direction_;
}

vec3 Light::getDiffuseColor(){
  return difusse_color_;
}

vec3 Light::getAmbientColor(){
  return ambient_color_;
}

vec3 Light::getSpecularColor(){
  return specular_color_;
}

float Light::getShinenes(){
  return sh_;
}

Light::LightType Light::getType(){
return l_type;
}