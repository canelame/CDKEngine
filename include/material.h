#ifndef __H_MATERIAL__
#define __H_MATERIAL__
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "command.h"
#include <sstream>
#include <fstream>
#include <iostream>
/**
* material.h
* @author Alejandro Canela Mendez
* @brief This class represents a material for one mesh.
*/
class Material :public Command{

public:
  enum TYPE{
    ONNLY_DIFFUSE_ = 0,
    DIFFUSE_TEXTURE
  };
  struct Light{
    glm::vec3 position;
    glm::vec4 color;

  };
  struct Material_attributes{
    GLuint texture;
    Light material_light; //We can have multiples lights , creating an array. 
  };
  Material(TYPE t);
  
  void runCommand()const;
  /**
  * @brief This function allows to load own shader.
  * @param vertex_file The name of vertex GLSL file.
  * @param fragment_file he name of fragment GLSL file.
  */
  void loadShader(const char*vertex_file, const char*fragment_file);

  
  GLuint texture(){ return mat_attrib_.texture; }
  ~Material(){};
private:
  enum TYPE_SHADER {
    FRAGMENT_SHADER = 0,
    VERTEX_FRAGMENT
  };
  mutable  GLint program_;
  mutable  GLuint vertex_shader_;
  mutable  GLuint fragment_shader_;
   Material_attributes mat_attrib_;

  const char* vertex_data_;
  const char* fragment_data_;

  void compileShader(GLuint shader)const;
  void diffuse();
  void diffuseTexture();


};


#endif