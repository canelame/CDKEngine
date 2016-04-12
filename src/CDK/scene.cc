#include "CDK/scene.h"
#include "CDK/engine_manager.h"
Scene::Scene(){
  root_ = std::make_shared<Node>();
  camera_ = std::make_shared<Camera>();

  directional_light_ = std::make_shared < DirectionalLight>();
  directional_light_->setPosition(vec3(0.0, -4.0, -1.0));
  directional_light_->setAmbientColor(vec3(0.0, 0.0, 0.0));
  directional_light_->setSpecularColor(vec3(0.0, 0.0, 0.0));
  directional_light_->setDifusseColor(vec3(1.0, 1.0, 1.0));

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

  camera_->render(this);
}