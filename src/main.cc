

#include <stdio.h>
#include "window2.h"
#include "raii_pointer.h"
#include <thread>

void createWindow(){
  raii_pointer<Window> g_win;
  g_win.alloc();
  if (!g_win.get()->init(800, 600)){
    printf("Error to init window.\n");
  }

  while (g_win.get()->processEvents()){
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
    g_win.get()->swap();
  }

}
int main(){
  

  std::thread t1(createWindow);
  t1.join();

  getchar();
  
  return 0;
}