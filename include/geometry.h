#ifndef __H_GEOMTRY__
#define __H_GEOMTRY__



/**
* Geomtry Class
* @author Alejandro Canela 2015.
* @brief This class allow us create geomtrys to render in our engine.
*/
class Geometry{

  struct geo_attributes{
  //  eastl::vector<float> vertex_;
    //eastl::vector<float>normals_;
   // eastl::vector<float> uvs_;
   // eastl::vector<unsigned int> indexes_;
  };

public:
  Geometry(){};
  void loadObjFile(const char * file);
private:
  //One geomtry can be composed  by several geometries
 // eastl::vector<geo_attributes> geomtrys;

  //Necessary to use tinyObj
// std::vector<tinyobj::shape_t> shapes_;
 // std::vector<tinyobj::material_t> materials_;
};


#endif