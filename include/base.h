#ifndef __H_BASE__
#define __H_BASE__
#include "glm\glm.hpp"
#include "raii_pointer.h"
/**
* base.h
* @author Alejandro Canela Mendez
* @brief This is a base class to set position rotation and scale
*/
#
class Base{

public:
  Base(){};
  void setPosition(float x, float y, float z);
  void setScale(float x, float y, float z);
  void setRotation(float x, float y, float z);

  glm::vec3 getPosition();
  glm::vec3 getScale();
  glm::vec3 getRotation();
private:
  glm::vec3 position_;
  glm::vec3 scale_;
  glm::vec3 rotation_;

};


#endif