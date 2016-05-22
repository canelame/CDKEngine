#include "CDK/engine_manager.h"
#include "CDK/opengl_interfaz.h"
EngineManager* EngineManager::instance_ = nullptr;
EngineManager& EngineManager::instance(){
  if (instance_ == NULL){
    instance_ = new EngineManager();
  }
  return *instance_;
}
struct EngineManager::Data{
  std::shared_ptr<ShadowMapMaterial>  shadow_shader_;
  std::shared_ptr<CubeShadowMaterial>  shadow_points_shader_;
 Composer * main_composer_;
  int width_;
  int height_;

};
EngineManager::EngineManager(){

  data_ = new Data();

}
void EngineManager::init(){
    data_->width_ = 0;
  data_->height_ = 0;
  data_->shadow_shader_ = std::make_shared<ShadowMapMaterial>();
  data_->shadow_points_shader_ = std::make_shared<CubeShadowMaterial>();
  last_display_list_ = std::make_shared<DisplayList>();
 //main_composer_ = std::make_shared < Composer >() ;
}
int EngineManager::width(){
  return data_->width_;
}

int EngineManager::height(){
  return data_->height_;
}

void EngineManager::setWidth(int w){
  data_->width_ = w;
}

void EngineManager::setHeight(int h){
  data_->height_ = h;
}

void EngineManager::setWindowModified(bool value){
  window_size_modified_ = value;
}

ShadowMapMaterial* EngineManager::getShadowMap(){
  return data_->shadow_shader_.get();

}
CubeShadowMaterial* EngineManager::getCubeShadowMap(){
  return data_->shadow_points_shader_.get();
}

Composer * EngineManager::getMainComposer(){
  if (data_->main_composer_ != nullptr){
  return (Composer*)data_->main_composer_;
  }
  
}

void EngineManager::setMainComposer( const Composer* comp){
  if (data_->main_composer_ == nullptr){
    data_->main_composer_ = (Composer* )comp;
  }
 
}