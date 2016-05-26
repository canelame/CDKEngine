#ifndef __H_INPUT__
#define __H_INPUT__
#include <memory>

class Input{
  static std::unique_ptr<Input>instance_;
  static bool g_keys[1024];
  static float mouseX_;
  static float mouseY_;
public:
  static bool pressKeyW();
  static bool pressKeyS();
  static bool pressKeyA();
  static bool pressKeyD();
  static bool pressSpace();
  static float getMouseX();
  static float getMouseY();
  static  void setInputPress(int key);
  static void setInputRealease(int key);
  static void setMouseXY(float x,float y);
  static void setMouseY(float y);
  static Input& instance();
  static bool pressL();
protected:

 friend class Window;
};



#endif