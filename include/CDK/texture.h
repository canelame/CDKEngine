#ifndef __H_TEXTURE__
#define __H_TEXTURE_
#include "command.h"
#include <memory>
#include "external/stb_image.h"

class Texture : public Command{
public:
	struct Data;
  Texture();
  //~Texture(){};
  Texture(const Texture&t);
  void loadTexture(const char *file,const char type[30]);
  void runCommand(OpenGlInterFaz &dl)const{};
  void setLoaded(bool value);
  bool getLoaded();
  unsigned char* getData();
  int getWidth();
  int getHeigth();
	unsigned int getTexturePosition();
	unsigned int getID();
	void setID(unsigned int value);
  char* getPath();
  char* getType();
private:
	Data *data_;

};


#endif