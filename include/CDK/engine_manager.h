#include "CDK/cube_shadowmap_material.h"
#include "shadow_material.h"
#include "display_list.h"
#include "composer.h"
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

private:
 EngineManager();

 struct Data;
 Data *data_;
 std::shared_ptr<DisplayList> last_display_list_;
 static EngineManager * instance_;

 /**
 */
 Composer * getMainComposer();
 /**
 */
 void setMainComposer(const Composer* comp);
 /**
 */
 ShadowMapMaterial* getShadowMap();
 /**
 */
 CubeShadowMaterial* getCubeShadowMap();
 /**
 */
 void setMainComposer();


 friend class Camera;
 friend class SendObjectShadow;
 friend class RenderDirectionalShadowMapCommand;
 friend class RenderPointShadowMapCommand;
 friend class Composer;
 friend class UpdateDisplay;
 friend class Material;
};