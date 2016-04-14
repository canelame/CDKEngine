#include "light.h"
#include <memory>
#include "frame_buffer.h"
class DirectionalLight : public Light{

public:


  void setPosition(vec3 p);
  DirectionalLight();
  mat4 getLightProyection();
  FrameBuffer * getShadowMap();
private:
  mat4 light_proyection_;
  std::shared_ptr<FrameBuffer> shadow_depth_buffer_;
};