#ifndef __H_FRAME_BUFFER__
#define __H_FRAME_BUFFER__

#include "CDK/geometry.h"
#include "CDK/texture.h"

class Material;
class FrameBuffer{

public:
  enum kFrameBufferAttachment{
    kFrameBufferAttachment_ColorAttachment=0,
    kFrameBufferAttachment_DepthAttachment,
    kFrameBufferAttachment_StencilAttachment,
    kFrameBufferAttachment_DepthStencilAttachment,
    kFrameBufferAttachment_None
  };

  enum  kFramebufferBindType
  {
    kFramebufferBindType_FrameBuffer=0,
    kFramebufferBindType_Draw ,
    kFramebufferBindType_Read,
    kFramebufferBindType_None
  };

  FrameBuffer();
  ~FrameBuffer(){};
  FrameBuffer(const FrameBuffer&);
  void initFrameBuffer();
  bool isLoaded();
  void setLoaded(bool loaded);
  void setId(int id);
  int getId();

  std::shared_ptr<Texture> getTexture();
  kFrameBufferAttachment getAttachment();
  void setAttachment(FrameBuffer::kFrameBufferAttachment attach);
  /**
  */

private:
  struct Data;
  Data *data_;
};

#endif