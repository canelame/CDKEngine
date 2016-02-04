/** window2.h
*  @author Alejandro Canela 2015
*  Class Window
*/
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "types.h"
#include "input.h"
class Window{
public:
   struct _Window;
   
   Window();
   /**
   @brief init window
   @param width Width of the screen
   @param height Height of the screen
   */
	bool init(unsigned int width, unsigned int height);
	bool processEvents();
	void swap();
	void finish();
	void clearScreen(vec3 color);
  ///Main to rewrite by the user
  static int main(int argc, char **argv);
  ~Window(){};
private:
  _Window * window_s_;

};