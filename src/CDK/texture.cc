#include "CDK/texture.h"
#include "CDK/task_manager.h"

struct Texture::Data{
	bool is_loaded;
	unsigned int texture_id_;
  unsigned char* image_;  
  int w, h;
  int comp;
  kTextureFiltering mag_filter;
  kTextureFiltering min_filter;
  kTextureWrapping s_wrapping;
  kTextureWrapping t_wrapping;
  kTextureFormat format;
  kTexturePixelType pixel_type;
  char path[100];
  char type[30];
};


Texture::Texture(){ 
	data_ = new Data;
	data_->is_loaded = false;
  data_->mag_filter = kTextureFiltering::kTextureFiltering_Linear;
  data_->min_filter = kTextureFiltering::kTextureFiltering_Linear;
  data_->s_wrapping = kTextureWrapping::kTextureWrapping_Repeat;
  data_->t_wrapping = kTextureWrapping::kTextureWrapping_Repeat;
};

void Texture::loadTexture(const char*file,const char type[30]){

    memcpy(&data_->path[0], &file[0], strlen(file)); data_->path[strlen(file)] = '\0';
    memcpy(&data_->type[0], &type[0], strlen(type)); data_->type[strlen(type)] = '\0';

    if (file == ""){
      data_->image_ = NULL;
    }
    else{
      data_->image_ = stbi_load(file, &data_->w, &data_->h, &data_->comp, STBI_rgb_alpha);
    }
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
bool Texture::getLoaded(){
  return data_->is_loaded; 
}

int Texture::getWidth(){
  return data_->w;
}
int Texture::getHeigth(){
  return data_->h;
}
unsigned int Texture::getID(){
	return data_->texture_id_;
}

void Texture::setID(unsigned int id){
	data_->texture_id_ = id;
}
 Texture::Texture(const Texture&t){
  *this = t;
}
char* Texture::getPath(){ 
  return data_->path; 
}

char* Texture::getType(){
  return data_->type; 
}

void Texture::setMagFilter(Texture::kTextureFiltering filter){
  data_->mag_filter = filter;
}
void Texture::setMinFilter(Texture::kTextureFiltering filter){
  data_->min_filter = filter;
}
void Texture::setWrapCoordinateS(Texture::kTextureWrapping wrap){
  data_->s_wrapping = wrap;
}
void Texture::setWrapCoordinateT(Texture::kTextureWrapping wrap){
  data_->t_wrapping = wrap;
}

Texture::kTextureFiltering Texture::getMagFilter(){
  return data_->mag_filter;
}
Texture::kTextureFiltering Texture::getMinFilter(){
  return data_->min_filter;
}
Texture::kTextureWrapping Texture::getWrapCoordinateS(){
  return data_->s_wrapping;
}
Texture::kTextureWrapping Texture::getWrapCoordinateT(){
 return data_->t_wrapping;
}

Texture::kTextureFormat Texture::getFormat(){
  return data_->format;
}

void Texture::setFormat(Texture::kTextureFormat format){
  data_->format = format;
}

Texture::kTexturePixelType Texture::getPixelType(){
  return data_->pixel_type;
}

void Texture::setPixelType(Texture::kTexturePixelType format){
  data_->pixel_type = format;
}

