#include "geometry.h"
Geometry::Geometry(){
	geo_buff_ = std::make_unique<Buffer>();
}


void Geometry::loadObjFile(const char*file){
  std::string err = tinyobj::LoadObj(shapes_, materials_, file);
  
  printf(err.c_str());
  if (shapes_.size() == 1)
  {
	  geo_buff_.get()->loadData(shapes_[0].mesh.positions, shapes_[0].mesh.normals, shapes_[0].mesh.texcoords,
								shapes_[0].mesh.indices);

  }
  loaded_ = true;
}

void Geometry::loadAttributes(std::vector<float>vertex, std::vector<float>normal, std::vector<float>uv,
                              std::vector<unsigned int>index){
	geo_buff_.get()->loadData(vertex, normal, uv, index);


}

void Geometry::create(){

 


}

void Geometry::runCommand()const{

	geo_buff_.get()->useGeometry();
  
 
}

void Geometry::setPosition(vec3 &p){
  position_ = p;
}
void Geometry::setRotation(vec3 &r){
  rotation_ = r;
}
void Geometry::setScale(vec3 &s){
  scale_ = s;
}
vec3 Geometry::position(){ return position_; }
vec3 Geometry::scale(){ return scale_; }
vec3 Geometry::rotation(){ return rotation_; }