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
     bitanget_offset + indices_size+diffuse_texture_size+specular_texture_size;
     std::unique_ptr<char[]> d = std::unique_ptr<char[]>(new char[total_size_r]);
     
     fread(d.get(), total_size_r, 1, file);

     float * p_pos = new float[position_offset];
    memcpy(p_pos, &d.get()[0], position_offset);

    float * n_pos = new float[normal_offset];
    memcpy(n_pos, &d.get()[position_offset], normal_offset);

    float * uv_pos = new float[uv_offset];
    memcpy(uv_pos, &d.get()[position_offset + normal_offset], uv_offset);

    float * t_pos = new float[tangent_offset];
    memcpy(t_pos, &d.get()[position_offset + normal_offset + uv_offset], tangent_offset);

    float * bt_pos = new float[bitanget_offset];
    memcpy(bt_pos, &d.get()[position_offset + normal_offset + uv_offset + tangent_offset], bitanget_offset);

    unsigned int *i_pos = new unsigned int[indices_size];
    memcpy(i_pos, &d.get()[position_offset + normal_offset + uv_offset + tangent_offset + bitanget_offset], indices_size);

   /* geo_child->getBuffer()->setAttributeSize(m.num_positions, m.num_normals, m.num_uvs, m.num_tangents, m.num_bitangents, m.num_indices);
    geo_child->loadAttributes((&p_pos[0]), &n_pos[0], &uv_pos[0], &i_pos[0]);*/
    std::shared_ptr<Drawable> child = std::make_shared<Drawable>();


    if (m.num_diffuse_textures == 0 && m.num_specular_textures == 0){
      mat_child = std::make_shared<Material>(Material::TYPE::ONNLY_DIFFUSE_);
    }
    else{
      mat_child = std::make_shared<Material>(Material::TYPE::DIFFUSE_TEXTURE);
    }
   
     for (int i = 0; i<m.num_diffuse_textures ; i++){
       TextureMesh t_t;
       memcpy(&t_t, &d.get()[position_offset + normal_offset + uv_offset + tangent_offset + bitanget_offset + indices_size + (i*sizeof(TextureMesh))], sizeof(TextureMesh));

       char tpath[50] = "textures/";
       strcat(tpath, t_t.path);
       printf("Loading diffuse texture: %s\n",t_t.path );
       bool skip = false;
       //Search if the texture is already loaded
       for (int j= 0; j < mat_child->totalTextures();j++){
        
         if (strcmp(mat_child->getTextureAt(j), tpath) == 0){
           mat_child->addTexture(mat_child->getTextureAt(j));
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
           mat_child->addTexture(tpath);

         }

       }
       
     }

     for (int i = 0; i<m.num_specular_textures; i++){

       TextureMesh t_t;
       memcpy(&t_t, &d.get()[position_offset + normal_offset + uv_offset + tangent_offset + bitanget_offset + indices_size + diffuse_texture_size+(i*sizeof(TextureMesh))], sizeof(TextureMesh));
       char tpath[50] = "textures/";
       strcat(tpath, t_t.path);
       printf("Loading specular texture: %s\n", t_t.path);
       std::shared_ptr<Texture> txt1 = std::make_shared<Texture>();
      // tk->addTask(std::make_shared < ReadTexture>(txt1, tpath, "diffuse"));
       mat_child->addTexture(tpath);
       bool skip = false;
       //Search if the texture is alreadyy loaded
       for (int j = 0; j < mat_child->totalTextures(); j++){

         if (strcmp(mat_child->getTextureAt(j), tpath) == 0){
           mat_child->addTexture(mat_child->getTextureAt(j));
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
         mat_child->addTexture(tpath);
       }

     }
     geo_child = std::make_shared<Geometry>();
     geo_child->getBuffer()->setAttributeSize(m.num_positions, m.num_normals, m.num_uvs, m.num_tangents, m.num_bitangents, m.num_indices);
     geo_child->loadAttributes((&p_pos[0]), &n_pos[0], &uv_pos[0], &i_pos[0]);
 
     if (num_meshes > 1 ){
       std::shared_ptr<Drawable> child = std::make_shared<Drawable>();
       child->setGeometry(geo_child);
       child->setMaterial(mat_child);
       node_geo->addChild(child);
     }
     else if(num_meshes==1 ){
       node_geo->setGeometry(geo_child);
       node_geo->setMaterial(mat_child);
     }

   
   }
    fclose(file);
  
  }
  else{

    printf("Eror to open file .CDK\n");
    return NULL;
  }
  return node_geo;
  printf("");
}

std::shared_ptr<Texture> Loader::loadTexture(const char* file_name,char *type, std::shared_ptr<TaskManager>tk){
  int x, y;
    char *data;
  std::shared_ptr<Texture> t = std::make_shared<Texture>();
  tk->addTask(std::make_unique<ReadTexture>(t,file_name,type));
  return t;
}