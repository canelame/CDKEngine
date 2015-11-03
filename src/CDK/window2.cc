#include "CDK/window2.h"

#include <stdio.h>

bool g_keys[1024];

void key_callback(GLFWwindow*window, int key, int scancode , int action, int mods){
 
  if (action == GLFW_PRESS){
    g_keys[key] = true;
  }
  else if (action == GLFW_RELEASE){
    g_keys[key] = false;
  }


}

struct Window::_Window{
  GLFWwindow* main_window_;
};
Window::Window(){
  window_s_ = new _Window;
}
int Window::main(int argc, char**argv){ return 0; }
bool Window::init(unsigned int width, unsigned int height){
	
	width_ = width;
	height_ = height;
	//Init GLFW
  if (!glfwInit()){
    printf("Error glfInit()");
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create Window
  window_s_->main_window_ = glfwCreateWindow(width_, height_, "Default name", nullptr, nullptr);

  if (window_s_->main_window_ == nullptr){
		printf("Error to create new window.\n");
		return false;
	}

  //Set ViewPort
  ImGui_ImplGlfwGL3_Init(window_s_->main_window_,true);
 
  glfwMakeContextCurrent(window_s_->main_window_);
  glfwSetKeyCallback(window_s_->main_window_, key_callback);
	//Init GLEW
	glewExperimental = GL_TRUE;

	if (glewInit()!=GLEW_OK){
	printf("Error to init GLEW.\n");
	return false;
	}
  glViewport(0, 0, width_, height_);
	return true;
	
}

bool Window::processEvents(){
  glfwPollEvents();
  
  if (g_keys[GLFW_KEY_ESCAPE]){
    return false;
  }  
  return true; 
}

void Window::swap(){

  glfwSwapBuffers(window_s_->main_window_);
}
void Window::finish(){
  glfwDestroyWindow(window_s_->main_window_);
	glfwTerminate();
}