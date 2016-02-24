#include "CDK/frame_buffer.h"
#include "GL/glew.h"
#include "CDK/texture.h"
#include "CDK/material.h"

struct FrameBuffer::Data{
  GLuint id_framebuffer_;
  std::shared_ptr<Geometry> render_quad_;
  std::shared_ptr<Texture> texture_;
  std::shared_ptr<Material> material_;
  GLuint texture_frame_buffer_id;
  bool loaded = false;
};

FrameBuffer::FrameBuffer(){
  data_->material_ = std::make_shared<Material>(0);
  data_->material_->loadShader("pp_f.glsl", "pp_v.glsl");
  data_->render_quad_ = std::shared_ptr<Geometry>();
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

Texture& FrameBuffer::getTexture(){
  if (data_->texture_ != nullptr){
    return *data_->texture_.get();
  }
}
void FrameBuffer::setId(int val){
  data_->id_framebuffer_ = val;
}
int FrameBuffer::getId(){
  return data_->id_framebuffer_;
}