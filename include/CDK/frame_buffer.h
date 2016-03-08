#ifndef __H_FRAME_BUFFER__
#define __H_FRAME_BUFFER__

#include "CDK/geometry.h"
#include "CDK/texture.h"

class Material;
class FrameBuffer{

public:
  enum kFrameBufferAttachment{
  
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


private:
  struct Data;
  Data *data_;
};

#endif