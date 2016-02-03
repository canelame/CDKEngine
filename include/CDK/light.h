#ifndef __H_LIGHT__
#define __H_LIGHT__
#include "glm\glm.hpp"
#include "CDK\types.h"
#include "CDK\node.h"

class Light{

public:
  enum LightType{
    NONE = 0,
    T_POINT_LIGHT,
    T_DIRECTION_LIGHT,
    T_SPOT_LIGHT


  };
  Light();
  Light(vec3 position, vec3 rotation, vec3 type);
  ~Light();
  Light(const Light&);
  void setPosition(vec3 p);
  void setRotation(vec3 r);
  void setDifusseColor(vec3 dc);
  void setSpecularColor(vec3 sc);
  void setAmbientColor(vec3 ac);
  void setTypeLight(LightType lt);

  vec3 getPosition();
  vec3 getDirection();
  vec3 getAmbientColor();
  vec3 getDiffuseColor();
  vec3 getSpecularColor();
  float getShinenes();
  LightType getType();
private:
  vec3 position_;
  vec3 direction_;
  vec3 difusse_color_;
  vec3 specular_color_;
  vec3 ambient_color_;
  float sh_;
  LightType l_type;
};

#endif




