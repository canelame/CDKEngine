#ifndef __H_MATERIAL__
#define __H_MATERIAL__

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "CDK/Lights/light.h"

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
    
  class MaterialSettings{
  public:

    vec3 diffuse_color_;
    vec3 specular_color_;
    vec3 ambient_color_;
    vec3 sh_;
    bool loaded_;

    MaterialSettings( ){     
        ambient_color_ = vec3(1.0);
        specular_color_ = vec3(1.0);
        diffuse_color_ = vec3(1.0);
    }

    void setDiffuseColor(vec3 value){ 
      diffuse_color_ = value;
    }
    void setSpecularColor(vec3 value){
      specular_color_ = value; 
    }
    void setAmbientColor(vec3 value){ 
      ambient_color_ = value;
    }
    vec3 getDiffuseColor(){ 
      return diffuse_color_; 
    }
    vec3 getSpecularColor(){ 
      return specular_color_; 
    }
    vec3 getAmbientColor(){ 
      return ambient_color_;
    }
  };
  Material();
  ~Material(){};
  /**
  * @brief This function allows to load own shader.
  * @param vertex_file The name of vertex GLSL file.
  * @param fragment_file he name of fragment GLSL file.
  */
  void loadShader(const char*vertex_shader, const char*fragment_shader,const char* geometry_shader);
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

  /**
  @brief Set value to uniform 
  @param name The name of the uniform to set value
  @param val The value 
  */
  void setUniformUiValue(const char* uniform_name, unsigned int *val);
  /**
  @brief Set value to uniform
  @param name The name of the uniform to set value
  @param val The value
  */
  void setUniformIValue(const char* uniform_name,  int *val);
  /**
  @brief Set value to uniform
  @param name The name of the uniform to set value
  @param val The value
  */
  void setUniformFValue(const char* uniform_name, float *val);
  /**
  @brief Set value to uniform
  @param name The name of the uniform to set value
  @param val The value
  */
  void setUniformMat4Value(const char* uniform_name, mat4 *val);
  /**
  @brief Set value to uniform
  @param name The name of the uniform to set value
  @param val The value
  */
  void setUniformMat3Value(const char* uniform_name, mat3 *val);
  /**
  @brief Set value to uniform
  @param name The name of the uniform to set value
  @param val The value
  */
  void setUniform3fValue(const char* uniform_name, vec3 *val);
  /**
  @brief Get uniform location by name
  @param name The name of the uniform to set value
  */
  int getUniformLocation(const char * name);

  //Variables
  bool is_compiled_ = false;
  std::string vertex_data_;
  std::string fragment_data_;
  std::string geometry_data_;
  int type_;


  protected:

  enum UniformTypes{
    kUniformTypesInt,
    kUniformTypesUInt,
    kUniformTypesFloat,
    kUniformTypes3vFloat,
    kUniformTypesMat3,
    kUniformTypesMat4,
    kUniformTypesSampler2D,
    kUniformTypesCubeSampler
  };
  struct UniformData{
    std::string name_;
    UniformTypes type_;
    int location_;
    void *data_;
    UniformData(){}
    UniformData(char*name, UniformTypes ut, int location, void *data){
      name_ = name; type_ = ut;  location_ = location; data_ = data;
    }
  };
  //This two vectors are use to store uniforms, i used 2 vectors to discard std::map
  //Firs vector are for names and the seconds for the uniform position
  std::vector<std::string> uniforms_names;
  std::vector<int > uniforms_values;
  UniformTypes value_type_;
  std::vector<UniformData> uniforms_;
  bool uniforms_loaded_;
  unsigned int program_;
  /**
  @brief return information about a uniform
  @param name Uniform name to get info
  */
  UniformData* findUniform(const char * name);
 
  private:
  void useMaterial();
  /**
  @brief Used to compile internally the shadder
  @param shader Id shader to compuile
  */
  void compileShader(GLuint shader)const;

  friend class OpenGlInterFaz;
  

};


#endif