/** window2.h
*  @author Alejandro Canela 2015
*  Class Window
*/
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "raii_pointer.h"
class Window {
public:
   struct _Window;
   _Window * window_s_;
	Window();
	bool init(unsigned int width, unsigned int height);
	bool processEvents();
	void swap();
	void finish();

private:

	int width_ = 800;
	int height_ = 600;
};