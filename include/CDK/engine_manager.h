#include "frame_buffer.h"

class EngineManager{
public:
  bool window_size_modified_ = false;
static  EngineManager& instance();
/**
*/
void init();
/**
*/
int width();
/**
*/
int height();
/**

*/
void setWidth(int w);
/**
*/
void setHeight(int h);
/**
*/
void setRenderTarget(FrameBuffer *fb);
/**
*/
void setWindowModified(bool value);
FrameBuffer* getRenderTarget();
private:
  EngineManager(){};
  int width_;
  int height_;
 FrameBuffer* current_render_target_=nullptr;
 static EngineManager * instance_;

};