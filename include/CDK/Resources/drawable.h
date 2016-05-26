#ifndef __H_DRAWABLE__
#define __H_DRAWABLE__
#include <memory>

#include "CDK\Material/material.h"
#include "CDK\Resources/geometry.h"
#include "CDK/Resources/node.h"

/**
@author Alejandro Canela Mendez
*ESAT 2016
*Drawable class
*/
class Drawable :public Node {
  
public:

	Drawable();

  /**
  *@brief Get geometry to drawable
  * @param  Update the display list.
  */
  std::shared_ptr<Geometry> geometry();
  /**
  *@brief GSet material to drawable
  * @param  Update the display list.
  */
  std::shared_ptr<Material> material();
  /**
  *@brief Set geometry to drawable
  * @param  Update the display list.
  */
  void setGeometry(const std::shared_ptr<Geometry> argo);
  /**
  *@brief Set material to drawable
  * @param  Update the display list.
  */
	void setMaterial(const std::shared_ptr<Material>mat);
  /**
  *@brief Set material  settings to drawable
  * @param New material sett
  */
  void setMaterialSettings(std::shared_ptr<Material::MaterialSettings>mat_s);
  /**
  *@brief Get material  settings of drawable
  * @return Drawable material settings  
  */
  std::shared_ptr<Material::MaterialSettings>  getMaterialSettings();
private:
  struct Data;
	Data *data_;

};

#endif