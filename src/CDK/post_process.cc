#include "post_process.h"
#include "CDK/engine_manager.h"
#include "CDK/opengl_interfaz.h"
#include "CDK/frame_buffer.h"
#include "CDK/texture.h"
#include "CDK/public_opengl_library.h"
PostProcess::PostProcess(){
  material_ = std::make_shared<Material>();
  render_quad_ = std::make_shared<Geometry>();
  frame_buff_ = std::make_shared<FrameBuffer>();
  frame_buff_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_ColorAttachment);
  material_->loadShader("shaders/pp_v.glsl", "shaders/pp_f.glsl","");
  render_quad_->createQuad();
}

Material& PostProcess::getMaterial(){
  return *material_.get();
}

std::shared_ptr<Buffer> PostProcess::getQuad(){
  return render_quad_->getBuffer();
}

FrameBuffer& PostProcess::getFrameBuffer(){
  return *frame_buff_.get();
}

void PostProcess::end(){
  OpenGlInterFaz::instance().bindFrameBuffer(0,FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
  OpenglInterfazPublic::instace().useMaterial(material_->getProgram());

  OpenGlInterFaz::instance().useMaterial(material_.get());
  int t_pp = material_->getUniformLocation("u_pp_texture");
  OpenGlInterFaz::instance().useUniformI(t_pp, 0);
  OpenGlInterFaz::instance().useTexture(0, frame_buff_->getTexture()->getID());
  Buffer * buff = render_quad_->getBuffer().get();
  if (buff->isDirty()){
    OpenGlInterFaz::instance().loadBuffer(buff);
    buff->setDirty(false);
  }
  OpenGlInterFaz::instance().drawGeometry((unsigned int)buff->getVAO(),6);
}