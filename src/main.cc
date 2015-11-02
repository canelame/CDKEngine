

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
 // g->loadObjFile("meshes/suzzane.obj");
  g->createCube(1);
  std::shared_ptr<Material> m;
  m = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE);
  m->loadTexture("textures/jovi.jpg");

  std::shared_ptr<Camera> c;
  c = std::make_shared<Camera>();
  c->setPerspective(45, 800.0 / 600.0, 1.0, 1000.0);

  std::shared_ptr< DisplayList> dl;
  dl = std::make_shared<DisplayList>();

  
 dl->add(m);
  dl->add(g);
  dl->add(c);
  


  
  while (g_win.processEvents()){
  //  task_manager_->addTask(std::make_shared<UpdateDisplay>(dl));
	  glClearColor(.3f, .2f, .7f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
	dl->execute();

    g_win.swap();
  }
 
}
int main(){

  
  createWindow();
 
  
  return 0;
}