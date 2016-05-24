#include "post_process.h"
#include "CDK/engine_manager.h"
#include "CDK/opengl_interfaz.h"
#include "CDK/frame_buffer.h"
#include "CDK/texture.h"
#include "CDK/public_opengl_library.h"
PostProcess::PostProcess(){
  material_ = std::make_shared<Material>();

  frame_buff_ = std::make_shared<FrameBuffer>();
  frame_buff_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_ColorAttachment);
  render_quad_ = std::make_shared<Geometry>();
  render_quad_->createQuad();
  
}

Material& PostProcess::getMaterial(){
  return *material_.get();
}



FrameBuffer& PostProcess::getFrameBuffer(){
  return *frame_buff_.get();
}


std::shared_ptr<Buffer> PostProcess::getQuad(){
  return render_quad_->getBuffer();
}
