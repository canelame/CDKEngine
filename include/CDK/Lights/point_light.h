#include "CDK/Lights/light.h"
#include <vector>
class PointLight : public Light{
  void init();
  struct Data;
  Data *data_;
  void computePerspectiveLight();
public:
  void setPosition(vec3 p);
  std::vector<mat4> getShadowMatrices();
  void setShadowCubeMapId(int id);
  void setTextureCubeMap(int id);
  int getShadowCubeMapBuffer();
  
  int getShadowCubeMapTexture();
  PointLight();
  ~PointLight();
  
};