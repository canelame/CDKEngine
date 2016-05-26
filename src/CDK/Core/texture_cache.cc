#include "CDK/Core/texture_cache.h"
#include "CDK/Resources/texture.h"

TextureCache* TextureCache::instance_ = NULL;




TextureCache& TextureCache::instance(){
  if (instance_ == NULL)instance_ = new TextureCache();
  return  *instance_;
}

void TextureCache::addTexture(std::shared_ptr<Texture>texture){
  textures_.insert(std::make_pair(texture->getPath(), texture));
}

std::shared_ptr<Texture>TextureCache::getTexture(const char* name){
  
  if (textures_.count(name) > 0){
    return textures_.at(name);
  }  
  return nullptr;
}

bool TextureCache::textureExists(const char *name){

  for (std::map<std::string, std::shared_ptr<Texture>>::iterator it = textures_.begin(); it != textures_.end(); it++){
    if (it->first == name){
      return true;
    }
  }

  return false;
}