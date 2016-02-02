#ifndef __H_NODE__
#define __H_NODE__
#include <memory>
#include <vector>
#include "types.h"

#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Light;
class Drawable;
class Node  {
  
public:
	struct Data;
  struct Transform;
	Node();
 virtual ~Node();
	void addChild(std::shared_ptr<Node> child);
  void removeChild(unsigned int index);
	std::shared_ptr<Node> childAt(int index);
  void addLight(Light t);

	//Getter and settersç
	vec3 position();
	vec3 rotation();
	vec3 scale();
	mat4 modelMat();
  mat4 worldMat();

  void setWorldMat(mat4 w_m);
  void setModelMat(mat4 w_m);

	void setPosition(vec3 &data);
	void setPosition(const float* data);

	void setRotation(vec3 &data);
	void setRotation(const float* data);

	void setScale(const float* data);
  std::shared_ptr<Node> getParent();
  void setParent(std::shared_ptr<Node>p);
	int size();
	void  calculateModel();
	void combine(std::shared_ptr<Node> c_m);
  void setDirtyNode(bool value);
  bool getDirtyNode();
  std::vector<Light> getLigths();
  
private:
	Data *data_;
	

};

#endif

