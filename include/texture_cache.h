#include <map>
#include <memory>
#include <string>
class Texture;
class TextureCache{
  static TextureCache *instance_;
  std::map<std::string, std::shared_ptr<Texture>> textures_;
 TextureCache(){};
public:
  void init();
  static TextureCache& instance();
  void addTexture(std::shared_ptr<Texture>);
  std::shared_ptr<Texture> getTexture(const char* texture_name);
  bool textureExists(const char* name);
};