#include "post_process.h"
#include "CDK/engine_manager.h"
#include "CDK/opengl_interfaz.h"
#include "CDK/frame_buffer.h"
#include "CDK/texture.h"


PostProcess::PostProcess(){
  material_ = std::make_shared<Material>();
  render_quad_ = std::make_shared<Geometry>();
  frame_buff_ = std::make_shared<FrameBuffer>();
  frame_buff_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_DepthAttachment);
  material_->loadShader("shaders/shadow_v.glsl", "shaders/shadow_f.glsl","");
  render_quad_->createQuad();
}

Material& PostProcess::getMaterial(){
  return *material_.get();
}

std::shared_ptr<Buffer> PostProcess::getQuad(){
  return render_quad_->getBuffer();
}



void PostProcess::begin(){

  glViewport(0, 0, 1024, 1024);
  OpenGlInterFaz::instance().bindFrameBuffer(frame_buff_->getId(), FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
  glClear(GL_DEPTH_BUFFER_BIT);
 
}
void PostProcess::end(){
 // OpenGlInterFaz::instance().bindFrameBuffer(0,FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
  /*glUseProgram(material_->getProgram());
  OpenGlInterFaz::instance().useTexture(0, 0, "", frame_buff_->getTexture().get()->getID());
  Buffer * buff = render_quad_->getBuffer().get();
  OpenGlInterFaz::instance().drawGeometry((unsigned int)buff->getVAO(),6);*/
}