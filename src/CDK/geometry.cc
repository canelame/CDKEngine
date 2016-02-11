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
glm::mat4 Geometry::getModel(){
  mat4 model;
  return model;
}

void Geometry::loadAttributes(float*positions, float*normals, float*uvs,
  unsigned int* indexes){

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
  data_->geo_buff_->loadData(quadVertices, 0, quad_uv, indices_quad);


}
