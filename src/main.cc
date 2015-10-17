

#include <stdio.h>
#include "window2.h"
#include "raii_pointer.h"
#include <thread>
#include "geometry.h"
#include "camera.h"
#include "display_list.h"
#include "draw.h"
#include <memory>
void createWindow(){
  Window g_win;
 
  if (!g_win.init(800, 600)){
    printf("Error to init window.\n");
  }
  raii_pointer<Camera> c;
  c.alloc();
  
  std::shared_ptr<Geometry> g;
  g = std::make_shared<Geometry>();
  
  

  DisplayList dl;
  dl.add(g);
  dl.execute();

  

  

                                               
  

  
  
  while (g_win.processEvents()){
    float ratio = 800 / (float)600;
    glViewport(0, 0, 800, 600);

    glClear(GL_COLOR_BUFFER_BIT);

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
  getchar();
}
int main(){


  std::thread t1(createWindow);
  t1.join();

  getchar();
  
  return 0;
}