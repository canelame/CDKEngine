#include "terrain.h"
#include "../terrain_mat.h"

Terrain::Terrain(){
  terrain_mesh_ = std::make_shared<Geometry>();
  terrain_material_ = std::make_shared <TerrainMaterial >();
  

}
Terrain::~Terrain(){

}
int Terrain::getHeight(){
  return height_map_height_;
}

int Terrain::getWidth(){
  return height_map_width_;
}



void Terrain::setPosition(vec3 &data){
  Node::setPosition(data);
  terrain_material_->setUniformMat4Value("u_mat_model", &modelMat());
}
void Terrain::setPosition(const float* data){
  Node::setPosition(data);
  terrain_material_->setUniformMat4Value("u_mat_model",&modelMat());
}


void Terrain::setRotation(vec3 &data){
  Node::setPosition(data);
  terrain_material_->setUniformMat4Value("u_mat_model", &modelMat());
}
void Terrain::setRotation(const float* data){
  Node::setPosition(data);
  terrain_material_->setUniformMat4Value("u_mat_model", &modelMat());
}



void Terrain::setScale(const float* data){
  Node::setPosition(data);
  terrain_material_->setUniformMat4Value("u_mat_model", &modelMat());
}
void Terrain::setScale(vec3 &data){
  Node::setPosition(data);
  terrain_material_->setUniformMat4Value("u_mat_model", &modelMat());
}


void Terrain::loadHeightMapTexture(const char* file_name){
  height_map_ = std::make_shared<Texture>();
  height_map_->loadTexture(file_name, "diffuse");
  
  height_map_width_ = height_map_->getWidth();
  height_map_height_ = height_map_->getHeigth();
  inc_ptr = height_map_->getBpp();
  row_step_ = inc_ptr * (height_map_width_);
}

void Terrain::create(){
  //w * h = n_pixels
  // pixels *=3; // 3 positions
  //pixels *=3 + lo anterior
  //pixels *=2 + todo lo anterior
  std::vector<float> terrain_position;
  std::vector<float> terrain_normal;
  std::vector<float> terrain_uvs;


  float textureU = float(height_map_width_) * 0.1f;
  float textureV = float(height_map_height_) * 0.1f;
  float terrainWidth = (height_map_width_ - 1) ;
 float terrainHeight = (height_map_height_ - 1) ;

  float halfTerrainWidth = terrainWidth * 0.5f;
  float halfTerrainHeight = terrainHeight * 0.5f;

  unsigned char *data = height_map_->getData();
  
  for (int y = 0; y < height_map_width_; y++){
    for (int x = 0; x < height_map_height_; x++){
      
      float s = float(x) / float(height_map_width_ - 1);
      float t = float(y) / float(height_map_height_ - 1);

      float new_heigth = (float)(data[ (row_step_*y+x)+(x*inc_ptr)])/255.0f;
      
      terrain_position.push_back( (-0.5f+s));
      terrain_position.push_back((new_heigth));
      terrain_position.push_back((-0.5+t));
      //Uvs
      terrain_uvs.push_back( s+(height_map_width_*0.1));
      terrain_uvs.push_back( t+(height_map_height_*0.1));
    }
  }
  //Normals.
  /**
  Each quad of the grid have to triangles, so we need 2 groups of normals
  .One for the first triangle and other one to the second
  */
  std::vector< std::vector< vec3>> v_normals[2];//" triangles
  for (int i = 0; i < 2; i++){
    v_normals[i] = std::vector< std::vector<vec3>>(height_map_height_ ,
      std::vector<vec3>(height_map_width_ ));
  }
  //Compute triangles
  for (int y = 0; y < height_map_height_; y++){
    for (int x = 0; x < height_map_width_; x++){
      //triangle 0
        //Vertex 1
      int vertex_x_0_1 = (3 * (x + (y * height_map_width_)));
      int vertex_y_0_1 = vertex_x_0_1 + 1;
      int vertex_z_0_1 = vertex_x_0_1 + 2;
        //Vertex 2
      int vertex_x_0_2 = (3 * (x + ((y + 1) * height_map_width_))) ;
      int vertex_y_0_2 = vertex_x_0_2 + 1;
      int vertex_z_0_2 = vertex_x_0_2 + 2;
        //Vertex 3
      int vertex_x_0_3 = (3 * ((x + 1) + ((y + 1) * height_map_width_)));
      int vertex_y_0_3 = vertex_x_0_3 + 1;
      int vertex_z_0_3 = vertex_x_0_3 + 2;

      vec3 triangle_0[3] = {  vec3(vertex_x_0_1, vertex_y_0_1, vertex_z_0_1),
                              vec3(vertex_x_0_2, vertex_y_0_2, vertex_z_0_2),
                              vec3(vertex_x_0_3, vertex_y_0_3, vertex_z_0_3) };
        
      //triangle  1
      int vertex_x_1_1 = (3 * ((x + 1) + ((y + 1) * height_map_width_)));
      int vertex_y_1_1 = vertex_x_1_1 +1;
      int vertex_z_1_1 = vertex_x_1_1 + 2;
        //Vertex 2
      int vertex_x_1_2 = (3 * ((x + 1) + (y * height_map_width_)));
      int vertex_y_1_2 = vertex_x_1_2 + 1;
      int vertex_z_1_2 = vertex_x_1_2 + 2;
        //Vertex 
      int vertex_x_1_3 = (3 * (x + (y * height_map_width_)));
      int vertex_y_1_3 = vertex_x_1_3 + 1;
      int vertex_z_1_3 = vertex_x_1_3 + 2;
      //Vertex 3
      vec3 triangle_1[3] = {  vec3(vertex_x_1_1, vertex_y_1_1, vertex_z_1_1),
                              vec3(vertex_x_1_2, vertex_y_1_2, vertex_z_1_2),
                              vec3(vertex_x_1_3, vertex_y_1_3, vertex_z_1_3) };

      //Triangle_normals
      vec3 triangle_normal_0 = glm::cross(triangle_0[0] - triangle_0[1], 
                                          triangle_0[1] - triangle_0[2]);

      vec3 triangle_normal_1 = glm::cross(triangle_1[0] - triangle_1[1],
                                           triangle_1[1] - triangle_1[2]);

      v_normals[0][y][x] = glm::normalize(triangle_normal_0);
      v_normals[1][y][x] = glm::normalize(triangle_normal_1);


    }
  }

  //We finally can compute noramls
  std::vector<std::vector<vec3>> final_normals = std::vector<std::vector<vec3>>(
                        height_map_height_, std::vector<vec3>(height_map_width_));

  for (int y = 0; y < height_map_height_; y++){
    for (int x = 0; x < height_map_width_; x++){
      vec3 final_normal = vec3(0.0);
      //Check up-left triangle
      if (x != 0 && y != 0){
        for (int k = 0; k < 2; k++){
          final_normal += v_normals[k][y - 1][x - 1];
        }
      }
      //Check for up-right tringle
      if (y != 0 && x != height_map_width_ - 1){
        final_normal += v_normals[0][y - 1][x];
      }
      //Checl for bottom-right triangle
      if (y != height_map_height_ - 1 && x != height_map_width_ -1){
        for (int k = 0; k < 2; ++k){
          final_normal += v_normals[k][y][x];
        }
      }
      //Check for bottom-left triangles
      if (y != height_map_height_ - 1 && x != 0){
        final_normal += v_normals[1][y][x - 1];
      }
      final_normal = glm::normalize(final_normal);
      
     // terrain_normal.push_back(final_normal.x);
      //terrain_normal.push_back( final_normal.y);
      //terrain_normal.push_back( final_normal.z);

    }
  }
  
  const unsigned int terrain_width = height_map_width_;
  const unsigned int terrain_height = height_map_height_;

  //2 triangles per quad, each pixel represents a triangle
  const unsigned int num_triangles = (terrain_width - 1) * (terrain_height - 1);
  std::vector<unsigned int> indices;
  //Each triangle have 3 vertex
  indices.resize(num_triangles * 6);
  int index = 0;
  for (int x = 0; x < (terrain_width -1); x++){
    for (int z = 0; z < (terrain_height - 1); z++){
      int a = (x * terrain_width) + z;
      int b = ((x + 1) * terrain_width) + z;
      int c = (x * terrain_width) + (z + 1);
      int d = ((x + 1) * terrain_width) + (z + 1);

      indices[index++] = a;
      indices[index++] = b;
      indices[index++] = c;

      indices[index++] = b;
      indices[index++] = d;
      indices[index++] = c;




    }
  }

  terrain_mesh_->getBuffer()->setAttributeSize(terrain_position.size(),
    terrain_normal.size(),
    terrain_uvs.size() , 0, 0,
    indices.size());
  terrain_mesh_->loadData(terrain_position, terrain_normal, terrain_uvs,indices);


  setGeometry(terrain_mesh_);
  setMaterial(terrain_material_);
}

float Terrain::getMapHeight(unsigned char*data , int num_bytes){

  switch (num_bytes)
  {
  case 1:
  {
    return (unsigned char)(data[0]) / (float)0xff;
  }
  break;
  case 2:
  {
    return (unsigned short)(data[1] << 8 | data[0]) / (float)0xffff;
  }
  break;
  case 3:
  {
    return (unsigned short)(data[2] << 12 | data[1] << 8) / (float)0xffffff;
  }
  break;
  case 4:
  {
    return (unsigned int)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]) / (float)0xffffffff;
  }
  break;
  default:
  {
    
  }
  break;
  }

  return 0.0f;

}