#ifndef __H_LOADER__
#define __H_LOADER__
#include "CDK\buffer.h"
#include "drawable.h"
#include "task_manager.h"
class Loader{

  void readData(std::vector<float>&v_l, int count, FILE *file);
  void readData(std::vector<unsigned int>&v_l, int count, FILE *file);
  float readFloat(FILE *file);
  int readInt(FILE *file);
public:
  std::shared_ptr<Drawable> Loader::loadCDK(const char*file_in,std::shared_ptr<TaskManager> tk);
 };



#endif