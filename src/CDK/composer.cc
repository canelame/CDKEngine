#include "CDK/composer.h"
#include "CDK/engine_manager.h"
Composer::Composer(){
  init();
}

Composer::~Composer(){

}
void Composer::addEffect(std::shared_ptr<PostProcess> new_effect){
  effects_list_.push_back(std::move(new_effect));
}
void Composer::compose(DisplayList * dl_to_update){
  for (int i = 0; i < effects_list_.size(); i++){
    
  }
}
void Composer::init(){
  EngineManager::instance().setMainComposer((this));
}

PostProcess * Composer::getEffect(int index){
  return effects_list_.at(index).get();
}
int Composer::size(){
  return effects_list_.size();
}