#include "CDK/engine_manager.h"

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
  current_render_target_ =0;
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

void EngineManager::setRenderTarget(FrameBuffer*fb){
  current_render_target_ = fb;
}

FrameBuffer* EngineManager::getRenderTarget(){
  return current_render_target_;
}

void EngineManager::addUniform(char*name, int value){
  loaded_uniforms_.insert(std::pair<char*, int>(name, value));
}

int EngineManager::getUniform(char*name){
  loaded_uniforms_.find(name);
}