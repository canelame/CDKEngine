#ifndef __H_MAT_DIFFUSE_
#define __H_MAT_DIFFUSE_
#include "CDK\material.h"

class MaterialDiffuse : public Material{

private :
 /* const char diffuse_vertex_shader[] = { "#version 330\n"

    "layout(location = 0) in vec3 position; \n"
  "layout(location = 1) in vec3 normal;\n"
  "layout(location = 2) in vec2 uv;\n"
  "uniform mat4 u_projection_m;\n"
  "uniform mat4 u_model_m;\n"
  "uniform mat4 u_view_m;\n"

  "out vec2 o_uv;\n"
  "out vec3 o_normal;\n"
  "out vec4 o_world_position;\n"

  "vec3 camera_position = (inverse(u_view_m)*vec4(0.0, 0.0, 0.0, 1.0)).xyz;\n"
  "void main(){\n"
    "o_normal = normal;\n"
    "o_uv = uv;\n"
    "o_normal = vec3(normalize(u_model_m * vec4(o_normal, 0.0)));\n"
    "o_world_position = u_model_m * vec4(position, 1.0);\n"
    "gl_Position = u_projection_m*u_view_m*o_world_position;\n"
  
  }*/


public:

};


#endif