#ifndef __H_CAMERA__
#define __H_CAMERA__
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
/**
* camera.h 
* @author Alejandro Canela Mendez 2015.
* @brief This class represent an abtraction of a camera in opengGL.
*
*/
class Camera
{
public:
  Camera();
  ~Camera();
  void setPerspective(float fov, float aspect, float near, float far);
  void setLookAt();
private:
  glm::mat4 proyection_mat_;
  glm::mat4 look_at_mat_;
};

Camera::Camera()
{
}

Camera::~Camera()
{
}

#endif