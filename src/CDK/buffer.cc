#include "CDK/buffer.h"
#include <list>
#include "GL\glew.h"
#include "CDK/types.h"
struct Buffer::Data {
  bool dirty_;

  std::unique_ptr<char[]> data;
  int num_position_vertex_;
  int num_normal_vertex_;
  int num_uv_vertex_;
  int num_tan_vertex_;
  int num_bitan_vertex_;
  int num_indices_;

  GLuint vao_;
};
void Buffer::loadData(std::unique_ptr<char[]>buffer_data){
  data_->data = std::move(buffer_data);
}

Buffer::Buffer(float*positions, float*normals, float*uvs,
  unsigned int* indexes){
  data_ = new Data;
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

void Buffer::loadData(std::shared_ptr<float*>positions, std::shared_ptr<float*>normals, std::shared_ptr<float*>uvs,
  std::shared_ptr<uint32*> indexes){
  //Reserve vectors.

  data_->dirty_ = true;

}

bool Buffer::isDirty(){ return  data_->dirty_; }
int Buffer::vertexSize(){ return  data_->num_position_vertex_; }
int Buffer::normalSize(){ return data_->num_normal_vertex_; }
int Buffer::uvSize(){ return data_->num_uv_vertex_; }
int Buffer::tangentSize(){ return data_->num_tan_vertex_; }
int Buffer::bitangentSize(){ return data_->num_bitan_vertex_; }
int Buffer::indiceSize(){ return data_->num_indices_; }
int Buffer::getVAO(){ return data_->vao_; }




std::vector<float*> Buffer::getAttributesT(){
  std::vector<float*> temp;

  return temp;
}
char* Buffer::getData(){
  return data_->data.get();
}

void Buffer::setDirty(bool d){ data_->dirty_ = d; }


void Buffer::setVAO(GLuint v){
  data_->vao_ = v;
}