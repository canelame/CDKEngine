#include "CDK/Material/material.h"
#include "CDK/Resources/texture.h"
class TextureMaterial : public Material{

public:

  TextureMaterial();

  class MaterialSettings : public Material::MaterialSettings{

  protected:
    std::vector<std::string > texture_;
  public:

   
    /**
    @Brief Return the texture placed at i
    @return Texture of material on index i
    */
    const char* getTextureAt(int i);
    /**
    @brief Get total textures of the material
    @return Total num texutures
    */
    int totalTextures();
    /**
    @brief add a texture to material
    @param txt new texture
    @param tk The current taskManager
    */
    void addTexture(const char*name);
    std::vector<std::string> getTextures();
  };
  friend class Material;
};
