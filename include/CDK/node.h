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
/**
@author Alejandor Canela Mendez
ESAT 2016.
Node class
*/
class Node  {
  
public:

  bool selected;//USE for GUI
	Node();
  virtual ~Node();
  /**
  @brief Add child to node
  @param child New child
  */
	void addChild(std::shared_ptr<Node> child);
  /**
  @brief Remove child from node
  @param index Position of the child to remove in the list
  */
  void removeChild(unsigned int index);
  /**
  @brief Return the child at target index
  @param index Index of the children to get.
  @return Children at index position
  */
	std::shared_ptr<Node> childAt(int index);
  /**
  @brief Add light to node.
  @param t New light
  */
  void addLight(std::shared_ptr<Light> t);
  /**
  @brief Get light position
  @return Current light position
  */
	vec3 position();
  /**
  @brief Get light rotation
  @return Current light rotation
  */
	vec3 rotation();
  /**
  @brief Get current scale node-
  @return Current scale
  */
	vec3 scale();
  /**
  @brief Return model matrix of the node
  @return Mat4 model matrix
  */
	mat4 modelMat();
  /**
  @brief Return calculated world matrix
  @return Mat4 world matrix
  */
  mat4 worldMat();
  /**
  @brief Set world matrix of the node
  @param w_m New world matrix
  */
  void setWorldMat(mat4 w_m);
  /**
  @brief Set model matrix of the node
  @param m_m  New model matrix 
  */
  void setModelMat(mat4 m_m);
  /**
  @brief Set new position to node
  @data New position whit vec3
  */
	void setPosition(vec3 &data);
  /**
  @brief Set position to node
  @param data New position whit pointer of floats
  */
	void setPosition(const float* data);
  /**
  @brief Set rotation to node
  @param data New rotation whit vec3
  */
	void setRotation(vec3 &data);
  /**
  @brief Set rotation to node
  @param data New rotation whit pointer of floats
  */
	void setRotation(const float* data);
  /**
  @brief Set scale to node
  @param data New scale whit pointer of floats
  */
	void setScale(const float* data);
  void setScale(vec3 &data);
  /**
  @brief Get current poarent of node
  @return shared_ptr of parent if exists
  */
  std::shared_ptr<Node> getParent();
  /**
  @brief Set parent to node
  @param p New parent
  */
  void setParent(std::shared_ptr<Node>p);
  /**
  @brief Get size of child list
  @return Total childs
  */
	int size();
  /**
  @brief Calculate model , taking position rotation and scale

  */
	void  calculateModel();
  /**
  @brief Set dirty if node change
  @param Is dirty or not.
  */
  void setDirtyNode(bool value);
  /**
  @brief Get if the node is dirty
  return True if node is dirty , otherwise false
  */
  bool getDirtyNode();
  /**
  @brief Get lights of the node
  @return Vector whit current lights
  */
  std::vector<std::shared_ptr<Light>> getLigths();
  /**
  @brief Return total lights of the node
  @return Total lights
  */
  int totalLights();
  /**
  @breif Set name node
  @param char* name
  */
  void setName( const char*name);
  /**
  @brief Get node name
  @return name Name of the node
  */
 const char* getName();
private:
  struct Data;
	Data *data_;
	

};

#endif

