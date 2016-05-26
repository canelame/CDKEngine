/** window2.h
*  @author Alejandro Canela 2015
*  Class Window
*/

#include "CDK/Core/types.h"
#include "CDK/Core/input.h"
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
  /**
  @brief This function return the time elapsed since window was initialized.
  @return Return time in seconds
  */
  double time();
  ///Main to rewrite by the user
  static int main(int argc, char **argv);
  ~Window(){};
private:

  _Window * window_s_;

};