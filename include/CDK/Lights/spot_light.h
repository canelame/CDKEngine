
#ifndef __H_SPOT_LIGHT__
#define __H_SPOT_LIGHT__

#include "CDK/Lights/light.h"
#include <memory>
#include "CDK/Misc/frame_buffer.h"
class SpotLight : public Light{
public:

  void setPosition(vec3 p);
  SpotLight();
  mat4 getLightProyection();
 FrameBuffer * getShadowMap();
 void setFar(float new_far);
 void setNear(float new_near);
 void setDirection(vec3 new_ditection);
 vec3 getDirection();
 float getConeAngle();
 void setConeAngle(float new_angle);
private:
  mat4 light_proyection_;
  std::shared_ptr<FrameBuffer> shadow_depth_buffer_;
  float far_;
  vec3 direction_;
  float near_;
  float cone_angle_;

};



#endif