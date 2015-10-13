#include "geometry.h"

void Geometry::loadObjFile(const char*file){
  std::string err = tinyobj::LoadObj(shapes_, materials_, "C:\\Users\\Alejandro\\Desktop\\GENIE\\debug\\bin\\cube.obj");
  
  printf(err.c_str());
}

void Geometry::loadAttributes(std::vector<float>vertex, std::vector<float>normal, std::vector<float>uv,
                              std::vector<unsigned int>index){
  
  vertex_ = vertex;
  normal_ = normal;
  uv_ = uv;
  index_ = index;

}

void Geometry::create(){

}