#ifndef __H_CAMERA__
#define __H_CAMERA__

#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ref_counter.h"
#include "raii_pointer.h"
#include "base.h"
#include "types.h"
#include "opengl_interfaz.h"
#include "node.h"
/**
* camera.h 
* @author Alejandro Canela Mendez 2015.
* @brief This class represent an abtraction of a camera in opengGL.
*
*/
 
class Camera 
{

public:
  vec3 position_;
  vec3 model_scale;
  struct Data;
  Camera();
  ~Camera(){};
  /**
  * @brief This function allow us to set the perspective projection matrix.
  * @param fov Field of view cam. Should be 45.0f
  * @param aspect Aspect Ratio of the cam. Should be WIDTH/HEIGHT
  * @param near Near point of the camera.
  * @param far Far point of the camera.

  */
  void setPerspective(float fov, float aspect, float near, float far);
  /**
  * @brief This function allow us to set up the view projection matrix.
  * @param eye Where is the position of observer, in this case the camera position.
  * @param center Where is the front of the camera, where is the camera front.
  * @param up Vector that represents Where is the up of the camera, should be vec3(0.0,1.0,0.0)
  */
  void setLookAt(vec3 eye, vec3 center, vec3 up);
  void render(std::shared_ptr<Node> node);
  void cull();
  glm::mat4 getModel();
  glm::mat4 getProyection();
  glm::mat4 getView();
  /**
  * @brief Runs the command 
  */
  void runCommand(OpenGlInterFaz &i)const;
  friend class OpenGlInterFaz;
private:
  Data *data;

};

#endif