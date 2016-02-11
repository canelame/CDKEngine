#include "CDK/frame_buffer.h"
#include "GL/glew.h"
#include "CDK/texture.h"
FrameBuffer::FrameBuffer(){}
FrameBuffer::~FrameBuffer(){}

struct FrameBuffer::Data{
  GLuint program_framebuffer_;
  GLuint id_framebuffer_;
  std::unique_ptr<Texture> texture_framebuffer_;
};
