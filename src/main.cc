

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
void createWindow(){
  Window g_win;
 
  if (!g_win.init(800, 600)){
    printf("Error to init window.\n");
  }

  
  std::shared_ptr<Geometry> g;
  g = std::make_shared<Geometry>();
  g->loadObjFile("mycube.obj");
  
  std::shared_ptr<Material> m;
  m = std::make_shared<Material>(Material::TYPE::ONNLY_DIFFUSE_);


  std::shared_ptr<Camera> c;
  c = std::make_shared<Camera>();

  DisplayList dl;
  dl.add(g);
  dl.add(m);
  

  c->setPerspective(45.0f, 800.0 / 60.0, 1.0, 1000.0);
  
  while (g_win.processEvents()){
  
    dl.execute();

    g_win.swap();
  }
 
}
int main(){

  
  std::thread t1(createWindow);
  t1.join();

 
  
  return 0;
}