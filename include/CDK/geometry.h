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
* Otherwise you can load geometry whit loadAttributes, passing the values in the function.
* REMEMBER TO USE A UNIQUE METHOD TO LOAD ATTRIBUTE VALUES.
*/


class Drawable;

class Geometry  {
public:

  
	Geometry();
	~Geometry(){
		printf("");
	};
  glm::mat4 getModel();
  /**
  * @brief This fucntion allows to load obj files. You can load several shapes from the file
  * using this funciton. You must call create(), after loading values
  * @param name File name.
  */
 
  void loadObjFile(const char* name);

  void loadCdkFormat(const char* name,bool assimp);

  void createTriangle();
  /**
  * @brief This funtion allow us to load the attribute values manually, you mast order the values and their
  * indexes . You must call create(), after load obj.
  * @param vertex Vertex position attributes-
  * @param normal Normal attributes.
  * @param uv Uv attributes.
  * @index Index values for each vertex.
  */
  void loadAttributes(std::vector<float>vertex, std::vector<float>normal, std::vector<float>uv,
    std::vector<unsigned int>index);

  std::shared_ptr<Buffer> getBuffer();


  /**
  * @brief This functions not must be here.
  */
  void setPosition(vec3 &p);
  void setScale(vec3 &s);
  void setRotation(vec3 &r);
  void createCube(int size);

  int numMes();
  void setMes(int v);
 std::shared_ptr<Buffer> total_meshes();


  vec3 position();
  vec3 rotation();
  vec3 scale();
  
private:
	int num_mesh_;
  vec3 position_;
  vec3 rotation_;
  vec3 scale_;
  bool loaded_ = false;
  mutable bool used_ = false;
  std::shared_ptr<Buffer> geo_buff_;



};


#endif