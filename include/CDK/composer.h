#ifndef __H_COMPOSER__
#define __H_COMPOSER__
#include "../post_process.h"
#include <vector>
#include <memory>
#include "display_list.h"
class Composer{

  std::vector<std::shared_ptr<PostProcess>> effects_list_;
  std::unique_ptr<PostProcess> final_target_;
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
  void compose(DisplayList * dl_to_update);
  /**
  */
  ~Composer();
  

};

#endif