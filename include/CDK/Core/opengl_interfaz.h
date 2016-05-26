#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__


#include <memory>
#include <vector>
#include "CDK/Core/types.h"  
#include <memory>
#include "CDK/Core/buffer.h"
#include "CDK/Material/material.h"
#include "CDK/Misc/frame_buffer.h"


class PointLight;
class OpenGlInterFaz{
public:

  ~OpenGlInterFaz(){};
  /**
  @brief Singleton instance
  @return Pointer to singlenton reference
  */
  static OpenGlInterFaz& instance();
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
  void useMaterial(Material*mat);
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
  @brief Use matrix 4 uniform  to current active material
  @param m Value to sent
  */
  void useUniformMat4(int position,mat4 m);
  /**
  @brief Use matrix 4 uniform  to current active material
  @param m Value to sent
  */
  void useUniformMat3(int position, mat3 m);
  /**
  @brief Use matrix 4 uniform  to current active material
  @param m Value to sent
  */
  void useUnifor3f(int position, vec3 data);
  /**
  @brief Use matrix 4 uniform  to current active material
  @param data Value to sent
  */
  void useUniformUi(int position, unsigned int value);
  /**
  @brief Use matrix 4 uniform  to current active material
  @param value Value to sent
  */
  void useUniformI(int position, unsigned int value);
  /**
  @brief Use matrix 4 uniform  to current active material
  @param value Value to sent
  */
  void useUniformF(int position, float value);
  /**
  @brief Used to load a teture to GPU
  @param t Current texture to load.
  */
	void loadTexture(std::shared_ptr<Texture> t);
  /**
  @brief Use texture
  @param position Location of texture uniform.
  @param texture_id Id of the texture, is setted when texture is laoded to GPU.
  */
  void useTexture(int position,int texture_id);
  /**
  @brief Draw object
  @param vao Object vao
  @param indices Indices number of the object
  */
  void drawGeometry(int vao, unsigned int buffer_indeces, unsigned int indices);
  /**
  @brief Create and load new framebuffer to GPU
  @param fb Current framebuffer
  */
  void createFrameBuffer(FrameBuffer &fb);
  /**
  @brief  Bind a framebuffer
  @param fb_id Framebuffer id
  @aram type Binding type
  */
  void bindFrameBuffer(int fb_id,FrameBuffer::kFramebufferBindType type);
  /**
  @brief Set drawmode of a framebuffer
  */
  void setDrawBuffer(int fb_id);
  /**
  @brief Set drawmode of a framebuffer
  */
  void setReadBuffer(int fb_id);
  /**
  @brief Create Cubemap to point light
  @param pl PointLight to create a cubemap
  */
  void  createShadoCubeMap(PointLight * pl);
  /**
  @brief Use material of diffuse type
  @param mat Material to load
  @param mat_sett Settings of materil
  @param cam_view Camera view matrix
  @param cam_proyc Camera proyection matrix
  @param model Camera model matrix
  @param dir_light Scene directional light
  @param lights Point lighs of scene
  */
  void useDiffuseMaterial(Material *mat, Material::MaterialSettings *mat_sett,
    mat4 cam_view, mat4 cam_proy, mat4 model, Light *dir_light, std::vector<std::shared_ptr<Light>> lights);
  /**
  @brief
  @param mat Use material of texture type
  @param mat_sett Settings of materil
  @param cam_view Camera view matrix
  @param cam_proyc Camera proyection matrix
  @param model Camera model matrix
  @param dir_light Scene directional light
  @param lights Point lighs of scene
  */
  void useTextureMaterial(Material *mat,Material::MaterialSettings *mat_sett,
                         mat4 cam_view, mat4 cam_proy, mat4 model , Light *dir_light ,std::vector<std::shared_ptr<Light>> lights);

  /**
  @brief Get info about uniform 
  @param program Material program
  @param index Uniform indix inside the program
  @param name Uniform name
  @param out_location Uniform location
  @param out_type Uniform type
  @return
  */
  void getUniformInfo(int program, int index,std::string &name, int &out_location,
    Material::UniformTypes &out_type);
  /**
  @brief Get the location of an uniform insede a prgram
  @param program Material program
  @param name Uniform name
  @return 
  */
  int getUniformIndex(int program, const char*name);
  /**
  @brief Use uniforms of one material
  @param  material Material to use uiforms
  @return
  */
  void useMaterialUniforms(Material * material);
private:
  OpenGlInterFaz();
  static OpenGlInterFaz *instance_;
  friend class Buffer;
  friend class Camera;
  friend class Material;
  friend class Light;
 

};

#endif