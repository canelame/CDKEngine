#ifndef __H_TEXTURE__
#define __H_TEXTURE_
#include "command.h"
#include <memory>
#include "external/stb_image.h"
/**
@author Alejandor Canela Mendez
ESAT 2016
*/
class Texture{
public:
  enum kTextureFiltering{
    kTextureFiltering_Linear = 0,
    kTextureFiltering_Nearest

  };
  enum kTextureWrapping{
    kTextureWrapping_Repeat = 0,
    kTextureWrapping_Mirror_Repeat,
    kTextureWrapping_Clamp_Edge,
    kTextureWrapping_Clamp_Border

  };
  Texture();
  //~Texture(){};
  Texture(const Texture&t);
  /**
  @brief Load texture data
  @param file Texture name
  @param type of texture, can be: specular or diffuse or fb(FrameBuffer)
  */
  void loadTexture(const char *file,const char type[30]);
  /**
  @brief Set loaded if the texture has been loaded to  GPU
  @param value True if its have been loaded
  */
  void setLoaded(bool value);
  /**
  @brief Get if the texture has been loaded.
  @return True or false, if the texture is loaded.
  */
  bool getLoaded();
  /**
  @brief Get texture data of the image.
  @return pointer to data
  */
  unsigned char* getData();
  /**
  @brief Get witdth of the texture
  @return texture width
  */
  int getWidth();
  /**
  @breif Get texture height
  @return texture height
  */
  int getHeigth();
  /**
  @brief Get texure id give by glGenTextures
  @return Texture id.
  */
	unsigned int getID();
  /**
  @brief Set id texture on GPU.
  @param value 
  */
	void setID(unsigned int value);
  /**
  @brief Get Texture path
  @return A char string whit path
  */
  char* getPath();
  /**
  @brief Get texture type
  @return A char string whit type
  */
  char* getType();

  /**
  */
  void setMagFilter(kTextureFiltering filter);
  /**
  */
  void setMinFilter(kTextureFiltering filter);
  /**
  */
  void setWrapCoordinateS(kTextureWrapping wrap);
  /**
  */
  void setWrapCoordinateT(kTextureWrapping wrap);
  /**
  */
  kTextureFiltering getMagFilter( );
  /**
  */
  kTextureFiltering getMinFilter( );
  /**
  */
  kTextureWrapping getWrapCoordinateS( );
  /**
  */
  kTextureWrapping getWrapCoordinateT( );
private:
  struct Data;
	Data *data_;

};


#endif