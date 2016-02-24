#include "CDK/engine_manager.h"

EngineManager* EngineManager::instance_ = nullptr;
EngineManager& EngineManager::instance(){
  if (instance_ == nullptr){
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

void EngineManager::setRenderTarget(int rt){
  current_render_target_ = rt;
}