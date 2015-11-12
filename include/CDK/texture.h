#ifndef __H_TEXTURE__
#define __H_TEXTURE_
#include "command.h"
#include "opengl_interfaz.h"
class Texture : public Command{
public:
	struct Data;
  Texture();
  ~Texture(){};
  void loadTexture(const char *file);
  void runCommand(OpenGlInterFaz &dl)const{};
  void setLoaded(bool value);
  bool getLoaded();
  unsigned char* getData();
  int getWidth();
  int getHeigth();
private:
	Data *data_;

};


#endif