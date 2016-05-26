#include "CDK/PostProcess/post_process.h"
class CrazyPP : public PostProcess{

public:
  void init(){
    material_->loadShader("shaders/molon_v.glsl", "shaders/molon_f.glsl", "");

  }
};