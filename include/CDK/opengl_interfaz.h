#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__

#include <memory>
#include "GL\glew.h"
#include <vector>
#include "types.h"  
#include <memory>
#include "CDK/buffer.h"
#include "CDK/material.h"

class OpenGlInterFaz{
public:

  /**
  @brief Use geometry whit VAO equals to vao variables
  @param vao VAO of the geometry to use

  */
  void useGeometry(GLuint vao);
  /**
  @brief Load geometry 
  @param buff The geometry buffer of mesh to laod
  */
  void loadBuffer(std::shared_ptr<Buffer> buff);
  /**
  @brief Use a specific material
  @param Program of the material to use
  */
  void useMaterial(int mat_program,Material::MaterialSettings& mat_s);
  /**
  @brief Load material shader .
  @param mat Current material pointer.
  @vertex_data Vertex shader code
  @fragment_data Fragment shader code
  @return program created.
  */
  int loadMaterial(const char*vertex_data, const char*fragment_data);


  /**
  @brief Compile shader passed as parameter
  @param shader Shader to compile
  */
  void compileShader(GLuint shader);
  /**
  @brief
  */
  void useUniformMat4(const char *name,const float* m_data);
  /**
  @brief
  */
  void useUnifor3f(const char *name, const float *data);
  /**
  @brief
  */
  void useUniformUi(const char *name,int value);
  /**
  @brief
  */
	void loadTexture(std::shared_ptr<Texture> m);
  /**
  @brief
  */
  void useTexture(int pro,int n_text,std::string u_name,int texture_id);
  /**
  @brief
  */
  void drawGeometry(unsigned int indices);
  /**
  @brief
  */
  void loadLight(int num_light);
  /**
  */
  void sendLight( Light *light);
  /**
  @brief
  */
  /**
  */
  void loadCamera();
  /**
  */

  void useCamera(mat4 proyection, mat4 model, mat4 view);
  /**
  */
  void createFrameBuffer();
  ~OpenGlInterFaz(){};

  friend class DisplayList;
private:
  struct Data;
	OpenGlInterFaz();
  Data *data_;
  friend class Buffer;
  friend class Camera;
  friend class Material;
 

};

#endif