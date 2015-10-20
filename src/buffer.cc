#include "buffer.h"

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

std::vector<float>*Buffer::getAttributes(){
	std::vector<float >t_a[4];
	t_a[0] =positions_;
	t_a[1] = normals_;
	t_a[2] = uvs_;
	return t_a;
}

std::vector<unsigned int > Buffer::getIndexes(){
	return indexes_;
}

void Buffer::setDirty(bool d){ d = dirty_; }

void Buffer::useGeometry(Buffer *c){
	interface_->useGeometry(c);
}