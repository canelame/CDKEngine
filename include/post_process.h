#ifndef __H_POSTPROCESS__
#define __H_POSTPROCESS__
#include <memory>
#include "CDK\geometry.h"
#include "CDK\material.h"

class FrameBuffer;
class PostProcess{

protected:
  std::shared_ptr<Material> material_;
  std::shared_ptr<FrameBuffer> frame_buff_;
  std::shared_ptr<Geometry> render_quad_;

private:
  int getProgram();
 
public:
  virtual void init() = 0;
  PostProcess();

  std::shared_ptr<Buffer> getQuad();
  Material& getMaterial();
  FrameBuffer& getFrameBuffer();

};



#endif