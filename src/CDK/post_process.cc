#include "post_process.h"
#include "CDK/engine_manager.h"
#include "CDK/opengl_interfaz.h"
#include "CDK/frame_buffer.h"
#include "CDK/texture.h"
#include "CDK/geometry.h"

PostProcess::PostProcess(){
  material_ = std::make_shared<Material>(0);
  render_quad_ = std::make_shared<Geometry>();
  frame_buff_ = std::make_shared<FrameBuffer>();
  material_->loadShader("shaders/molon_f.glsl", "shaders/pp_v.glsl");
  render_quad_->createQuad();
}

Material& PostProcess::getMaterial(){
  return *material_.get();
}

std::shared_ptr<Buffer> PostProcess::getQuad(){
  return render_quad_->getBuffer();
}



void PostProcess::begin(){
  EngineManager::instance().setRenderTarget(frame_buff_.get());
  if (!frame_buff_->isLoaded()){
    OpenGlInterFaz::instance().createFrameBuffer(*frame_buff_.get());
    OpenGlInterFaz::instance().loadMaterial(material_->getVertexData().c_str() ,material_->getFragmentData().c_str());
    OpenGlInterFaz::instance().loadBuffer(render_quad_->getBuffer().get());
  }
  OpenGlInterFaz::instance().bindFrameBuffer(frame_buff_->getId());
}
void PostProcess::end(){
  glUseProgram(material_->getProgram());
  OpenGlInterFaz::instance().useTexture(0, 0, "", frame_buff_->getTexture().get()->getID());
  OpenGlInterFaz::instance().useGeometry((unsigned int)render_quad_->getBuffer()->getIndexesT());
  EngineManager::instance().setRenderTarget(nullptr);
}