#ifndef __H_GEOMETRY__
#define __H_GEOMETRY__

#include "external/tiny_obj_loader.h"
#include "GL\glew.h"
#include "CDK/command.h"
#include "CDK/buffer.h"
#include "CDK/types.h"
#include <memory>
/**
* Geometry class
* @author Alejandro Canela Méndez 2015
* @brief This class controls geometry generation. 
* You can load from obj, wwhit this form you can load several shapes.
*
* REMEMBER TO USE A UNIQUE METHOD TO LOAD ATTRIBUTE VALUES.
*/


class Drawable;

class Geometry  {
public:

  enum DrawMode{
    kDrawModeTriangles = 0,
    kDrawModeStripTriangles,
    kDrawModePoints,
  };
  
	Geometry();
	~Geometry(){};
  /**
  @brief Get model matrix of the model
  @param Get 
  */
  mat4 getModel();


  void createTriangle();
  /**
  * @brief This funtion allow us to load the attribute values manually, you mast order the values and their
  * indexes . You must call create(), after load obj.
  * @param vertex Vertex position attributes-
  * @param normal Normal attributes.
  * @param uv Uv attributes.
  * @index Index values for each vertex.
  */
  void loadData(std::unique_ptr<char[]>data);
  void loadData(std::vector<float> positions, std::vector<float> normals
                ,std::vector<float> uvs, std::vector<unsigned int> indices);
  /**
  @brief Get geometry buffer
  @return Buffer
  */
  std::shared_ptr<Buffer> getBuffer();


  /**
  * @brief This functions not must be here.
  */

  void createCube();
  void createQuad();

private:
  struct Data;
  Data *data_;



};


#endif