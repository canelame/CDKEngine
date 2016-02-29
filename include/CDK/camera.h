#ifndef __H_CAMERA__
#define __H_CAMERA__

#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "types.h"
#include "opengl_interfaz.h"
#include "drawable.h"

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
  ~Camera(){};
  /**
  @brief This function allow to user control camera as a fps game. 
  * To use it only call this function in your update funtion.
  */
  void FpsCameraUpdate();
  void controlMouse();
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

  /**
  @brief Set camera position
  @param position New position
  */
  void setPosition(vec3 position);
  /*@brief Set front position
    @param position New front
  */
  void setFront(vec3 front);
  /**
  @brief Render the scene which is loaded in one root node
  @param node Root node
  @param tk TaskManager
  */
  void render(std::shared_ptr<Node> node);
  /**
  @brief Get model cam.
  */
  mat4 getModel(vec3 position, vec3 rotation, vec3 scale);
  /**
  @brief Get proyection matrix of the camera
  @return proyection matrix
  */
  mat4 getProyection();
  /**
  @brief Get view matrix cam
  @return View matrix
  */
  mat4 getView();

  void setLoaded(bool value);
  bool getLoaded();
private:
  struct Data;
  ///Internal Data
  Data *data_;
  /**
  @brief Load node and puts into the display list.
  @param node Root node
  */
  void loadNode(std::shared_ptr<Node> node);

};

#endif