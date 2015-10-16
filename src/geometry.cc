#include "geometry.h"
Geometry::Geometry(){}


void Geometry::loadObjFile(const char*file){
  std::string err = tinyobj::LoadObj(shapes_, materials_, "C:\\Users\\Alejandro\\Desktop\\GENIE\\debug\\bin\\cube.obj");
  
  printf(err.c_str());
  if (shapes_.size() == 1)
  {
	  vertex_ = shapes_[0].mesh.positions;
	  normal_ = shapes_[0].mesh.normals;
	  uv_ = shapes_[0].mesh.texcoords;
  }

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

void Geometry::runCommand(int c){
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  glGenBuffers(3, vbo_);
  //Load positions
  glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
  glBufferData(GL_ARRAY_BUFFER, vertex_.size()*sizeof(float), &vertex_[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  //Load normals
  glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
  glBufferData(GL_ARRAY_BUFFER, normal_.size()*sizeof(float), &normal_[0], GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
  glEnableVertexAttribArray(1);
  //Load uvs
  glBindBuffer(GL_ARRAY_BUFFER, vbo_[2]);
  glBufferData(GL_ARRAY_BUFFER, uv_.size()*sizeof(float), &uv_[0], GL_STATIC_DRAW);
  glVertexAttribPointer(2, 2, uv_.size(), GL_FALSE, 0, 0);
  glEnableVertexAttribArray(2);
}