#include "texture.h"


void Texture::loadTexture(const char*file){
  interfaz_->loadTexture(file);

}
void Texture::setLoaded(bool value){
  is_loaded = value;
}
bool Texture::getLoaded(){ return is_loaded; }
