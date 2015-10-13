#ifndef __H_GEOMETRY__
#define __H_GEOMETRY__
#include "tiny_obj_loader.h"
/**
* Geometry class
* @author Alejandro Canela
* @brief This class controls geometry generation. 
* You can load from obj, wwhit this form you can load several shapes.
* Otherwise you can load geometry whit loadAttributes, passing the values in the function.
*/
class Geometry{
public:
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
  
private:
  std::vector<float> vertex_;
  std::vector<float> normal_;
  std::vector<float> uv_;
  std::vector<unsigned int > index_;

  std::vector<tinyobj::shape_t> shapes_; //Only used whit loadObjFile
  std::vector<tinyobj::material_t> materials_; //Only ude whit loadObjFile


};


#endif