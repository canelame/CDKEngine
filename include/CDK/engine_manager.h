#
#include "material.h"
class EngineManager{
public:
  bool window_size_modified_ = false;
static  EngineManager& instance();
/**
*/
void init();
/**
*/
int width();
/**
*/
int height();
/**

*/
void setWidth(int w);
/**
*/
void setHeight(int h);

/**
*/
void setWindowModified(bool value);
void addUniform(char *name, int location);
 int getUniform(char *name);


std::shared_ptr<Material>  shadow_shader_;
std::shared_ptr<Material>  shadow_points_shader_;
int shadow_buffer_created_ = false;
int depth_bufer_id_;
int depth_texture_id_;
int draw_mode_;
private:
 EngineManager(){};
 int width_;
 int height_;





 static EngineManager * instance_;

};