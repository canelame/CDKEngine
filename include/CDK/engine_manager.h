

class EngineManager{
public:
  
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
void setRenderTarget(int rt);
/**
*/
int getRenderTarget();
private:
  EngineManager(){};
  int width_;
  int height_;
  int current_render_target_;
 static EngineManager * instance_;

};