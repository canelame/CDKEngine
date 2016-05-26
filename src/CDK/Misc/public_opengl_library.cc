#include "CDK/Misc/public_opengl_library.h"
#include "GL\glew.h"
OpenglInterfazPublic* OpenglInterfazPublic::instance_ptr_ = nullptr;
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


int OpenglInterfazPublic::getUniformLocation(int program, char * name){
  return glGetUniformLocation(program, name);
}
