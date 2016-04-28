#include "CDK/engine_manager.h"
#include "CDK/opengl_interfaz.h"
EngineManager* EngineManager::instance_ = nullptr;
EngineManager& EngineManager::instance(){
  if (instance_ == NULL){
    instance_ = new EngineManager();
  }
  return *instance_;
}

void EngineManager::init(){
  width_ = 0;
  height_ = 0;

  
  shadow_shader_ = std::make_shared<Material>();
  shadow_shader_->loadShader("shaders/shadow_v.glsl", "shaders/shadow_f.glsl", "");

  shadow_points_shader_ = std::make_shared<Material>();
  shadow_points_shader_->loadShader("shaders/point_shadow_v.glsl", "shaders/point_shadow_f.glsl", "shaders/point_shadow_geo.glsl");

}
int EngineManager::width(){
  return width_;
}

int EngineManager::height(){
  return height_;
}

void EngineManager::setWidth(int w){
  width_ = w;
}

void EngineManager::setHeight(int h){
  height_ = h;
}

void EngineManager::setWindowModified(bool value){
  window_size_modified_ = value;
}

int EngineManager::getUniform(char*name){
 // loaded_uniforms_.find(name);
  return 0;
}

