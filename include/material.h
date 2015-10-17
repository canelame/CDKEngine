#ifndef __H_MATERIAL__
#define __H_MATERIAL__
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
/**
* material.h
* @author Alejandro Canela Mendez
* @brief This class represents a material for one mesh.
*/
class Material{

public:
  struct Light{
    glm::vec3 position;
    glm::vec4 color;

  };
  struct Material_attributes{
    GLuint texture;
    Light material_light; //We can have multiples lights , creating an array. 
  };
  Material();
  /**
  * @brief This function allows to load own shader.
  * @param vertex_file The name of vertex GLSL file.
  * @param fragment_file he name of fragment GLSL file.
  */
  void loadShader(const char*vertex_file, const char*fragment_file);
  void diffuse();
  void diffuseTexture();
private:

    GLuint program_;
    GLuint vertex_shader_;
    GLuint fragment_shader_;
    Material_attributes mat_attrib_;

    const char* vertex_data_;
    const char* fragment_data_;
  ~Material();


};


#endif