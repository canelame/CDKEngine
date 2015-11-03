#include "CDK/texture.h"

struct Texture::Data{
	bool is_loaded;
	OpenGlInterFaz *interfaz_;

};
Texture::Texture(){ 
	data_ = new Data;
	data_->is_loaded = false;
};
void Texture::loadTexture(const char*file){
  data_->interfaz_->loadTexture(file);

}
void Texture::setLoaded(bool value){
  data_->is_loaded = value;
}
bool Texture::getLoaded(){ return data_->is_loaded; }
