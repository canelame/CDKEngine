#include "CDK/geometry.h"
#include <list>
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Geometry::Geometry(){
	geo_buff_ = std::make_unique<Buffer>();
}
glm::mat4 Geometry::getModel(){
  mat4 model;
  // view = glm::rotate(view, 0.0, vec3(1.0, 0.0, 0.0));
  model = glm::scale(model, scale_);
  model = glm::translate(model, position_);
  return model;
}

void Geometry::loadObjFile(const char*file){
  std::string err = tinyobj::LoadObj(shapes_, materials_, file);
  
  printf(err.c_str());
  if (shapes_.size() == 1)
  {
	  geo_buff_.get()->loadData(shapes_[0].mesh.positions, shapes_[0].mesh.normals, shapes_[0].mesh.texcoords,
								shapes_[0].mesh.indices);

  }
  loaded_ = true;
}

void Geometry::loadAttributes(std::vector<float>vertex, std::vector<float>normal, std::vector<float>uv,
                              std::vector<unsigned int>index){
	geo_buff_.get()->loadData(vertex, normal, uv, index);


}
std::shared_ptr< Buffer> Geometry::getBuffer(){
  return geo_buff_;
}
void Geometry::setPosition(vec3 &p){
  position_ = p;
}
void Geometry::setRotation(vec3 &r){
  rotation_ = r;
}
void Geometry::setScale(vec3 &s){
  scale_ = s;
}
vec3 Geometry::position(){ return position_; }
vec3 Geometry::scale(){ return scale_; }
vec3 Geometry::rotation(){ return rotation_; }
void Geometry::createCube(int size) {

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
	std::vector<float> positions, normals, uvs;
	std::vector<unsigned int> indices;

	for (int i = 0; i < 72; i++) {
		positions.push_back(cube_vertices[i]);
		normals.push_back(normales[i]);
	}

	for (int i = 0; i < 48; i++) {
		uvs.push_back(uvs_position[i]);
	}

	std::vector<unsigned int> index;

	for (int i = 0; i < 36; i++) {
		indices.push_back(indexes_cube[i]);
	}
	geo_buff_->loadData(positions, normals, uvs, indices);
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
  std::vector<float> positions, normals, uvs;
  std::vector<unsigned int> indexes;
  for (int i = 0; i < 12; i++) {
    positions.push_back(quadVertices[i]);
    normals.push_back(normales[i]);

  }
  for (int i = 0; i < 8; i++) {

    uvs.push_back(quad_uv[i]);
  }
  for (int i = 0; i <6; i++) {
    indexes.push_back(indices_quad[i]);
  }
	geo_buff_->loadData(positions, normals, uvs,indexes);

}