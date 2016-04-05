#ifndef __H_SCENE__
#define __H_SCENE__
#include <memory>
#include "node.h"
#include "camera.h"
#include <vector>
class Scene {
public:
  std::shared_ptr<Node> root_;
  std::shared_ptr<Camera> camera_;
  std::shared_ptr<Light> directional_light_;
  std::vector < std::shared_ptr<Light> >lights_;

  Scene();
  /**
  */
  void addChild(std::shared_ptr<Node> child);
  /**
  */
  void addLight(std::shared_ptr<Light>light );
  /**
  */
  void render();

};

#endif