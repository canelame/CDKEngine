#include "CDK/frame_buffer.h"
#include "GL/glew.h"
#include "CDK/texture.h"
#include "CDK/material.h"
#include "CDK/engine_manager.h"


struct FrameBuffer::Data{
  GLuint id_framebuffer_;
  std::shared_ptr<Geometry> render_quad_;
  std::shared_ptr<Texture> texture_;
  std::shared_ptr<Material> material_;
  GLuint texture_frame_buffer_id;
  bool loaded = false;
  FrameBuffer::kFrameBufferAttachments attachment;
};

enum FrameBuffer::kFrameBufferAttachments{

  kFrameBufferAttachments_Depth=0,
  kFrameBufferAttachments_Stencil,
  kFrameBufferAttachments_Depth_Stencil,
  kFrameBufferAttachments_Color

};

FrameBuffer::FrameBuffer(){
  data_ = new Data;
  data_->material_ = std::make_shared<Material>(0);
  data_->material_->loadShader("shaders/molon_f.glsl", "shaders/pp_v.glsl");
  data_->render_quad_ = std::make_shared<Geometry>();
  data_->texture_ = std::make_shared<Texture>();
  data_->texture_->loadTexture("", "fb");
  data_->render_quad_->createQuad();
}
int FrameBuffer::getProgram(){
  return data_->material_->getProgram();
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

void FrameBuffer::begin(){
  EngineManager::instance().setRenderTarget(this);
}

void FrameBuffer::end(){
  EngineManager::instance().setRenderTarget(nullptr);
}
Material& FrameBuffer::getMaterial(){
  return *data_->material_.get();
}

std::shared_ptr<Buffer> FrameBuffer::getQuad(){
  return data_->render_quad_->getBuffer();
}

FrameBuffer::kFrameBufferAttachments FrameBuffer::getAttachment(){
  return data_->attachment;
}

void FrameBuffer::setAttachment(FrameBuffer::kFrameBufferAttachments attach){
  data_->attachment = attach;
}