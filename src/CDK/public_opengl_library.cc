#include "CDK/public_opengl_library.h"
#include "GL\glew.h"
#include "CDK/opengl_interfaz.h"
OpenglInterfazPublic::OpenglInterfazPublic(){
}

OpenglInterfazPublic& OpenglInterfazPublic::instace(){
  if (instance_ptr_ == nullptr){
    instance_ptr_ = new OpenglInterfazPublic();
  }
  return *instance_ptr_;
}

void OpenglInterfazPublic::useMaterial(unsigned int id){
  glUseProgram((GLuint)id);
}

void OpenglInterfazPublic::setDrawMode(int mode){
  OpenGlInterFaz::instance().draw_mode_ = mode;
}
