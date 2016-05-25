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
  /**
  */
  int getProgram();
public:
  /**
  @brief Constructor
  */
  PostProcess();
  /**
  @brief Get quad on post process is rendered
  @return The current quad vao of post process
  */
  std::shared_ptr<Buffer> getQuad();
  /**
  @brief Get Post Process material shaders
  @return The current material 
  */
  Material& getMaterial();
  /**
  @brief Get post process current framebuffer
  @return Pointer to frambebuffer
  */
  FrameBuffer& getFrameBuffer();
  /**
  @brief initialize post process material, the user must reimplement this function on her own class
  Example:
  void init(){
    loadSha
  }
  */
  virtual void init() = 0;
};



#endif