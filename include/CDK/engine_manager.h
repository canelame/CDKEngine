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
void addUniform(char *name, int location);
 int getUniform(char *name);
FrameBuffer* getRenderTarget();
private:
 EngineManager(){};
 int width_;
 int height_;
 std::map<char*, unsigned int> loaded_uniforms_;

 FrameBuffer* current_render_target_=nullptr;
 static EngineManager * instance_;

};