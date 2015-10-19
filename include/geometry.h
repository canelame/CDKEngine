#ifndef __H_GEOMETRY__
#define __H_GEOMETRY__
#include "tiny_obj_loader.h"
#include "GL\glew.h"
#include "display_list.h"
#include "command.h"
/**
* Geometry class
* @author Alejandro Canela Méndez 2015
* @brief This class controls geometry generation. 
* You can load from obj, wwhit this form you can load several shapes.
* Otherwise you can load geometry whit loadAttributes, passing the values in the function.
* REMEMBER TO USE A UNIQUE METHOD TO LOAD ATTRIBUTE VALUES.
*/
class Geometry : public Command{
public:
	Geometry();
  
  /**
  * @brief This fucntion allows to load obj files. You can load several shapes from the file
  * using this funciton. You must call create(), after loading values
  * @param name File name.
  */
 
  void loadObjFile(const char* name);
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
  /**
  * @brief After loading the attributes we must call this function to create the geometry.
  */
  void create();
  Command* c;
  /**
  * @brief Pure virtual function, this execute OpenGL code in displayList.
  */
  int runCommand()const;
  /**
  * @brief Pure virtual function, not need implementation.
  */
  void add()const;
  
private:
  bool loaded_ = false;

	mutable GLuint vao_;
	mutable GLuint vbo_[3]; //0 positions, 1 normals, 2 uvs;

  std::vector<float> vertex_;
  std::vector<float> normal_;
  std::vector<float> uv_;
  std::vector<unsigned int > index_;

  std::vector<tinyobj::shape_t> shapes_; //Only used whit loadObjFile
  std::vector<tinyobj::material_t> materials_; //Only ude whit loadObjFile


};


#endif