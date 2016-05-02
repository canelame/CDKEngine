#include "terrain.h"
#include "CDK\texture_material.h"

Terrain::Terrain(){
  terrain_mesh_ = std::make_shared<Geometry>();
  terrain_material_ = std::make_shared <TextureMaterial >();
  drawable_terrain_ = std::make_shared<Drawable>();
}
Terrain::~Terrain(){

}
int Terrain::getHeight(){
  return height_map_height_;
}

int Terrain::getWidth(){
  return height_map_width_;
}

void Terrain::loadHeightMapTexture(const char* file_name){
  height_map_ = std::make_shared<Texture>();
  height_map_->loadTexture(file_name, "diffuse");
  
  height_map_width_ = height_map_->getWidth();
  height_map_height_ = height_map_->getHeigth();
  inc_ptr = height_map_->getBpp();
  row_step_ = inc_ptr * height_map_width_;
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

  unsigned char *data = height_map_->getData();

  for (int y = 0; y < height_map_height_; y++){
    for (int x = 0; x < height_map_width_; x++){
      float new_x = float(x) / float(height_map_width_ - 1);
      float new_y = float(y) / float(height_map_height_ - 1);

      
      float new_height = float( *data + row_step_ * y + x*inc_ptr) / 255.0f;
      terrain_position.push_back(-0.5f + new_x);
      terrain_position.push_back(new_height);
      terrain_position.push_back(-0.5f + new_y);
      //Uvs
      terrain_uvs.push_back(textureU * new_x);
      terrain_uvs.push_back(textureV * new_y);
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
/*  std::vector<std::vector<vec3>> final_normals = std::vector<std::vector<vec3>>(
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
      
      terrain_normal.push_back(final_normal.x);
      terrain_normal.push_back( final_normal.y);
      terrain_normal.push_back( final_normal.z);

    }
  }
  */
  const unsigned int terrain_width = height_map_width_;
  const unsigned int terrain_height = height_map_height_;

  //2 triangles per quad, each pixel represents a triangle
  const unsigned int num_triangles = (terrain_width - 1) * (terrain_height - 1) * 2;
  std::vector<unsigned int> indices;
  //Each triangle have 3 vertex
  indices.resize(num_triangles * 3);
  int index = 0;
  for (int y = 0; y < (terrain_height -1); y++){
    for (int x = 0; x < (terrain_width - 1); x++){
      int vertex_index = (y * terrain_width) + x;
      //1 triangle
      indices[index++] = vertex_index;
      indices[index++] = vertex_index + terrain_width + 1;
      indices[index++] = vertex_index + 1;
      //2 triangle 
      indices[index++] = vertex_index;
      indices[index++] = vertex_index + terrain_width;
      indices[index++] = vertex_index + terrain_width + 1;
    }
  }

  terrain_mesh_->getBuffer()->setAttributeSize(terrain_position.size() / 3,
    0,
    terrain_uvs.size() / 2, 0, 0,
    indices.size());
  terrain_mesh_->loadData(terrain_position, terrain_normal, terrain_uvs,indices);

  drawable_terrain_->setGeometry(terrain_mesh_);
  drawable_terrain_->setMaterial(terrain_material_);
}