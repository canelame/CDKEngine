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

};
Geometry::Geometry(){
  data_ = new Data;
	data_->geo_buff_ = std::make_shared<Buffer>();
  
}


void Geometry::loadAttributes(std::shared_ptr<float*>positions, std::shared_ptr<float*>normals, std::shared_ptr<float*>uvs,
  std::shared_ptr<uint32*> indexes){

  data_->geo_buff_->loadData(positions, normals, uvs, indexes);
}


std::shared_ptr< Buffer> Geometry::getBuffer(){
  return    data_->geo_buff_;
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
void Geometry::createCube(){
  std::vector<float>vertex;
  std::vector<float>normal;
  std::vector<float>uv;
  std::vector<unsigned int>indexes;
  float size = 1.0f;
  const float cube_vertices[72]{
    //Cara 0
    -1 * size, -1 * size, 1 * size,
      1 * size, -1 * size, 1 * size,
      1 * size, 1 * size, 1 * size,
      -1 * size, 1 * size, 1 * size,

      //cara 1

      -1 * size, -1 * size, -1 * size,
      1 * size, -1 * size, -1 * size,
      1 * size, -1 * size, 1 * size,
      -1 * size, -1 * size, 1 * size,

      //cara 2

      -1 * size, -1 * size, -1 * size,
      -1 * size, -1 * size, 1 * size,
      -1 * size, 1 * size, 1 * size,
      -1 * size, 1 * size, -1 * size,

      //cara 3

      1 * size, -1 * size, 1 * size,
      1 * size, -1 * size, -1 * size,
      1 * size, 1 * size, -1 * size,
      1 * size, 1 * size, 1 * size,

      //cara 4

      -1 * size, 1 * size, 1 * size,
      1 * size, 1 * size, 1 * size,
      1 * size, 1 * size, -1 * size,
      -1 * size, 1 * size, -1 * size,

      //cara 5

      -1 * size, 1 * size, -1 * size,
      1 * size, 1 * size, -1 * size,
      1 * size, -1 * size, -1 * size,
      -1 * size, -1 * size, -1 * size,
  };
  const float uvs_position[48]{
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

      20, 21, 22, 20, 22, 23, };
  //END DATA
  const float normales[72]{
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
  int total_size = ((72 + 72 + 48)*sizeof(float)+36*sizeof(unsigned int));
  std::unique_ptr<char[]> t_buff = std::unique_ptr<char[]>(new char[total_size]);
  memcpy(t_buff.get(),&cube_vertices[0],72*sizeof(float));
  memcpy(&t_buff.get()[72 * sizeof(float)], &normales[0], 72 * sizeof(float));
  memcpy(&t_buff.get()[144 * sizeof(float)], &uvs_position[0], 48 * sizeof(float));
  memcpy(&t_buff.get()[192 * sizeof(float)], &indexes_cube[0], 36 * sizeof(unsigned int));
  data_->geo_buff_->setAttributeSize(72, 72, 48, 0, 0, 36);
  data_->geo_buff_->loadData(std::move(t_buff));
  
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