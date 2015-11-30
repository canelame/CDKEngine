#ifndef __H_NODE__
#define __H_NODE__
#include <memory>
#include <vector>
#include "types.h"

#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Drawable;
class Node{
  
public:
	struct Data;
  struct Transform;
	Node();
  ~Node();
	void addChild(std::shared_ptr<Node> child);
	std::shared_ptr<Node> childAt(int index);

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
  std::shared_ptr<Node> getParent();
  void setParent(std::shared_ptr<Node>p);
	int size();
private:
	Data *data_;
	

};

#endif