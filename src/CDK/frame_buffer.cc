#include "CDK/frame_buffer.h"
#include "GL/glew.h"


#include "CDK/engine_manager.h"


struct FrameBuffer::Data{
  GLuint id_framebuffer_;
  std::shared_ptr<Texture> texture_;
  bool loaded = false;
  FrameBuffer::kFrameBufferAttachment attachment;
};

FrameBuffer::FrameBuffer(){
  data_ = new Data;
  data_->texture_ = std::make_shared<Texture>();
  data_->texture_->loadTexture("","fb");
  data_->attachment = kFrameBufferAttachment::kFrameBufferAttachment_None;
}

void FrameBuffer::initFrameBuffer(){
  
}
bool FrameBuffer::isLoaded(){
  return data_->loaded;
}

void FrameBuffer::setLoaded(bool value){
  data_->loaded = value;
}

std::shared_ptr<Texture> FrameBuffer::getTexture(){
  if (data_->texture_ != nullptr){
    return data_->texture_;
  }
}
void FrameBuffer::setId(int val){
  data_->id_framebuffer_ = val;
}
int FrameBuffer::getId(){
  return data_->id_framebuffer_;
}

FrameBuffer::kFrameBufferAttachment FrameBuffer::getAttachment(){
  return data_->attachment;
}

void FrameBuffer::setAttachment(FrameBuffer::kFrameBufferAttachment attach){
  data_->attachment = attach;
}