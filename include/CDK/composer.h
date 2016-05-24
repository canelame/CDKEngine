#ifndef __H_COMPOSER__
#define __H_COMPOSER__
#include "../post_process.h"
#include <vector>
#include <memory>
#include "CDK/material_composer.h"
class Composer{

  std::vector<std::shared_ptr<PostProcess>> effects_list_;
  std::shared_ptr<FrameBuffer> final_target_;
  std::shared_ptr<FrameBuffer> aux_target_;
  std::shared_ptr<ComposerMaterial> composer_material_;
  std::shared_ptr<Geometry> render_quad_;

  void init();
public:

  Composer();
  /**
  */
   PostProcess * getEffect(int index);
   /**
   */
   int size();
   /**
   */
  void addEffect(std::shared_ptr<PostProcess> new_effect);
  /**
  */
  std::shared_ptr<Buffer> getQuad();
  /**
  */
  void render();
  ~Composer();
  friend class UpdateDisplay;
  friend class ComposePostProcess;

};

#endif