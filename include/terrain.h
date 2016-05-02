#include "CDK\texture.h"
#include "CDK\geometry.h"

class Terrain{
  std::shared_ptr<Texture> height_map_;
  std::shared_ptr<Geometry> terrain_mesh_;
  unsigned int height_map_width_;
  unsigned int height_map_height_;
  unsigned int inc_ptr;
  unsigned int row_step_;
public:
  Terrain();
  ~Terrain();
  void loadHeightMapTexture( const char * file_name);
  void create();
  int getWidth();
  int getHeight();




};