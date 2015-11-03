#ifndef __H_NODE__
#define __H_NODE__
#include <memory>
#include <vector>
#include "types.h"
#include "drawable.h"
class Node{

public:
	struct Data;
	Node();
	void addChild(std::shared_ptr<Drawable> child);
	std::shared_ptr<Drawable> childAt(int index);

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

	int size();
private:
	Data *data_;
	

};

#endif