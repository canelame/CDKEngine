#include "geometry.h"
Geometry::Geometry(){
	geo_buff_ = std::make_unique<Buffer>();
}


void Geometry::loadObjFile(const char*file){
  std::string err = tinyobj::LoadObj(shapes_, materials_, "mycube.obj");
  
  printf(err.c_str());
  if (shapes_.size() == 1)
  {
	  geo_buff_.get()->loadData(shapes_[0].mesh.positions, shapes_[1].mesh.normals, shapes_[2].mesh.texcoords,
								shapes_[3].mesh.indices);

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

