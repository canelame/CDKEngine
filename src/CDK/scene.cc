#include "CDK/scene.h"
#include "CDK/engine_manager.h"
Scene::Scene(){
  root_ = std::make_shared<Node>();
  camera_ = std::make_shared<Camera>();

  directional_light_ = std::make_shared < Light>();
  directional_light_->setPosition(vec3(-2.0, 4.0, -1.0));
  directional_light_->setAmbientColor(vec3(1.0, 1.0, 1.0));
  directional_light_->setSpecularColor(vec3(1.0, 1.0, 1.0));
  directional_light_->setDifusseColor(vec3(1.0, 1.0, 1.0));
  directional_light_->setTypeLight(Light::LightType::T_DIRECTION_LIGHT);
}

void Scene::addChild(std::shared_ptr<Node> child){
  root_->addChild(child);
}
/**
*/
void Scene::addLight(std::shared_ptr<Light>light){
  if (light->getType() != Light::LightType::T_DIRECTION_LIGHT){
    lights_.push_back(light);
  }
}

void Scene::render(){
  mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
  mat4 light_view = glm::lookAt(directional_light_->getPosition(), vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
  mat4 light_space = light_projection * light_view;
  OpenGlInterFaz::instance().setLightProyection(light_space);
  camera_->render(this);
}