#ifndef __H_COMPOSER__
#define __H_COMPOSER__
#include "CDK/PostProcess/post_process.h"
#include <vector>
#include <memory>
#include "CDK/Material/material_composer.h"
class Composer{

public:

  Composer();
  /**
  @brief Get post-process from composer list by index
  @param index Postprocess index
  */
   PostProcess * getEffect(int index);
   /**
   @brief Get total post process of te composr
   @return 
   */
   int size();
   /**
   @brief Add new pos process effect to composer
   @param new_effect New post process effect
   */
  void addEffect(std::shared_ptr<PostProcess> new_effect);
  /**
  @brief Get post process quad
  @return Buffer containing quad of the post process.
  */
  std::shared_ptr<Buffer> getQuad();
  /**
  @brief Get post process quad
  @return Buffer containing quad of the post process.
  */
  void render();
  ~Composer();
  friend class UpdateDisplay;
  friend class ComposePostProcess;
private :
  std::vector<std::shared_ptr<PostProcess>> effects_list_;
  std::shared_ptr<FrameBuffer> final_target_;
  std::shared_ptr<FrameBuffer> aux_target_;
  std::shared_ptr<ComposerMaterial> composer_material_;
  std::shared_ptr<Geometry> render_quad_;
  void init();
};

#endif