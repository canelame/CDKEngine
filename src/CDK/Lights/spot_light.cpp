#include "CDK/Lights/spot_light.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
SpotLight::SpotLight(){
  setTypeLight(LightType::T_SPOT_LIGHT);
  shadow_depth_buffer_ = std::make_shared<FrameBuffer>();
  shadow_depth_buffer_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_DepthAttachment);
}
void SpotLight::setPosition(vec3 p){
  Light::setPosition(p);
  mat4 light_projection = glm::perspective(90.0f,1024.0f/1024.0f  , near_, far_);
  mat4 light_view = glm::lookAt(getPosition(), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
  mat4 light_space = light_projection * light_view;
  light_proyection_ = light_space;

}

mat4 SpotLight::getLightProyection(){
  return light_proyection_;
}

FrameBuffer* SpotLight::getShadowMap(){
  return shadow_depth_buffer_.get();
}

void SpotLight::setFar(float new_far){
   far_ =  new_far;
}
void SpotLight::setNear(float new_near){
   near_ = new_near;
}

void SpotLight::setDirection(vec3 new_ditection){
  direction_ = new_ditection;
}
vec3 SpotLight::getDirection(){
  return direction_;
}
void SpotLight::setConeAngle(float new_angle){
  cone_angle_ = new_angle;
}
float SpotLight::getConeAngle(){
  return cone_angle_;
}
