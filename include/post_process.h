#ifndef __H_POSTPROCESS__
#define __H_POSTPROCESS__
#include <memory>
#include "CDK\geometry.h"
#include "CDK\material.h"

class FrameBuffer;
class PostProcess{

  std::shared_ptr<Geometry> render_quad_;
  std::shared_ptr<Material> material_;
  std::shared_ptr<FrameBuffer> frame_buff_;
  int getProgram();
public:

  PostProcess();

  void init();
  std::shared_ptr<Buffer> getQuad();
  Material& getMaterial();

  void begin();
  void end();
  void render();

};



#endif