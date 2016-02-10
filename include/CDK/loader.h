#ifndef __H_LOADER__
#define __H_LOADER__
#include "CDK\buffer.h"
#include "drawable.h"
/**
@author Alejandro Canela Mendez
2016 ESAT
TaskManager class
*/
class TaskManager;
class Loader{
  friend class Texture;
  struct MeshData;
  struct TextureMesh;
  /**
  @brief Read float data from cdk file
  @param count Number of floats to read.
  @param file Current file from read data
  @return Pointer to data
  */
  float* readData( int count, FILE *file);
  /**
  @brief Read unsigned int data from cdk file
  @param file Current file
  @param count Num of int to read 
  */
  unsigned int* readData(FILE *file, int count);


public:
  /**
  @brief Read cdk file and return a drawable whit all geometrys and materials loaded.
  @param file_in Name of .cdk file
  @return Drawable whit asset loaded.
  */
  std::shared_ptr<Drawable> Loader::loadCDK(const char*file_in);
  /**
  @brief Reads a texture into Texture object
  @param file_name Texture name.
  @param type Type of texture //Can be: TEXTURE or ONLY_DIFFUSE
  */
  std::shared_ptr<Texture> loadTexture(const char* file_name, char *type, std::shared_ptr<TaskManager> tk);
 };



#endif