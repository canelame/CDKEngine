#include "light.h"
#include <memory>
#include "frame_buffer.h"
class DirectionalLight : public Light{

public:
  std::shared_ptr<FrameBuffer> shadow_depth_buffer_;
  mat4 light_proyection_;
  void setPosition(vec3 p);
  DirectionalLight();

private:


};