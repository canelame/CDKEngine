#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__
#include <memory>
#include "GL\glew.h"
#include <vector>
#include "types.h"

class OpenGlInterFaz{
public:
	OpenGlInterFaz(){
		
	};
  void useDrawGeometry();
  void useGeometry();
  void loadBuffer(std::vector<std::vector<float>> attributes, std::vector<unsigned int> &index);
  void useMaterial();
  void loadMaterial(const char*vertex_data, const char*fragment_data);
  void compileShader(GLuint shader);
  void useUniformMat4(const char *name,const float* m_data);
  void useUnifor3f(const char *name, const float *data);

  ~OpenGlInterFaz(){};
private:
  //For materials
  GLuint shadow_program_;
  GLuint shadow_vertex_shader_;
  GLuint shadow_fragment_shader_;

  //For geometries
  GLuint shadow_vao_;
  GLuint shadow_vbo_v_;
  GLuint shadow_vbo_i_;
  std::vector<float> shadow_attrib_[3];
  std::vector<unsigned int > shadow_index_;

};

#endif