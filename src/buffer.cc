#include "buffer.h"
#include <list>
void Buffer::init(int size){
	size_ = size;
}
void Buffer::loadData(std::vector<float>positions, std::vector<float>normals, std::vector<float>uvs,
	std::vector<unsigned int> indexes){
	//Reserve vectors.
	positions_.reserve(positions.size()*sizeof(float));
	normals_.reserve(normals.size()*sizeof(float));
	uvs_.reserve(uvs.size()*sizeof(float));
	indexes_.reserve(indexes.size()*sizeof(unsigned int));

	positions_ = positions;
	normals_ = normals;
	uvs_ = uvs;
	indexes_ = indexes;
	dirty_ = true;
}

bool Buffer::isDirty(){
	return dirty_;
}

GLuint* Buffer::getVAO(){ return &vao_; }

GLuint* Buffer::getVBO(){ return vbo_; }

std::vector<std::vector<float>> Buffer::getAttributes(){
  std::vector<std::vector<float>> temp;
	temp.push_back(positions_);
	temp.push_back( normals_);
	temp.push_back( uvs_);
	return temp;
}

std::vector<unsigned int > Buffer::getIndexes(){
	return indexes_;
}

void Buffer::setDirty(bool d){  dirty_=d; }

OpenGlInterFaz* Buffer::useGeometry(){
  if (isDirty()){
    std::vector<std::vector<float>> a = { positions_, normals_, uvs_ };
    interface_->loadBuffer(a,indexes_);
    setDirty(false);
  }
	interface_->useGeometry();
	return interface_;
}

OpenGlInterFaz* Buffer::useDrawGeometry(){
	interface_->useDrawGeometry();
	return interface_;
}