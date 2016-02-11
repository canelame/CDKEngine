#ifndef __H_FRAME_BUFFER__
#define __H_FRAME_BUFFER__

class FrameBuffer{


  FrameBuffer();
  ~FrameBuffer();
  FrameBuffer(const FrameBuffer&);
private:
  struct Data;
  Data *data_;
};

#endif