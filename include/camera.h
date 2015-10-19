#ifndef __H_CAMERA__
#define __H_CAMERA__
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ref_counter.h"
#include "raii_pointer.h"
#include "base.h"
#include "display_list.h"
#include "types.h"


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
  void setPerspective(float fov, float aspect, float near, float far);
  void setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
   ~Camera(){}; 
    void render(DisplayList &dl);
  void cull();
private:
 
  glm::mat4 proyection_mat_;
  glm::mat4 look_at_mat_;

  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 front_;
protected:
 

  
};



#endif