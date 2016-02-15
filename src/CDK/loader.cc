#include "CDK/loader.h"
#include "CDK/buffer.h"
 #include "CDK/task_manager.h"
#include "CDK/texture_cache.h"
struct Loader::MeshData{
  int num_positions;
  int num_normals;
  int num_uvs;
  int num_tangents;
  int num_bitangents;
  int num_indices;
  //Data
  int num_diffuse_textures;
  int num_specular_textures;
  MeshData(int n_p, int n_n, int n_uv, int n_t, int n_bt, int n_i, int n_texture, int n_diffuse_texture, int n_specular_texture){
    num_positions = n_p;
    num_normals = n_n;
    num_uvs = n_uv;
    num_tangents = n_t;
    num_bitangents = n_bt;
    num_indices = n_i;
    num_diffuse_textures = n_diffuse_texture;
    num_specular_textures = n_specular_texture;
  }
  MeshData(){}
};


struct Loader::TextureMesh{
  int id;
  char path[100];
  char type[30];
};
float* Loader::readData( int count, FILE*file){

  std::unique_ptr<char*>data = std::make_unique<char*>(new char[sizeof(float)*count]);

  fread(*data, sizeof(float)*count, 1, file);
  float *float_data = (float*)*data;

  return float_data;

}
unsigned int* Loader::readData(FILE*file, int count){

  std::unique_ptr<char*>data = std::make_unique<char*>(new char[sizeof(float)*count]);
  fread(*data, sizeof(unsigned int)*count, 1, file);
  unsigned int *int_data = (unsigned int*)*data;
  return int_data;
}




std::shared_ptr<Drawable> Loader::loadCDK(const char*file_in){
  
  FILE *file = fopen(file_in, "rb");
  std::shared_ptr<Drawable> node_geo = std::make_shared<Drawable>();
  std::shared_ptr<Geometry> geo_child;

  int num_meshes = 0;

 if (file != NULL){

   std::shared_ptr<Material> mat_child;
   std::shared_ptr<Material::MaterialSettings> mat_settings;
   fread((void*)&num_meshes, sizeof(const int), 1, file);
   MeshData m;

   for (int mn = 0; mn < num_meshes; mn++){

     fread(&m, sizeof(MeshData), 1, file);
     const int position_offset = m.num_positions*sizeof(float);
     const int normal_offset = m.num_normals*sizeof(float);
     const int uv_offset = m.num_uvs*sizeof(float);
     const int tangent_offset = m.num_tangents*sizeof(float);
     const int bitanget_offset = m.num_bitangents*sizeof(float);
     const int indices_size = m.num_indices*sizeof(unsigned int);
     const int diffuse_texture_size = m.num_diffuse_textures*sizeof(TextureMesh);
     const int specular_texture_size = m.num_specular_textures*sizeof(TextureMesh);
     const int total_size_r = position_offset + normal_offset + uv_offset + tangent_offset +
       bitanget_offset + indices_size;
     const int texture_total_size =diffuse_texture_size + specular_texture_size;
     std::unique_ptr<char[]> d = std::unique_ptr<char[]>(new char[total_size_r]);
     std::unique_ptr<char[]> d_texture = std::unique_ptr<char[]>(new char[texture_total_size]);
     
     fread(d.get(), total_size_r, 1, file);
     fread(d_texture.get(), texture_total_size, 1, file);
    
     std::shared_ptr<Drawable> child = std::make_shared<Drawable>();


    if (m.num_diffuse_textures == 0 && m.num_specular_textures == 0){
      mat_child = std::make_shared<Material>(Material::TYPE::ONNLY_DIFFUSE_);
    }
    else{

      mat_child = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE);
    }
   
    mat_settings = std::make_shared<Material::MaterialSettings>();
     for (int i = 0; i<m.num_diffuse_textures ; i++){
       TextureMesh t_t;
       memcpy(&t_t, &d_texture.get()[(i*sizeof(TextureMesh))], sizeof(TextureMesh));

       char tpath[50] = "textures/";
       strcat(tpath, t_t.path);
       printf("Loading diffuse texture: %s\n",t_t.path );
       bool skip = false;
       
       //Search if the texture is already loaded
       for (int j = 0; j < mat_settings->totalTextures(); j++){
        
         if (strcmp(mat_settings->getTextureAt(j).c_str(), tpath) == 0){
           mat_settings->addTexture(mat_settings->getTextureAt(j).c_str());
           skip = true;
           break;
         }
       }
       if (!skip){
     
         if (TextureCache::instance().textureExists(tpath) == false){
           std::shared_ptr<Texture> txt1 = std::make_shared<Texture>();
           std::shared_ptr<ReadTexture> nt = std::make_shared<ReadTexture>(txt1, tpath, "diffuse");
           TaskManager::instance().addTask(nt);
           TaskManager::instance().waitTask(*nt.get());
           TextureCache::instance().addTexture(txt1);
           mat_settings->addTexture(tpath);

         }

       }
       
     }

     for (int i = 0; i<m.num_specular_textures; i++){

       TextureMesh t_t;
       memcpy(&t_t, &d_texture.get()[ diffuse_texture_size+(i*sizeof(TextureMesh))], sizeof(TextureMesh));
       char tpath[50] = "textures/";
       strcat(tpath, t_t.path);
       printf("Loading specular texture: %s\n", t_t.path);
       std::shared_ptr<Texture> txt1 = std::make_shared<Texture>();
      // tk->addTask(std::make_shared < ReadTexture>(txt1, tpath, "diffuse"));
       mat_settings->addTexture(tpath);
       bool skip = false;
       //Search if the texture is alreadyy loaded
       for (int j = 0; j < mat_settings->totalTextures(); j++){

         if (strcmp(mat_settings->getTextureAt(j).c_str(), tpath) == 0){
           mat_settings->addTexture(mat_settings->getTextureAt(j).c_str());
           skip = true;
           break;
         }
       }
       if (!skip){

         std::shared_ptr<ReadTexture> nt = std::make_shared<ReadTexture>(txt1, tpath, "specular");
         if (!TextureCache::instance().textureExists(tpath))
		 TaskManager::instance().addTask(nt);
		 TaskManager::instance().waitTask(*nt.get());
     TextureCache::instance().addTexture(txt1);
         mat_settings->addTexture(tpath);
       }

     }
     geo_child = std::make_shared<Geometry>();
     geo_child->getBuffer()->setAttributeSize(m.num_positions, m.num_normals, m.num_uvs, m.num_tangents, m.num_bitangents, m.num_indices);
     geo_child->getBuffer()->loadData(std::move(d));
     if (num_meshes > 1 ){
       std::shared_ptr<Drawable> child = std::make_shared<Drawable>();
       child->setGeometry(geo_child);
       mat_child->setMaterialSettings(mat_settings);
       child->setMaterial(mat_child);
       node_geo->addChild(child);
     }
     else if(num_meshes==1 ){
       std::shared_ptr<Drawable> child = std::make_shared<Drawable>();
       node_geo->setGeometry(geo_child);
       mat_child->setMaterialSettings(mat_settings);
       node_geo->setMaterial(mat_child);
     }

   
   }
    fclose(file);
    printf("File loaded.\n");
  }
  else{

    printf("Eror to open file .CDK\n");
    return NULL;
  }
  return node_geo;
  printf("");
}
void Material::setMaterialSettings(std::shared_ptr<Material::MaterialSettings> mat_s){
  mat_settings_ = mat_s;
}
std::shared_ptr<Texture> Loader::loadTexture(const char* file_name,char *type, std::shared_ptr<TaskManager>tk){
  int x, y;
    char *data;
  std::shared_ptr<Texture> t = std::make_shared<Texture>();
  tk->addTask(std::make_unique<ReadTexture>(t,file_name,type));
  return t;
}

