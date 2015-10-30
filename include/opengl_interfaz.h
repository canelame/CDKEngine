#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__

#include <memory>
#include "GL\glew.h"
#include <vector>
#include "types.h"  

class OpenGlInterFaz{
public:
  struct Data;
  OpenGlInterFaz();
  void drawGeometry();
  void useGeometry();
  void loadBuffer(std::vector<std::vector<float>> attributes, std::vector<unsigned int> &index);
  void useMaterial();
  void loadMaterial(const char*vertex_data, const char*fragment_data);
  void compileShader(GLuint shader);
  void useUniformMat4(const char *name,const float* m_data);
  void useUnifor3f(const char *name, const float *data);
  void useUniformUi(const char *name,int value);
  void loadTexture(const char *file);
  void useTexture();

  ~OpenGlInterFaz(){};
private:
  Data *data_;
 

};

#endif