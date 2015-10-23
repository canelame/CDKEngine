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
#include "opengl_interfaz.h"


/**
* camera.h 
* @author Alejandro Canela Mendez 2015.
* @brief This class represent an abtraction of a camera in opengGL.
*
*/

 
class Camera : public Command
{
public:
 
  
  Camera();
  void setPerspective(float fov, float aspect, float near, float far);
  void setLookAt(vec3 eye, vec3 center, vec3 up);
   ~Camera(){}; 
    void render(DisplayList &dl);
  void cull();
  void runCommand(OpenGlInterFaz &i, OpenGlInterFaz &out)const;
private:
	OpenGlInterFaz *interfaz_;
  mat4 proyection_mat_;
 mat4 look_at_mat_;


 vec3 position_;
  vec3 up_;
  vec3 right_;
  vec3 front_;
protected:
 

  
};



#endif