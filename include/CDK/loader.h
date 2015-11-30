#ifndef __H_LOADER__
#define __H_LOADER__
#include "CDK\buffer.h"
class Loader{
  
  float readFloat(FILE *file);
  int readInt(FILE *file);
  void readData(std::vector<float>&v_l, int count, FILE *file);
  void readData(std::vector<unsigned int>&v_l, int count, FILE *file);
  void Loader::readData(std::vector<float> &v_d, int count, FILE*file){

    std::unique_ptr<char*>data = std::make_unique<char*>(new char[sizeof(float)*count]);

    fread(*data, sizeof(float)*count, 1, file);
    float *float_data = (float*)*data;
    for (int i = 0; i < count; i++){
      float v = *float_data;
      float_data++;
      v_d.push_back(v);
    }


  }
  void Loader::readData(std::vector<unsigned int> &v_d, int count, FILE*file){

    std::unique_ptr<char*>data = std::make_unique<char*>(new char[sizeof(float)*count]);
    fread(*data, sizeof(unsigned int)*count, 1, file);
    unsigned int *int_data = (unsigned int*)*data;
    for (int i = 0; i < count; i++){
      int v = *int_data;
      int_data++;
      v_d.push_back(v);
    }

  }

  float Loader::readFloat(FILE *file){
    float temp = 0;
    fread((void*)&temp, sizeof(float), 1, file);
    return temp;
  }
  int Loader::readInt(FILE *file){
    int temp = 0;
    fread((void*)&temp, sizeof(const int), 1, file);
    return temp;
  }
public:
  std::vector<Buffer> Loader::loadCDK(const char*file_in){
    std::vector<Buffer> list_buffer;
    FILE *file = fopen(file_in, "rb");

    std::vector<float> v_V;
    std::vector<float> v_N;
    std::vector<float> v_UV;
    std::vector<unsigned int> v_I;
    std::vector<float> v_Tan;
    std::vector<float> v_Bitan;
    int num_meshes = 0;

    if (file != NULL){
      num_meshes = readInt(file);

      for (int m = 0; m < num_meshes; m++){
        int i_num_p = readInt(file);

        readData(v_V, i_num_p * 3, file);
        int num_t_n = readInt(file);
        readData(v_N, num_t_n * 3, file);
        int num_t_uv = readInt(file);
        readData(v_UV, num_t_uv * 2, file);
        int num_t_t = readInt(file);
        readData(v_Tan, num_t_t * 3, file);
        int num_t_bt = readInt(file);
        readData(v_Bitan, num_t_bt * 3, file);
        int num_i_i = readInt(file);
        // int num_i_p_face = readInt(file);
        readData(v_I, num_i_i, file);


           list_buffer.push_back( Buffer(v_V,v_N,v_UV,v_I));

      }
      fclose(file);
    }
    else{

      printf("Eror to open file .CDK\n");
    }

    return list_buffer;
  }
};



#endif