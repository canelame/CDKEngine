#include "CDK\texture.h"
#include "CDK\drawable.h"

class TextureMaterial;
class Terrain{

  std::shared_ptr<Texture> height_map_;
  std::shared_ptr<Geometry> terrain_mesh_;
  std::shared_ptr<TextureMaterial> terrain_material_;

  unsigned int height_map_width_;
  unsigned int height_map_height_;
  unsigned int inc_ptr;
  unsigned int row_step_;
public:
  std::shared_ptr<Drawable> drawable_terrain_;
  Terrain();
  ~Terrain();
  void loadHeightMapTexture( const char * file_name);
  void create();
  int getWidth();
  int getHeight();
  float height_scale = 500.0f; //Max height
  float block_scale = 2.0f;




};