#ifndef __H_DRAWABLE__
#define __H_DRAWABLE__
#include <memory>
#include "CDK\geometry.h"
#include "CDK\material.h"
class Drawable{
public:
	struct Data;
	Drawable();
	//Getter and settersç
	vec3 position();
	vec3 rotation();
	vec3 scale();

	void setPosition(vec3 &data);
	void setPosition(const float* data);

	void setRotation(vec3 &data);
	void setRotation(const float* data);

	void setScale(vec3 &data);
	void setScale(const float* data);

	void setGeometry(std::shared_ptr<Geometry>);
	void setMaterial(std::shared_ptr<Material>);
private:
	Data *data_;

};

#endif