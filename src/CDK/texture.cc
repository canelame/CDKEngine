#include "CDK/texture.h"


struct Texture::Data{
	bool is_loaded;
	unsigned int texture_id_;
  unsigned char* image_;  
  int w, h;
  int comp;
  char path[100];
  char type[30];
};
enum Texture::kTextureFiltering{
  kTextureFiltering_Linear =0,
  kTextureFiltering_Nearest

};
enum Texture::kTextureWrapping{
  kTextureWrapping_Repeat=0,
  kTextureWrapping_Mirror_Repeat,
  kTextureWrapping_Clamp_Edge,
  kTextureWrapping_Clamp_Border

};

Texture::Texture(){ 
	data_ = new Data;
	data_->is_loaded = false;
};
void Te
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