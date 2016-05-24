#include "CDK/composer.h"
#include "CDK/engine_manager.h"
#define TEXTURE_LOCATION 0
Composer::Composer(){
  init();
}

Composer::~Composer(){

}
void Composer::addEffect(std::shared_ptr<PostProcess> new_effect){
  if (effects_list_.size() <= 3){
    effects_list_.push_back(std::move(new_effect));
  }
  else{
    printf("Error to add effect, max number of effects available\n");
  }
  
}

void Composer::init(){
  composer_material_ = std::make_shared<ComposerMaterial>();

  render_quad_ = std::make_shared<Geometry>();
  render_quad_->createQuad();
  final_target_ = std::make_shared<FrameBuffer>();
  final_target_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_ColorAttachment);
  
  aux_target_ = std::make_shared<FrameBuffer>();
  aux_target_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_ColorAttachment);
  EngineManager::instance().setMainComposer((this));
}

PostProcess * Composer::getEffect(int index){
  return effects_list_.at(index).get();
}
int Composer::size(){
  return effects_list_.size();
}

void Composer::render(){
  


  if (composer_material_->is_compiled_ == false){
   composer_material_->setProgram( OpenGlInterFaz::instance().loadMaterial(composer_material_.get()));
  }

  for (int i = 0; i < effects_list_.size(); i++){
    Material * mat = &effects_list_[i]->getMaterial();
    if (mat->is_compiled_ == false){
      OpenGlInterFaz::instance().loadMaterial(mat);
    }
    FrameBuffer * fb =& effects_list_[i]->getFrameBuffer();
    if (fb->isLoaded() == false){
      OpenGlInterFaz::instance().createFrameBuffer(*fb,true);
    }

    OpenGlInterFaz::instance().bindFrameBuffer(effects_list_[i]->getFrameBuffer().getId(), FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);

    OpenGlInterFaz::instance().useMaterial(mat);
    int pos_texture0 = mat->getUniformLocation("u_wb_texture");

    if (pos_texture0 >= 0){
      OpenGlInterFaz::instance().useUniformI(pos_texture0, TEXTURE_LOCATION + 0);
      //OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 0, effects_list_[0]->getFrameBuffer().getTexture()->getID());
      OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 0, aux_target_->getTexture()->getID());
    }

    Buffer * buff = effects_list_[i]->getQuad().get();
    if (buff->isDirty()){
      OpenGlInterFaz::instance().loadBuffer(buff);

      buff->setDirty(false);
    }
    OpenGlInterFaz::instance().drawGeometry((unsigned int)buff->getVAO(), 6);

  }
  glViewport(0, 0, 1024, 2014);
  
  int total_pos = composer_material_->getUniformLocation("total");
  if (total_pos >= 0){
    OpenGlInterFaz::instance().useUniformI(total_pos, effects_list_.size());
  }

  OpenGlInterFaz::instance().bindFrameBuffer(0, FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  OpenGlInterFaz::instance().useMaterial(composer_material_.get());
  int pos_texture0 = composer_material_->getUniformLocation("u_pp_texture0");

  if (pos_texture0 >= 0){
    OpenGlInterFaz::instance().useUniformI(pos_texture0, TEXTURE_LOCATION + 0);
    OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 0, effects_list_[0]->getFrameBuffer().getTexture()->getID());
   // OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 0, aux_target_->getTexture()->getID());
  }

  int pos_texture1 = composer_material_->getUniformLocation("u_pp_texture1");
  if (pos_texture1 >= 0){
    OpenGlInterFaz::instance().useUniformI(pos_texture1, TEXTURE_LOCATION + 1);
    OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 1, effects_list_[1]->getFrameBuffer().getTexture()->getID());
  }

  Buffer * buff = render_quad_->getBuffer().get();
  if (buff->isDirty()){
    OpenGlInterFaz::instance().loadBuffer(buff);

    buff->setDirty(false);
  }
  OpenGlInterFaz::instance().drawGeometry((unsigned int)buff->getVAO(), 6);

  /*int total_pos = composer_material_->getUniformLocation("total");
  if (total_pos >= 0){
    OpenGlInterFaz::instance().useUniformI(total_pos,effects_list_.size());
  }
 int pos_texture0 = composer_material_->getUniformLocation("u_pp_texture0");
  if (pos_texture0 >= 0){
    OpenGlInterFaz::instance().useUniformI(pos_texture0,TEXTURE_LOCATION+0);
    //OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 0, effects_list_[0]->getFrameBuffer().getTexture()->getID());
    OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 0, aux_target_->getTexture()->getID());
  }
  int pos_texture1 = composer_material_->getUniformLocation("u_pp_texture1");
  if (pos_texture1 >= 0){
    OpenGlInterFaz::instance().useUniformI(pos_texture1, TEXTURE_LOCATION + 1);
    OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 1, effects_list_[0]->getFrameBuffer().getTexture()->getID());
  }
  int pos_texture2 = composer_material_->getUniformLocation("u_pp_texture2");
  if (pos_texture2 >= 0){
    OpenGlInterFaz::instance().useUniformI(pos_texture2, TEXTURE_LOCATION + 2);
    OpenGlInterFaz::instance().useTexture(TEXTURE_LOCATION + 2, effects_list_[0]->getFrameBuffer().getTexture()->getID());
  }*/



}

std::shared_ptr<Buffer> Composer::getQuad(){
  return render_quad_->getBuffer();
}