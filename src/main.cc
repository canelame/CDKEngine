

#include <stdio.h>
#include "window2.h"
#include "raii_pointer.h"
#include <thread>
#include "geometry.h"
#include "camera.h"
#include "display_list.h"
#include "draw.h"
#include <memory>
#include "material.h"
#include "task_manager.h"
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw_gl3.h"


void imGuiWindow(glm::vec3 &scale, glm::vec3 &cam_position){
  float size[3] = { scale.x, scale.y, scale.z };
  float position[3] = {cam_position.x,cam_position.y,cam_position.z};
  ImGui::SetWindowSize(ImVec2(200, 100), 0);
  ImGui::Begin("Window");
  ImGui::Text("Camera Mocement");
  ImGui::SliderFloat3("Position cam", position, 0, 100);
  ImGui::SliderFloat3("Scale object", size, 0, 100);
  ImGui::End();
  scale.x = size[0]; scale.y = size[1]; scale.z = size[2];
  cam_position.x = position[0]; cam_position.y = position[1]; cam_position.z = position[2];
  ImGui::Render();
}
void createWindow(){
  Window g_win;
 
  if (!g_win.init(800, 600)){
    printf("Error to init window.\n");
  }
  
  std::unique_ptr<TaskManager> task_manager_;
  task_manager_ = std::make_unique<TaskManager>();
  task_manager_.get()->init();
  
  std::shared_ptr<Geometry> g;
  g = std::make_shared<Geometry>();
  g->createCube(1);
 // g->loadObjFile("meshes/suzzane.obj");
 // g->loadObjFile("meshes/suzzane.obj");
  std::shared_ptr<Material> m;
  m = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE);
  m->loadTexture("textures/jovi.jpg");

  std::shared_ptr<Camera> c;
  c = std::make_shared<Camera>();
  c->setPerspective(45, 800.0 / 600.0, 1.0, 1000.0);

  std::shared_ptr< DisplayList> dl;
  dl = std::make_shared<DisplayList>();



  //dl->add(std::make_shared <LoadMaterialCommand>(g) );
  //dl->add(std::make_shared<UseMaterialCommand>() );
  dl->add( std::make_shared<LoadGeometryCommand>(m) );
  //dl->add(std::make_shared<>);
 


  
  while (g_win.processEvents()){
    ImGui_ImplGlfwGL3_NewFrame();
  //  task_manager_->addTask(std::make_shared<UpdateDisplay>(dl));
	  glClearColor(.3f, .2f, .7f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
  	dl->execute();
   imGuiWindow(c.get()->model_scale,c.get()->position_);
    g_win.swap();
  }
 
}
int main(){

  
  createWindow();
 
  
  return 0;
}