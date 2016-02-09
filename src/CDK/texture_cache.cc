#include "texture_cache.h"
#include "CDK/texture.h"

TextureCache* TextureCache::instance_ = NULL;


void TextureCache::init(){

}

TextureCache& TextureCache::instance(){
  if (instance_ == NULL)instance_ = new TextureCache();
  return  *instance_;
}

void TextureCache::addTexture(std::shared_ptr<Texture>texture){
  textures_.insert(std::make_pair(texture->getPath(), texture));
}

std::shared_ptr<Texture>TextureCache::getTexture(const char* name){
  
  return textures_.at(name);
}

bool TextureCache::textureExists(const char *name){

  for (std::map<std::string, std::shared_ptr<Texture>>::iterator it = textures_.begin(); it != textures_.end(); it++){
    if (it->first == name){
      return true;
    }
  }

  return false;
}