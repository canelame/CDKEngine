#ifndef __H_MATERIAL__
#define __H_MATERIAL__
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "light.h"

/**
* material.h
* @author Alejandro Canela Mendez
* @brief This class represents a material for one mesh.
*/
class TaskManager;
class ReadFile;
class ReadTexture;
class Material {

public:


  enum TYPE_SHADER {
    FRAGMENT_SHADER = 0,
    VERTEX_FRAGMENT 
  };
  
 /// @brief Material Setting Struct 
  
  class MaterialSettings{
  public:

    vec3 diffuse_color_;
    vec3 specular_color_;
    vec3 ambient_color_;
    vec3 sh_;

    MaterialSettings( ){     
        ambient_color_ = vec3(1.0);
        specular_color_ = vec3(1.0);
        diffuse_color_ = vec3(1.0);
    }


    void setDiffuseColor(vec3 value){ diffuse_color_ = value; }
    void setSpecularColor(vec3 value){ specular_color_ = value; }
    void setAmbientColor(vec3 value){ ambient_color_ = value; }
    vec3 getDiffuseColor(){ return diffuse_color_; }
    vec3 getSpecularColor(){ return specular_color_; }
    vec3 getAmbientColor(){ return ambient_color_; }
  };
  Material();

  /**
  * @brief This function allows to load own shader.
  * @param vertex_file The name of vertex GLSL file.
  * @param fragment_file he name of fragment GLSL file.
  */
  void loadShader(const char*vertex_file, const char*fragment_file);
  /**
  @brief Get current program
  @return program
  */
  unsigned int getProgram();
  /**
  @brief Set current program
  @param value New program
  */
  void setProgram(int value);


  ~Material(){};
  /**
  @brief Get current Vertex code
  @return Vertex shader code
  */
  std::string getVertexData();

  /**
  @brief Get the fragment glsl code
  @returnm Code glsl of fragment shader
  */
  std::string getFragmentData();



  //Variables
  bool is_compiled_=false;
  std::string vertex_data_;
  std::string fragment_data_;
  int type_;
private:
  
  void useMaterial();
  void compileShader(GLuint shader)const;
  unsigned int program_;
  


  





};


#endif