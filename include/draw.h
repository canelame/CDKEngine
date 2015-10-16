#ifndef __H_DRAW__
#define __H_DRAW__
 
#include "geometry.h"
//TODO: #include "material.h"
/**
* draw.h
* @author Alejandro Canela Mendez 2015.
* @brief Class to control render
*/

class Draw{

public:
  Draw(){};
  void render(){};
private:
  Geometry *geo;

};


#endif