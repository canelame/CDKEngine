#include "CDK/loader.h"
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

std::shared_ptr<Drawable> Loader::loadCDK(const char*file_in,std::shared_ptr<TaskManager> tk){
  std::vector<Buffer> list_buffer;
  FILE *file = fopen(file_in, "rb");
  std::shared_ptr<Drawable> node_geo = std::make_shared<Drawable>();
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
      std::shared_ptr<Drawable> child = std::make_shared<Drawable>();
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
      std::shared_ptr<Geometry> geo_child = std::make_shared<Geometry>();

      std::shared_ptr<Material> mat_child;
      mat_child = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE, tk);
      std::shared_ptr<Texture> txt1 = std::make_shared<Texture>();
      txt1->loadTexture("textures/cat.tga");
      mat_child->setTexture(txt1);
      geo_child->loadAttributes(v_V, v_N, v_UV, v_I);
      if (num_meshes != 1){
        node_geo->setGeometry(geo_child);
        node_geo->setMaterial(mat_child);
      }
      else{

        child->setGeometry(std::make_shared<Geometry>(*geo_child.get()));
        child->setMaterial(mat_child);
        node_geo->addChild(child);
      }

  


    }
    fclose(file);
  }
  else{

    printf("Eror to open file .CDK\n");
  }

  return node_geo;
}