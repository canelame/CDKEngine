#include "CDK/geometry.h"
#include <list>
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//Assimp include

Geometry::Geometry(){
	geo_buff_ = std::make_unique<Buffer>();

}
glm::mat4 Geometry::getModel(){
  mat4 model;
  return model;
}



void Geometry::loadObjFile(const char*file){
  /*Load whit tinyobj

  std::string err = tinyobj::LoadObj(shapes_, materials_, file);
  
  printf(err.c_str());
  if (shapes_.size() == 1)
  {
	  geo_buff_.get()->loadData(shapes_[0].mesh.positions, shapes_[0].mesh.normals, shapes_[0].mesh.texcoords,
								shapes_[0].mesh.indices);

  }
  loaded_ = true;*/

  //Load whit asssimp
 
}
int Geometry::numMes(){
	return 0;
}

void Geometry::loadCdkFormat(const char* file_in,bool assimp){
  
}

void Geometry::loadAttributes(float*positions, float*normals, float*uvs,
  unsigned int* indexes){

  geo_buff_->loadData(positions, normals, uvs, indexes);
}


std::shared_ptr< Buffer> Geometry::getBuffer(){
	return    geo_buff_;
}

void Geometry::createCube(int size) {

	 float cube_vertices[72]{
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
	 float uvs_position[48]{
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
	 float normales[72]{
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
   geo_buff_->setAttributeSize(72, 72, 48, 0, 0, 36);
  geo_buff_->loadData(cube_vertices, normales, uvs_position, indexes_cube);

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
  geo_buff_->setAttributeSize(12, 12, 8, 0, 0, 6);
  geo_buff_->loadData(quadVertices, 0, quad_uv, indices_quad);


}
