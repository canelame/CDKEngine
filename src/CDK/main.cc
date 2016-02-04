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

#include "CDK/node.h"
#include "CDK/loader.h"
#include "glm\glm.hpp"
Window g_win;

struct {
	std::shared_ptr<Node> root;
	std::shared_ptr<Camera> cam;

}Scene;

void createWindow(){
 
  bool up = false;
  if (!g_win.init(800, 600)){
    printf("Error to init window.\n");
  }
  //Create Task Manager
	  std::shared_ptr<TaskManager> task_manager_;
	  task_manager_ = std::make_shared<TaskManager>();
	  task_manager_.get()->init();

  //Create Geometry
  
    std::unique_ptr<Loader> loader = std::make_unique<Loader>();

    std::shared_ptr<Drawable> w = loader->loadCDK("meshes/paris.cdk", task_manager_);
    printf("Loaded\n");

    std::shared_ptr<Light> l1 = std::make_shared<Light>();
    l1->setPosition(vec3(0.0, 0.0, 95.0));
    l1->setAmbientColor(vec3(1.0, 0.0, 0.0));
    l1->setDifusseColor(vec3(0.0,1.0,0.0));
  //Create Camera
  
	  Scene.cam = std::make_shared<Camera>();
	  Scene.cam->setPerspective(45, 800.0 / 600.0, 0.1, 100000.0);
	//Create Root
	  Scene.root = std::make_shared<Node>();


   w->setPosition(vec3(0.0, 3.0, 0.0));
   //w->setScale(vec3(1, 1, 1));



//   w->material()->setColor(vec3(1.0, 0.0, 0.0));

   Scene.root.get()->addChild(w);
   Scene.root.get()->setPosition(vec3(0.0, -5.0, 95.0));
   Scene.root.get()->setRotation(vec3(0,0,0));


   Scene.root.get()->addLight(*l1.get());
   double next_frame = 0;
   double deltaTime = 0.0; 
   float angle=96.0f;
  while (g_win.processEvents()){

      Scene.cam->FpsCameraUpdate();

      glClearColor(.3f, .2f, .7f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      angle += 0.002;


      Scene.cam->render(Scene.root,task_manager_.get());

      g_win.swap();
    
  }

 //task_manager_->~TaskManager();
}

int main(){

  
  createWindow();
	printf("");
  
  return 0;
}