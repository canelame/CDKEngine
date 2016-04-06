#include "CDK/directional_light.h"
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
DirectionalLight::DirectionalLight(){
  setTypeLight(LightType::T_DIRECTION_LIGHT);
  shadow_depth_buffer_ = std::make_shared<FrameBuffer>();
  shadow_depth_buffer_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_DepthAttachment);
}
void DirectionalLight::setPosition(vec3 p){
  Light::setPosition(p);
  
  mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
  mat4 light_view = glm::lookAt(getPosition(), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
  mat4 light_space = light_projection * light_view;

}