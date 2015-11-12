#include "CDK/buffer.h"
#include <list>

struct Buffer::Data {
  bool dirty_;
  int size_;
  std::vector<float>positions_;
  std::vector<float>normals_;
  std::vector<float>uvs_;
  std::vector<unsigned int>indexes_;
  OpenGlInterFaz *interface_;
  GLuint vao_;
  GLuint vbo_[4]; //0 positions, 1 normals, 2 uvs,3 indexes;
};

Buffer::Buffer(){
  data_ = new Data;
};
void Buffer::init(int size){
  data_->size_ = size;
}
void Buffer::loadData(std::vector<float>positions, std::vector<float>normals, std::vector<float>uvs,
	std::vector<unsigned int> indexes){
	//Reserve vectors.
  data_->positions_.reserve(positions.size()*sizeof(float));
  data_->normals_.reserve(normals.size()*sizeof(float));
  data_->uvs_.reserve(uvs.size()*sizeof(float));
  data_->indexes_.reserve(indexes.size()*sizeof(unsigned int));

  data_->positions_ = positions;
  data_->normals_ = normals;
  data_->uvs_ = uvs;
  data_->indexes_ = indexes;
  data_->dirty_ = true;
}

bool Buffer::isDirty(){
  return  data_->dirty_;
}

GLuint* Buffer::getVAO(){ return &data_->vao_; }

GLuint* Buffer::getVBO(){ return  data_->vbo_; }

std::vector<std::vector<float>> Buffer::getAttributes(){
  std::vector<std::vector<float>> temp;
  temp.push_back(data_->positions_);
  temp.push_back(data_->normals_);
  temp.push_back(data_->uvs_);
	return temp;
}

std::vector<unsigned int > Buffer::getIndexes(){
  return  data_->indexes_;
}

void Buffer::setDirty(bool d){ data_->dirty_ = d; }


void Buffer::setVAO(GLuint v){
  data_->vao_ = v;
}