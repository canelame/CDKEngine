/** window2.h
*  @author Alejandro Canela 2015
*  Class Window
*/
#include "GL\glew.h"
#include "GLFW\glfw3.h"

class Window {
public:
   struct _Window;

	Window();
	bool init(unsigned int width, unsigned int height);
	bool processEvents();
	void swap();
	void finish();

private:
  _Window * window_s_;
	int width_ = 800;
	int height_ = 600;
};