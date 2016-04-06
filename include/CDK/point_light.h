#include "light.h"
#include <vector>
class PointLight : public Light{
  void init();
  struct Data;
  Data *data_;
public:
  PointLight();
  ~PointLight();
  
};