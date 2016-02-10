#include "CDK/buffer.h"
#include <list>
#include "GL\glew.h"
struct Buffer::Data {
  bool dirty_;

  std::shared_ptr<float *>positions;
  std::shared_ptr<float *>normals;
  std::shared_ptr<float * > uvs;
  std::shared_ptr<unsigned int*> indices;
  std::unique_ptr<char[]> data;

  int num_position_vertex_;
  int num_normal_vertex_;
  int num_uv_vertex_;
  int num_tan_vertex_;
  int num_bitan_vertex_;
  int num_indices_;

  GLuint vao_;
  GLuint vbo_[4]; //0 positions, 1 normals, 2 uvs,3 indexes;
};


Buffer::Buffer(float*positions, float*normals, float*uvs,
  unsigned int* indexes){
  data_ = new Data;
  data_->positions = std::make_shared<float*>(positions);
  data_->normals = std::make_shared<float*>(normals);
  data_->uvs = std::make_shared<float*>(uvs);
  data_->indices = std::make_shared<unsigned int*>(indexes);
}
Buffer::Buffer(){
  data_ = new Data;
};
void Buffer::setAttributeSize(int p, int n, int uv, int t, int bt, int i){
  data_->num_position_vertex_ = p;
  data_->num_normal_vertex_ = n;
  data_->num_uv_vertex_ = uv;
  data_->num_tan_vertex_ = t;
  data_->num_bitan_vertex_ = bt;
  data_->num_indices_ = i;
}
void Buffer::init(int size){}

void Buffer::loadData(float*positions, float*normals, float*uvs,
  unsigned int* indexes){
  //Reserve vectors.
  data_->positions = std::make_shared<float*>(positions);
  data_->normals = std::make_shared<float*>(normals);
  data_->uvs = std::make_shared<float*>(uvs);
  data_->indices = std::make_shared<unsigned int*>(indexes);
  data_->dirty_ = true;
}

bool Buffer::isDirty(){ return  data_->dirty_; }
int Buffer::vertexSize(){ return  data_->num_position_vertex_; }
int Buffer::normalSize(){ return data_->num_normal_vertex_; }
int Buffer::uvSize(){ return data_->num_uv_vertex_; }
int Buffer::tangentSize(){ return data_->num_tan_vertex_; }
int Buffer::bitangentSize(){ return data_->num_bitan_vertex_; }
int Buffer::indiceSize(){ return data_->num_indices_; }
unsigned int* Buffer::getVAO(){ return &data_->vao_; }
unsigned int* Buffer::getVBO(){ return  data_->vbo_; }



std::vector<float*> Buffer::getAttributesT(){
  std::vector<float*> temp;
  temp.push_back(*data_->positions.get());
  temp.push_back(*data_->normals.get());
  temp.push_back(*data_->uvs.get());
  return temp;
}

unsigned int * Buffer::getIndexesT(){
  return  *data_->indices.get();
}
void Buffer::setDirty(bool d){ data_->dirty_ = d; }


void Buffer::setVAO(GLuint v){
  data_->vao_ = v;
}