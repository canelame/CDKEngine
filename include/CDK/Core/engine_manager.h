#include "CDK/Material/cube_shadowmap_material.h"
#include "CDK/Material/shadow_material.h"
#include "CDK/Core/display_list.h"
#include "CDK/PostProcess/composer.h"
class EngineManager{
public:

bool window_size_modified_ = false;
static  EngineManager& instance();
/**
@brief Initialize EngineManager class
*/
void init();
/**
@brief Get windows width
@return Width
*/
int width();
/**
@brief Get windows height
@return Height
*/
int height();
/**
@brief Set windows width
@param w New width
*/
void setWidth(int w);
/**
@bried Set windows height
@param h New height
*/
void setHeight(int h);

/**
@brief Handle if windows has been modified
@param value True if its , false otherwise
*/
void setWindowModified(bool value);
int enable_shadows_;
private:
 EngineManager();

 struct Data;
 Data *data_;
 std::shared_ptr<DisplayList> last_display_list_;
 static EngineManager * instance_;

 /**
 @brief Get the current composer of the engine
 @return Runing composer
 */
 Composer * getMainComposer();
 /**
 @brief Set composer to engine manager
 @param comp New Composer
 */
 void setMainComposer(const Composer* comp);
 /**
 @brief ShadowMap to directional light scene
 @return shadow map
 */
 ShadowMapMaterial* getShadowMap();
 /**
 @breif Get ShadowCumeMap to point lights
 */
 CubeShadowMaterial* getCubeShadowMap();
 /**
 */

 friend class Camera;
 friend class SendObjectShadow;
 friend class RenderDirectionalShadowMapCommand;
 friend class RenderPointShadowMapCommand;
 friend class Composer;
 friend class UpdateDisplay;
 friend class Material;
};