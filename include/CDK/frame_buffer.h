#ifndef __H_FRAME_BUFFER__
#define __H_FRAME_BUFFER__

#include "CDK/geometry.h"

class Texture;
class FrameBuffer{

public:
  FrameBuffer();
  ~FrameBuffer();
  FrameBuffer(const FrameBuffer&);
  void initFrameBuffer();
  bool isLoaded();
  void setLoaded(bool loaded);
  void setId(int id);
  int getId();
  Texture& getTexture();

private:
  struct Data;
  Data *data_;
};

#endif