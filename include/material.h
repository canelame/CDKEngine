#ifndef __H_MATERIAL__
#define __H_MATERIAL__
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "command.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "opengl_interfaz.h"
#include "texture.h"
#include <memory>
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
  void loadTexture(const char* file_name);
  void runCommand(OpenGlInterFaz &i)const;

  /**
  * @brief This function allows to load own shader.
  * @param vertex_file The name of vertex GLSL file.
  * @param fragment_file he name of fragment GLSL file.
  */
  void loadShader(const char*vertex_file, const char*fragment_file);
  GLuint getProgram();
  
  GLuint texture(){ return mat_attrib_.texture; }
  ~Material(){};
  std::string getVertexData();
  std::string getFragmentData();
private:
  enum TYPE_SHADER {
    FRAGMENT_SHADER = 0,
    VERTEX_FRAGMENT
  };
  unsigned char* image_;
  bool is_texture_;
  mutable  GLint program_;
  mutable  GLuint vertex_shader_;
  mutable  GLuint fragment_shader_;
  Material_attributes mat_attrib_;
  mutable bool is_compiled_;
  std::string vertex_data_;
  std::string fragment_data_;
  std::string texture_name_;
  void useMaterial();

  void compileShader(GLuint shader)const;
  OpenGlInterFaz *interfaz_;
  std::unique_ptr<Texture> texture_;
  friend OpenGlInterFaz;
};


#endif