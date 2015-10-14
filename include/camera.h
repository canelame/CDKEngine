#ifndef __H_CAMERA__
#define __H_CAMERA__
#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ref_counter.h"
#include "raii_pointer.h"
#include "base.h"


/**
* camera.h 
* @author Alejandro Canela Mendez 2015.
* @brief This class represent an abtraction of a camera in opengGL.
*
*/


class Camera: virtual public Ref_Counter, Base
{
public:
 
  

  void setPerspective(float fov, float aspect, float near, float far);
  void setLookAt();
  virtual ~Camera(){};
private:
  Base sett_;
  glm::mat4 proyection_mat_;
  glm::mat4 look_at_mat_;
protected:
  Camera(){};
  friend raii_pointer<Camera>;
  
};



#endif