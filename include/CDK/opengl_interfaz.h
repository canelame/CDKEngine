#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__

#include <memory>
#include "GL\glew.h"
#include <vector>
#include "types.h"  

#include <memory>
#include "CDK/buffer.h"
class OpenGlInterFaz{
public:
  struct Data;


  void useGeometry(GLuint vao);
  void loadBuffer(std::shared_ptr<Buffer> buff);
  void useMaterial();
  void loadMaterial(const char*vertex_data, const char*fragment_data);
  void compileShader(GLuint shader);
  void useUniformMat4(const char *name,const float* m_data);
  void useUnifor3f(const char *name, const float *data);
  void useUniformUi(const char *name,int value);
  void loadTexture(unsigned char *file,int w_texture, int _texture);
  void useTexture();
  void drawGeometry(std::vector<unsigned int> indices);

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