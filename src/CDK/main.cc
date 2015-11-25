#include <chrono>
#include <stdio.h>
#include <memory>
#include "CDK/window2.h"
#include "CDK/geometry.h"
#include "CDK/camera.h"
#include "CDK/display_list.h"
#include "CDK/draw.h"
#include "CDK/material.h"
#include "CDK/task_manager.h"
#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_glfw_gl3.h"
#include "CDK/node.h"

struct {
	std::shared_ptr<Node> root;
	std::shared_ptr<Camera> cam;

}Scene;

void imGuiWindow(glm::vec3 &scale, glm::vec3 &cam_position,std::shared_ptr<Node> &t_n){
  float size[3] = { scale.x, scale.y, scale.z };
  float rotation[3] = { t_n.get()->rotation().x, t_n.get()->rotation().y, t_n.get()->rotation().z };
  float position[3] = {cam_position.x,cam_position.y,cam_position.z};
  ImGui::SetWindowSize(ImVec2(200, 100), 0);
  ImGui::Begin("Window");
  ImGui::Text("Camera Mocement");
  ImGui::SliderFloat3("Position cam", position, 0, 100);
  ImGui::SliderFloat3("Scale object", size, 0, 100);
  ImGui::SliderFloat3("Rotation object", rotation, 0, 100);
  ImGui::End();
  scale.x = size[0]; scale.y = size[1]; scale.z = size[2];
  cam_position.x = position[0]; cam_position.y = position[1]; cam_position.z = position[2];
  t_n.get()->setRotation(vec3(rotation[0],rotation[1], rotation[2]));
  ImGui::Render();
}

void createWindow(){
  Window g_win;
 
  if (!g_win.init(800, 600)){
    printf("Error to init window.\n");
  }
  //Create Task Manager
	  std::shared_ptr<TaskManager> task_manager_;
	  task_manager_ = std::make_shared<TaskManager>();
	  task_manager_.get()->init();
  
  //Create Geometry
  
	  std::shared_ptr<Geometry> g;
	  g = std::make_shared<Geometry>();
    g->loadCdkFormat("meshes/sphere.cdk",true);
	  std::shared_ptr<Geometry> g2;
	  g2 = std::make_shared<Geometry>();
	  g2->loadObjFile("meshes/suzzane.obj");
  //Create Material
  
	  std::shared_ptr<Material> m;
	  m = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE,task_manager_);

    std::shared_ptr<Material> m2;
    m2 = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE,task_manager_);

    std::shared_ptr<Texture> txt1 = std::make_shared<Texture>();
    txt1->loadTexture("textures/jovi.jpg");
    m->setTexture(txt1);

    std::shared_ptr<Texture> txt2 = std::make_shared<Texture>();
    txt2->loadTexture("textures/red.png");
    m2->setTexture(txt2);
	 
  
  //Create Camera
  
	  Scene.cam = std::make_shared<Camera>();
	  Scene.cam->setPerspective(45, 800.0 / 600.0, 1.0, 1000.0);
	//Create Root
	  Scene.root = std::make_shared<Node>();
 //Create Display List
	  std::shared_ptr< DisplayList> dl;
	  dl = std::make_shared<DisplayList>();

  for (int i = 0; i <5; i++){
	  std::shared_ptr<Drawable> drawable;
	  drawable = std::make_shared<Drawable>();
	  
    if (i == 1){
      drawable->setGeometry(g2);
      drawable->setMaterial(m2);
    }
    else{
      drawable->setGeometry(g);
      drawable->setMaterial(m);
    }
	 
    drawable->setPosition(vec3( (-1.0+(i*2)), 0.0, -2.0+(i*2.0) ));
	
    drawable->setScale(vec3(5.0,5.0,5.0));
    Scene.root.get()->addChild(drawable);
  }
  Scene.root.get()->setPosition(vec3(0.0, 0.0, -50.0));
  Scene.root.get()->setRotation(vec3(0.0,0.0,0.0));

  while (g_win.processEvents()){
    auto start_c = std::chrono::steady_clock::now();
		ImGui_ImplGlfwGL3_NewFrame();
		task_manager_->addTask(std::make_shared<UpdateDisplay>(dl));
		glClearColor(.3f, .2f, .7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable(GL_DEPTH_TEST);
		Scene.cam->render(Scene.root);
		imGuiWindow(Scene.cam.get()->model_scale, Scene.cam.get()->position_,Scene.root);
		g_win.swap();
   
  }
	task_manager_->~TaskManager();
}

int main(){

  
  createWindow();
	printf("");
  
  return 0;
}