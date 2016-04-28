#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__

#include <memory>
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
  void useMaterial(int program_id);
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
  @param
  @return
  */
  void useUniformMat4(int position,mat4 m);
  /**
  @brief
  @param
  @return
  */
  void useUniformMat3(int position, mat3 m);
  /**
  @brief
  @param
  @return
  */
  void useUnifor3f(int position, const float *data);
  /**
  @brief
  @param
  @return
  */
  void useUniformUi(int position, unsigned int value);
  /**
  @brief
  @param
  @return
  */
  void useUniformI(int position, unsigned int value);
  /**
  @brief
  @param
  @return
  */
  void useUniformF(int position, float value);
  /**
  @brief
  @param
  @return
  */
	void loadTexture(std::shared_ptr<Texture> m);
  /**
  @brief
  @param
  @return
  */
  void useTexture(int position,int texture_id);
  /**
  @brief
  @param
  @return
  */
  void drawGeometry(int vao, unsigned int indice);
  /**
  @brief
  @param
  @return
  */
  void loadLight(int num_light);
  /**
  @brief
  @param
  @return
  */
  void sendLight( Light *light,Material * mat,int num_light,bool is_directional);
  /**
  @brief
  @param
  @return
  */
  void createFrameBuffer(FrameBuffer &fb, bool use_render_buffer);
  /**
  @brief
  @param
  @return
  */
  void renderFrameBuffer(FrameBuffer &fb);
  /**
  @brief
  @param
  @return
  */
  void bindFrameBuffer(int fb_id,FrameBuffer::kFramebufferBindType type);
  /**
  @brief
  @param
  @return
  */
  void setDrawBuffer(int fb_id);
  /**
  @brief
  @param
  @return
  */
  void setReadBuffer(int fb_id);
  /**
  @brief
  @param
  @return
  */
  ~OpenGlInterFaz(){};
  /**
  @brief
  @param
  @return
  */
  void renderShadows(int program,mat4 light_proyection_space);

  /**
  @brief
  @param
  @return
  */
  void setLightProyection(mat4 mat);

  /**
  @brief
  @param
  @return
  */
  void sendPointLightMatrix(const int &n_light, const int n_mat, const  mat4 mat);
  /**
  @brief
  @param
  @return
  */
  void sendPointLightFar(vec3 pos_light, float far);
  /**
  @brief
  @param
  @return
  */
  void  createShadoCubeMap(PointLight * pl);
  /**
  @brief
  @param
  @return
  */
  void usePointShadowModel(mat4 m);
  /**
  @brief
  @param
  @return
  */
  static OpenGlInterFaz& instance();
  /**
  @brief
  @param
  @return
  */
  void useDiffuseMaterial(Material * mat);
  /**
  @brief
  @param
  @return
  */
  void useTextureMaterial(Material *mat,Material::MaterialSettings *mat_sett,
                         mat4 cam_view, mat4 cam_proy, mat4 model , Light *dir_light ,std::vector<std::shared_ptr<Light>> lights);
  /**
  @brief
  @param
  @return
  */
  void useShadowMapMaterial(Material* shadow_map_material, mat4 light_rojection_mat);
  /**
  @brief
  @param
  @return
  */
  void useShadowCubeMapMaterial(Material * mat,vec3 li);

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