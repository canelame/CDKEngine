#include "CDK/geometry.h"
#include <list>
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//Assimp include

struct Geometry::Data{
  bool loaded_ = false;
  mutable bool used_ = false;
  std::shared_ptr<Buffer> geo_buff_;
  DrawMode drawing_mode_;

};
Geometry::Geometry(){
  data_ = new Data;
	data_->geo_buff_ = std::make_shared<Buffer>();
  
}


void Geometry::loadData(std::unique_ptr<char[]>data){

  data_->geo_buff_->loadData(std::move(data));
}


std::shared_ptr< Buffer> Geometry::getBuffer(){
  if (this != NULL){
    return    data_->geo_buff_;
  }
}


void Geometry::createTriangle(){
 // float x = 0, y = 0;
  float x = 0.5;// width / 2;
  float y = 0.5;// height / 2;

  float quadVertices[12] = {

    -1.0f*x, 1.0f*y, 0.0f,
    -1.0f*x, -1.0f*y, 0.0f,
    1.0f*x, -1.0f*y, 0.0f,
    1.0f*x, 1.0f*y, 0.0f,
  };
  float quad_uv[8]{

    0.0f, 1.0f,
      0.0f, 0.0f,
      1.0f, 0.0f,
      1.0f, 1.0f,

  };
  unsigned int indices_quad[6] = {  // Note that we start from 0!
    0, 1, 2,   // First Triangle
    2, 3, 0    // Second Triangle
  };

  const float normales[]{
    0, 0, 1,
      0, 0, 1,
      0, 0, 1,
      0, 0, 1,
  };
  data_->geo_buff_->setAttributeSize(12, 12, 8, 0, 0, 6);
//  data_->geo_buff_->loadData(quadVertices, 0, quad_uv, indices_quad);


}
void Geometry::setDrawGeometryMode(int mode){
  data_->geo_buff_->setDrawMode(mode);
}

void Geometry::createCube(){
  std::vector<float>vertex;
  std::vector<float>normal;
  std::vector<float>uv;
  std::vector<unsigned int>indexes;
  float size = 1.0f;
  float vertices[72] =
  { -1 * size, -1 * size, 1 * size, //0   //0
  1 * size, -1 * size, 1 * size, //1
  1 * size, 1 * size, 1 * size, //2
  -1 * size, 1 * size, 1 * size, //3

  -1 * size, -1 * size, -1 * size, //4 //1
  1 * size, -1 * size, -1 * size, //5
  1 * size, -1 * size, 1 * size, //1
  -1 * size, -1 * size, 1 * size, //0  

  -1 * size, -1 * size, -1 * size, //4   //2
  -1 * size, -1 * size, 1 * size, //0
  -1 * size, 1 * size, 1 * size, //3
  -1 * size, 1 * size, -1 * size, //7

  1 * size, -1 * size, 1 * size, //1   //3
  1 * size, -1 * size, -1 * size, //5
  1 * size, 1 * size, -1 * size, //6
  1 * size, 1 * size, 1 * size, //2

  -1 * size, 1 * size, 1 * size, //3   //4
  1 * size, 1 * size, 1 * size, //2
  1 * size, 1 * size, -1 * size, //6
  -1 * size, 1 * size, -1 * size, //7

  -1 * size, 1 * size, -1 * size, //7   //5
  1 * size, 1 * size, -1 * size, //6
  1 * size, -1 * size, -1 * size, //5
  -1 * size, -1 * size, -1 * size, //4 
  };

  float normals[72] =
  {
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
    0, 0, -1
  };

 float uvs[48] = {
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0
  };
  unsigned int indexes_cube[36]{
    0, 1, 2, 0, 2, 3,
      4, 5, 6, 4, 6, 7,
      8, 9, 10, 8, 10, 11,
      12, 13, 14, 12, 14, 15,
      16, 17, 18, 16, 18, 19,
      20, 21, 22, 20, 22, 23};

  std::vector<float> positions, normals_v, uvs_v;
  std::vector<unsigned int> indices;
  for (int i = 0; i < 72; i++){
    positions.push_back(vertices[i]);
    normals_v.push_back(normals[i]);
  }
  for (int i = 0; i < 48; i++){
    uvs_v.push_back(uvs[i]);
  }
  for (int i = 0; i < 36; i++){
    indices.push_back(indexes_cube[i]);
  }
  loadData(positions, normals_v, uvs_v, indices);

}

void Geometry::createQuad(){
    float quadVertices[12] = {

      -1.0f, 1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,
      1.0f, -1.0f, 0.0f,
      1.0f, 1.0f, 0.0f,


    };
    float quad_uv[8]{

      0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

    };
    unsigned int indices_quad[6] = {  // Note that we start from 0!
      0, 1, 2,   // First Triangle
      2, 3, 0    // Second Triangle
    };

    const float normales[12]{
      0, 0, 1,
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,
    };

    int total_size = ((12 + 12 + 8)*sizeof(float) + 6 * sizeof(unsigned int));
    std::unique_ptr<char[]> t_buff = std::unique_ptr<char[]>(new char[total_size]);
    memcpy(t_buff.get(), &quadVertices[0], 12 * sizeof(float));
    memcpy(&t_buff.get()[12 * sizeof(float)], &normales[0], 12 * sizeof(float));
    memcpy(&t_buff.get()[24 * sizeof(float)], &quad_uv[0], 8 * sizeof(float));
    memcpy(&t_buff.get()[32 * sizeof(float)], &indices_quad[0], 6 * sizeof(unsigned int));
    data_->geo_buff_->setAttributeSize(12, 12, 8, 0, 0, 6);
    data_->geo_buff_->loadData(std::move(t_buff));

}

void Geometry::loadData(std::vector<float> positions, std::vector<float> normals
  , std::vector<float> uvs, std::vector<unsigned int> indices){
  int total_size = (positions.size() + normals.size() + uvs.size()) * sizeof(float);
  total_size += (indices.size() * sizeof(unsigned int));
  std::unique_ptr<char[]> t_buff = std::unique_ptr<char[]>(new char[total_size]);

  memcpy(t_buff.get(), &positions[0], positions.size() * sizeof(float));
  memcpy(&t_buff.get()[positions.size() * sizeof(float)], &normals[0], normals.size() * sizeof(float));
  memcpy(&t_buff.get()[ (positions.size() + normals.size()) * sizeof(float)], &uvs[0], uvs.size() * sizeof(float));
  memcpy(&t_buff.get()[ (positions.size() + normals.size()+uvs.size() ) * sizeof(float)], &indices[0], indices.size() * sizeof(unsigned int));
  data_->geo_buff_->setAttributeSize(positions.size(), normals.size(), uvs.size(), 0, 0, indices.size());
  data_->geo_buff_->loadData(std::move(t_buff));
  

}



