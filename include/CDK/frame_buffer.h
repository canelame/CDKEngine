#ifndef __H_FRAME_BUFFER__
#define __H_FRAME_BUFFER__

#include "CDK/geometry.h"

class Texture;
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
  Material& getMaterial();
  std::shared_ptr<Texture> getTexture();
  std::shared_ptr<Buffer> getQuad();
  int getProgram();
  void begin();
  void end();

private:
  struct Data;
  Data *data_;
};

#endif