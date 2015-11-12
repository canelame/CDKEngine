#include "CDK/texture.h"
#define STB_IMAGE_IMPLEMENTATION    
#include "external/stb_image.h"

struct Texture::Data{
	bool is_loaded;
	OpenGlInterFaz *interfaz_;
  unsigned char* image_;  
  int w, h;
};
Texture::Texture(){ 
	data_ = new Data;
	data_->is_loaded = false;
};
void Texture::loadTexture(const char*file){
  //  data_->interfaz_->loadTexture(file);

  int x, y;

  int comp;
  data_->image_ = stbi_load(file, &data_->w, &data_->h, &comp, 0);
  if (data_->image_ == nullptr){
    printf("Failed to load texture\n ");

  }
}
  unsigned char* Texture::getData(){
    return data_->image_;
  }
void Texture::setLoaded(bool value){
  data_->is_loaded = value;
}
bool Texture::getLoaded(){ return data_->is_loaded; }

int Texture::getWidth(){
  return data_->w;
}
int Texture::getHeigth(){
  return data_->h;
}