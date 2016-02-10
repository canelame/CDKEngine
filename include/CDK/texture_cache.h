#include <map>
#include <memory>
#include <string>
class Texture;
/**
@author Alejandro Canela Mendez ESAT 2016.
@brief Singlenton cache to manage textures in the engine
*/
class TextureCache{
  static TextureCache *instance_;
  std::map<std::string, std::shared_ptr<Texture>> textures_;
 TextureCache(){};
public:

  static TextureCache& instance();
  /**
   @brief Add texture to cache
   @param texture New texture
  */
  void addTexture(std::shared_ptr<Texture>texture);
  /**
  @brief Get texture of the cache.
  @return Selected texture
  */

  std::shared_ptr<Texture> getTexture(const char* texture_name);
  /**
  @brief Return if the texture exists into the cache
  @return True if exists, false if not.
  */
  bool textureExists(const char* name);
};