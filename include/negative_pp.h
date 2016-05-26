#include "CDK/PostProcess/post_process.h"
class NegativePP : public PostProcess{

public:
  void init(){
    material_->loadShader("shaders/negative_pp_v.glsl", "shaders/negative_pp_f.glsl", "");

  }
};