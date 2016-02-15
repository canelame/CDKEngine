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
  unsigned int getProgram();
  /**
  @brief Set current program
  @param value New program
  */
  void setProgram(int value);


  unsigned int texture(){}
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


  void setColor(vec3 color);
  vec3 getColor();
  Light lightAt(int i);
  //Variables
  bool is_compiled_;
  std::string vertex_data_;
  std::string fragment_data_;
  
  class MaterialSettings{
  public:
    MaterialSettings();
    ~MaterialSettings();
    /**
    @brief add a texture to material
    @param txt new texture
    @param tk The current taskManager
    */
    void addTexture(const char*name);
    /**
    @Brief Return the texture placed at i
    @return Texture of material on index i
    */

    std::string getTextureAt(int index);
    /**
    @brief Get total textures of the material
    @return Total num texutures
    */
    float getShinenes();
    void setShinenes(float value);
    int totalTextures();

    void setDiffuseColor(vec3);
    void setSpecularColor(vec3);
    void setAmbientColor(vec3);

    vec3 getAmbientColor();
    vec3 getSpecularColor();
    vec3 getAmbienColor();
  
  private:
    struct Data;
    Data *data_;
  };
  void setMaterialSettings(std::shared_ptr<Material::MaterialSettings> mat_s);
  MaterialSettings& getMaterialSettings();
private:
  std::shared_ptr<MaterialSettings> mat_settings_;
  void useMaterial();
  void compileShader(GLuint shader)const;
  float getShinenes();
  void setShinenes(float value);
  unsigned int program_;









};


#endif