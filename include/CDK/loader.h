#ifndef __H_LOADER__
#define __H_LOADER__
#include "CDK\buffer.h"
#include "drawable.h"

class TaskManager;
class Loader{
  friend class Texture;
  struct MeshData;
   struct TextureMesh;
  float* readData( int count, FILE *file);
  unsigned int* readData(FILE *file, int count);
  float readFloat(FILE *file);
  int readInt(FILE *file);

public:

  std::shared_ptr<Drawable> Loader::loadCDK(const char*file_in,std::shared_ptr<TaskManager> tk);
  std::shared_ptr<Texture> loadTexture(const char* file_name, char *type, std::shared_ptr<TaskManager> tk);
 };



#endif