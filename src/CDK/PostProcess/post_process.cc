#include "CDK/PostProcess/post_process.h"
#include "CDK/Core/engine_manager.h"
#include "CDK/Core/opengl_interfaz.h"
#include "CDK/Misc/frame_buffer.h"
#include "CDK/Resources/texture.h"
#include "CDK/Misc/public_opengl_library.h"
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
