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
  struct Data;


  void useGeometry(GLuint vao);
  void loadBuffer(std::shared_ptr<Buffer> buff);
  void useMaterial(int mat_program);
  /**
  @brief Load material shader .
  @param mat Current material pointer.
  @vertex_data Vertex shader code
  @fragment_data Fragment shader code
  @return program created.
  */
  int loadMaterial(const char*vertex_data, const char*fragment_data);
  void compileShader(GLuint shader);
  void useUniformMat4(const char *name,const float* m_data);
  void useUnifor3f(const char *name, const float *data);
  void useUniformUi(const char *name,int value);
	void loadTexture(std::shared_ptr<Texture> m);
  void useTexture(int pro,std::shared_ptr<Texture>m,int n_text,std::string u_name);
  void drawGeometry(unsigned int indices);
  void sendLight( Light *light, int num_light);
  ~OpenGlInterFaz(){};

  friend class DisplayList;
private:

	OpenGlInterFaz();
  Data *data_;
  friend class Buffer;
  friend class Camera;
  friend class Material;

};

#endif