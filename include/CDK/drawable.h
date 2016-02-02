#ifndef __H_DRAWABLE__
#define __H_DRAWABLE__
#include <memory>

#include "CDK\material.h"
#include "CDK\geometry.h"
#include "node.h"
class Drawable :public Node {
  
public:
	struct Data;
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
	void setGeometry(std::shared_ptr<Geometry>);
  /**
  *@brief Set material to drawable
  * @param  Update the display list.
  */
	void setMaterial(std::shared_ptr<Material>);

private:
	Data *data_;

};

#endif