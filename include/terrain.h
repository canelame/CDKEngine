#include "CDK\texture.h"
#include "CDK\drawable.h"

class TerrainMaterial;
class Terrain : public Drawable{

  std::shared_ptr<Texture> height_map_;
  std::shared_ptr<Geometry> terrain_mesh_;


  unsigned int height_map_width_;
  unsigned int height_map_height_;
  unsigned int inc_ptr;
  unsigned int row_step_;

  float getMapHeight(unsigned char*data, int num_bytes);
public:

  std::shared_ptr<TerrainMaterial> terrain_material_;
  Terrain();
  ~Terrain();
  void loadHeightMapTexture( const char * file_name);
  void create();
  int getWidth();
  int getHeight();

  void setPosition(vec3 &data);
  void setPosition(const float* data);
  void setRotation(vec3 &data);
  void setRotation(const float* data);

  void setScale(const float* data);
  void setScale(vec3 &data);


  float height_scale = 500.0f; //Max height
  float scale_x_ = 16.0f;
  float scale_z_= 16.0f;
  float scale_y_ = 1.25;


 


};
