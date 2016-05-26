#include "CDK/Core/input.h"
#include "GLFW\glfw3.h"

bool Input::g_keys[1024];
 std::unique_ptr<Input>Input::instance_;
 float Input::mouseX_;
 float Input::mouseY_;
Input& Input::instance(){
  if (instance_ = NULL){
    instance_ = std::make_unique<Input>();
  }
  return *instance_.get();
}

bool Input::pressKeyW(){
  if (g_keys[GLFW_KEY_W] == true){
    return true;
  }
  else{
    return false;
  }

 
}
bool Input::pressKeyS(){
  if (g_keys[GLFW_KEY_S] == true){
    return true;
  }
  else{
    return false;
  }
}
bool Input::pressKeyA(){
  if (g_keys[GLFW_KEY_A] == true){
    return true;
  }
  else{
    return false;
  }
}
bool Input::pressKeyD(){
  if (g_keys[GLFW_KEY_D] == true){
    return true;
  }
  else{
    return false;
  }
}
float Input::getMouseX(){
  return mouseX_;
}
float Input::getMouseY(){
  return mouseY_;
}
void Input::setInputPress(int key){
  g_keys[key] = true;
}
void Input::setInputRealease(int key){
  g_keys[key] = false;
}

void Input::setMouseXY(float x,float y){
  mouseX_ = x;
  mouseY_ = y;
}
void Input::setMouseY(float y){
  mouseY_ = y;
}

bool Input::pressSpace(){
  if (g_keys[GLFW_KEY_SPACE]){
    return true;
  }
  return false;
}

bool Input::pressL(){
  if (g_keys[GLFW_KEY_L]==true){
    return true;
  }
  return false;
}