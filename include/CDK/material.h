#ifndef __H_MATERIAL__
#define __H_MATERIAL__
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "texture.h"
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
  enum TYPE{
    ONNLY_DIFFUSE_ = 0,
    DIFFUSE_TEXTURE
  };

  enum TYPE_SHADER {
    FRAGMENT_SHADER = 0,
    VERTEX_FRAGMENT
  };
  
 /// @brief Material Setting Struct 
  
  struct MaterialSettings;

  Material(TYPE t);

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
  GLuint getProgram();
  /**
  @brief Set current program
  @param value New program
  */
  void setProgram(int value);
  /**
  @brief add a texture to material
  @param txt new texture
  @param tk The current taskManager
  */
  void addTexture(std::shared_ptr<Texture> txt, std::shared_ptr<TaskManager> tk);

  GLuint texture(){}
  ~Material(){};
  /**
  @brief Get current Vertex code
  @return Vertex shader code
  */
  std::string getVertexData();
  /**
  @brief Get total textures of the material
  @return Total num texutures
  */
  int totalTextures();
  /**
  @brief Get the fragment glsl code
  @returnm Code glsl of fragment shader
  */
  std::string getFragmentData();
  /**
  @Brief Return the texture placed at i
  @return Texture of material on index i
  */
  std::shared_ptr<Texture> getTextureAt(int i);

  int getTotalLights();
  void setColor(vec3 color);
  vec3 getColor();
  Light lightAt(int i);
  //Variables
  bool is_compiled_;
  std::string vertex_data_;
  std::string fragment_data_;
private:
  MaterialSettings *material_settings_;
  void useMaterial();
  void compileShader(GLuint shader)const;

  GLint program_;



  





};


#endif