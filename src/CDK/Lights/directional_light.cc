#include "CDK/Lights/directional_light.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
DirectionalLight::DirectionalLight(){
  setTypeLight(LightType::T_DIRECTION_LIGHT);
  shadow_depth_buffer_ = std::make_shared<FrameBuffer>();
  shadow_depth_buffer_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_DepthAttachment);
  type = 2;
}
void DirectionalLight::setPosition(vec3 p){
  Light::setPosition(p);
  
  mat4 light_projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 20.5f);
  mat4 light_view = glm::lookAt(getPosition(), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
  mat4 light_space = light_projection * light_view;
  light_proyection_ = light_space;

}

mat4 DirectionalLight::getLightProyection(){
  return light_proyection_;
}

FrameBuffer* DirectionalLight::getShadowMap(){
  return shadow_depth_buffer_.get();
}