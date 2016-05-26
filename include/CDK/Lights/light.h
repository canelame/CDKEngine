#ifndef __H_LIGHT__
#define __H_LIGHT__
#include "glm\glm.hpp"
#include "CDK\Core/types.h"


class Light{

public:
  enum LightType{
    NONE = 0,
    T_POINT_LIGHT,
    T_DIRECTION_LIGHT,
    T_SPOT_LIGHT
  };
  ///Constructor
  Light();
  ///Constructor whit position roation and type
  Light(vec3 position, vec3 rotation, vec3 type);
  ///Destructor
  ~Light();
  ///Copy constructor
  Light(const Light&);
  /**
  @brief Set ligh position
  @param p New position
  */
  void setPosition(vec3 p);
  /** 
  @brief Not used,
  @param
  */
  void setRotation(vec3 r);
  /**
  @brief Set new diffuse color to light
  @param dc New diffuse color
  */
  void setDifusseColor(vec3 dc);
  /**
  @brief Set new specular color to light
  @param sc New specular color
  */
  void setSpecularColor(vec3 sc);
  /**
  @brief Set new ambient color to light
  @param ac New ambient color
  */
  void setAmbientColor(vec3 ac);
  /**
  @brief Set type of light
  @param lt Type of light
  */
  void setTypeLight(LightType lt);
  /**
  @brief Get current position of the light
  @return Current position
  */

  vec3 getPosition();
  /**
  @brief Get direction of the light //Not used
  @return Light direction
  */
  vec3 getDirection();
  /**
  @brief Get ambient color of the light
  @return Current ambient color
  */
  vec3 getAmbientColor();
  /**
  @brief Get diffuse color of the light
  @return Current diffuse color
  */
  vec3 getDiffuseColor();
  /**
  @brief Get specular color of the light
  @return Current specualar color
  */
  vec3 getSpecularColor();
  /**
  @brief Get specular shinnenes
  @return current Shinnenes
  */
  float getShinenes();
  /**
  @brief Get current light type
  @return Current light type
  */
  LightType getType();
  /**
  @brief Set true or false if the light has been loaded into GPU
  @param value New value for loaded state
  */
  void setLoaded(bool value);
  /**
  @brief Get true or false if the light has been loaded into GPU
  @return value Get value for loaded state
  */
  bool getLoaded();

  bool isDirty();
  void setDirty(bool value);
  friend class OpenGlInterFaz;
  protected:
    int type = 0;
private:

  struct Data;
  Data *data_;
};

#endif




