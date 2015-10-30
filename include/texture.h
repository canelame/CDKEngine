#ifndef __H_TEXTURE__
#define __H_TEXTURE_
#include "command.h"
#include "opengl_interfaz.h"
class Texture : public Command{
public:
  Texture(){ is_loaded = false; };
  ~Texture(){};
  void loadTexture(const char *file);
  void runCommand(OpenGlInterFaz &dl)const{};
  void setLoaded(bool value);
  bool getLoaded();
private:
  bool is_loaded;
  OpenGlInterFaz *interfaz_;
};


#endif