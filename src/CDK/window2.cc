#include "CDK/window2.h"

#include <stdio.h>
#include "CDK/input.h"
#include "CDK/task_manager.h"
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw_gl3.h"
#include "CDK/gui_interface.h"
#include "CDK/engine_manager.h"

void key_callback(GLFWwindow*window, int key, int scancode , int action, int mods){
 
  if (action == GLFW_PRESS){
    Input::instance().setInputPress(key);
  }
  else if (action == GLFW_RELEASE){
    Input::instance().setInputRealease(key);
  }


}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
  Input::instance().setMouseXY(xpos, ypos);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  EngineManager::instance().window_size_modified_ = true;
  EngineManager::instance().setWidth(width);
  EngineManager::instance().setHeight(height);
  glViewport(0, 0, width, height);
}
struct Window::_Window{
  GLFWwindow* main_window_;
  int32 width_ = 800;
  int32 height_ = 600;
};
Window::Window(){
  window_s_ = new _Window;
}
int main(int argc, char**argv){ 
	TaskManager::instance().init();
  EngineManager::instance().init();
  Window::main(argc,argv);
  return 0;
}

void Window::clearScreen(vec3 color){
	glClearColor(color.x, color.y, color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

bool Window::init(unsigned int width, unsigned int height){
	
	window_s_->width_ = width;
	window_s_->height_ = height;
  EngineManager::instance().setWidth(width); EngineManager::instance().setHeight(height);
	//Init GLFW
  if (!glfwInit()){
    printf("Error glfInit()");
    return false;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Create Window
  window_s_->main_window_ = glfwCreateWindow(window_s_->width_, window_s_->height_, "Default name", nullptr, nullptr);

  if (window_s_->main_window_ == nullptr){
		printf("Error to create new window.\n");
		return false;
	}

  //Set ViewPort

  ImGui_ImplGlfwGL3_Init(window_s_->main_window_, true);
 
  glfwMakeContextCurrent(window_s_->main_window_);
  glfwSetKeyCallback(window_s_->main_window_, key_callback);
  glfwSetCursorPosCallback(window_s_->main_window_, mouse_callback);
  glfwSetFramebufferSizeCallback(window_s_->main_window_, framebuffer_size_callback);
	//Init GLEW
	glewExperimental = GL_TRUE;

	if (glewInit()!=GLEW_OK){
	printf("Error to init GLEW.\n");
	return false;
	}
  glViewport(0, 0, window_s_->width_, window_s_->height_);
	return true;
	
}

bool Window::processEvents(){
  glfwPollEvents();

  ImGui_ImplGlfwGL3_NewFrame();
  
  return true; 
}

void Window::swap(){

  glfwSwapBuffers(window_s_->main_window_);
}
void Window::finish(){
  glfwDestroyWindow(window_s_->main_window_);
	glfwTerminate();
}