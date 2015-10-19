

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
  g->loadObjFile("Cube.obj");
  
  std::shared_ptr<Material> m;
  m = std::make_shared<Material>(Material::TYPE::ONNLY_DIFFUSE_);


  std::shared_ptr<Camera> c;
  c = std::make_shared<Camera>();

  DisplayList dl;
  dl.add(g);
  dl.execute();

  c->setPerspective(45.0f, 800.0 / 60.0, 1.0, 1000.0);
  
  while (g_win.processEvents()){
    float ratio = 800 / (float)600;
    glViewport(0, 0, 800, 600);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 1.0);
 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
    g_win.swap();
  }
 
}
int main(){

  
  std::thread t1(createWindow);
  t1.join();

 
  
  return 0;
}