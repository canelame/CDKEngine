#include "CDK/point_light.h"
struct PointLight::Data{
  GLuint shadowCube;
  std::vector<mat4> shadow_matrices;
  
};
PointLight::PointLight(){
  data_ = new Data;
}
PointLight::~PointLight(){}


void PointLight::init(){

}