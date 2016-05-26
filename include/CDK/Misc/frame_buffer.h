#ifndef __H_FRAME_BUFFER__
#define __H_FRAME_BUFFER__

#include "CDK/Resources/geometry.h"
#include "CDK/Resources/texture.h"

class Material;
class FrameBuffer{

public:
  /**
  * Rememeber to set the Framebuffer attachment
  */
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
  /**
  *@brief Initilize framebuffer
  */
  void initFrameBuffer();
  /**
  @param Get if the framebuffer has been loaded to GPU
  */
  bool isLoaded();
  /**
  @brief Set true when  frameBuffer has been loaded to GPu
  @param value
  */
  void setLoaded(bool loaded);
  /**
  @brief Set framebuffer id when its loaded to GPU
  @param Framebuffer id
  */
  void setId(int id);
  /**
  @brief Get framebuffer id 
  @return Framebuffer id
  */
  int getId();
  /**
  @brief Get texture attached to framebuffer
  @return Framebuffer 
  */
  std::shared_ptr<Texture> getTexture();
  /**
  @brief Get framebuffer attachments type
  @return Attachment type
  */
  kFrameBufferAttachment getAttachment();
  /**
  @brief Set framebuffer attachments type
  @param attach Attachment type
  */
  void setAttachment(FrameBuffer::kFrameBufferAttachment attach);

private:
  struct Data;
  Data *data_;
};

#endif