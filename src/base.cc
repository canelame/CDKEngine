#include "base.h"

glm::vec3 Base::getPosition(){ return position_; }

glm::vec3 Base::getRotation(){return rotation_;}

glm::vec3 Base::getScale(){ return scale_; }

void Base::setPosition(float x, float y, float z){ position_.x = x; position_.y = y; position_.z = z; }
void Base::setScale(float x, float y, float z){ scale_.x = x; scale_.y = y; scale_.z = z; }
void Base::setRotation(float x, float y, float z){ rotation_.x = x; rotation_.y = y; rotation_.z = z; }