#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__

#include <memory>
#include "GL\glew.h"
#include <vector>
#include "types.h"  
#include <memory>
#include "CDK/buffer.h"
#include "CDK/material.h"
#include "frame_buffer.h"
class PointLight;
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
  void loadBuffer(Buffer* buff);
  /**
  @brief Use a specific material
  @param Program of the material to use
  */
  void useMaterial(Material &mat, vec3 color_amb, vec3 color_diff, vec3 color_spe);
  /**
  @brief Load material shader .
  @param mat Current material pointer.
  @vertex_data Vertex shader code
  @fragment_data Fragment shader code
  @return program created.
  */
  int loadMaterial(Material * mat);


  /**
  @brief Compile shader passed as parameter
  @param shader Shader to compile
  */
  void compileShader(GLuint shader);
  /**
  @brief
  */
  void useUniformMat4(mat4 m);
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
  void drawGeometry(int vao,unsigned int indices);
  /**
  @brief
  */
  void loadLight(int num_light);
  /**
  */
  void sendLight( Light *light,int num_light,bool is_directional);
  /**
  @brief
  */

  void useCamera(mat4 proyection, mat4 model, mat4 view);
  /**
  */
  void createFrameBuffer(FrameBuffer &fb, bool use_render_buffer);
  /**
  */
  void renderFrameBuffer(FrameBuffer &fb);
  /**
  */
  void bindFrameBuffer(int fb_id,FrameBuffer::kFramebufferBindType type);

  /**
  */
  void setDrawBuffer(int fb_id);
  /**
 */
  void setReadBuffer(int fb_id);
  ~OpenGlInterFaz(){};
  /**
  */
  void renderShadows(int program,mat4 light_proyection_space);
  /**
  */
  void setDepthRenderTarget(int value);
  /**
  */
  void setLightProyection(mat4 mat);
  /**
  */
  void loadDirectionalLight();

  /**
  */
  void sendPointLightMatrix(const int &n_light, const int n_mat, const  mat4 mat);
  void sendPointLightFar(vec3 pos_light, float far);
  //Return depth buffer id
  void  createShadoCubeMap(PointLight * pl);
  void usePointShadowModel(mat4 m);
  static OpenGlInterFaz& instance();
  
private:
 
  struct Data;
 static OpenGlInterFaz *instance_;
	OpenGlInterFaz();
  Data *data_;
  friend class Buffer;
  friend class Camera;
  friend class Material;
 

};

#endif