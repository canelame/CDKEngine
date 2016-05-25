#include <chrono>
#include <stdio.h>
#include <memory>
#include "CDK/window2.h"
#include "CDK/geometry.h"
#include "CDK/camera.h"

#include "CDK/point_light.h"
#include "CDK/spot_light.h"
#include "CDK/node.h"
#include "CDK/loader.h"
#include "glm\glm.hpp"
#include "CDK/texture.h"
#include "crazy_pp.h"
#include "negative_pp.h"
#include "CDK/gui_interface.h"
#include "CDK/scene.h"
#include "terrain.h"
#include "../terrain_mat.h"
#include "CDK/diffuse_material.h"
#include "CDK/composer.h"
std::shared_ptr<Scene> scene = std::make_shared<Scene>();


int Window::main(int argc, char** argv){

  std::shared_ptr<Window> window = std::make_shared<Window>();
  window->init(1024, 1024);

  //Init root
  std::shared_ptr<Loader> loader = std::make_shared<Loader>();
  ///
  
  ///CREATE OBJECTS
  std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>();
  terrain->loadHeightMapTexture("textures/height_map.png");
  terrain->create();

  terrain->setScale(vec3(1.0,1.0, 1.0));
  terrain->setRotation(vec3(180.0, 0.0, 0.0));
  terrain->setPosition(vec3(0.0,0.0, 0.0));

  std::shared_ptr<Geometry> plane = std::make_shared<Geometry>();
  plane->createQuad();

  std::shared_ptr<Geometry> cube = std::make_shared<Geometry>();
  cube->createCube();

  std::shared_ptr<Drawable> drawable_cube;


  
  std::shared_ptr<Texture> texture_cube = loader->loadTexture("textures/container.jpg","diffuse");
  std::shared_ptr<Texture> texture_plane = loader->loadTexture("textures/wall.jpg", "diffuse");

  std::shared_ptr< MaterialDiffuse::MaterialSettings> mat_p = std::make_shared<MaterialDiffuse::MaterialSettings>();
  mat_p->diffuse_color_ = vec3(0.0, 0.5, 0.0);
  mat_p->ambient_color_ = vec3(0.0);
  mat_p->specular_color_ = vec3(0.5);
  std::shared_ptr<MaterialDiffuse> mater = std::make_shared<MaterialDiffuse>();

  // mat_p->addTexture("textures/container.jpg");

  drawable_cube = std::make_shared<Drawable>();
  drawable_cube->setName("Plane");
  drawable_cube->setGeometry(plane);

  drawable_cube->setPosition(vec3(0.0, 0.0, 0.0));
  drawable_cube->setRotation(vec3(90.0, 0.0, 0.0));
  drawable_cube->setScale(vec3(25.0, 25.0, 25.0));
  drawable_cube->setMaterial(mater);



  //terrain->setMaterial(mater);
  drawable_cube->setMaterialSettings(mat_p);
  
  scene->addChild(drawable_cube);
  terrain->setMaterial(mater);
  terrain->setMaterialSettings(mat_p);

 // scene->addChild(terrain);
  vec3 positions[10] = { vec3(0.0, 5.5f, 0.0),
    vec3(2.0f, 0.0f, 1.0f),
    vec3(-1.0, 0.0f, 2.0f),
    vec3(0.0,0.0,0.0),
    vec3(-3.0, 1.0, 10.0),
    vec3(1.0f, 1.0f, 1.0f),
    vec3(-1.0, 1.0f, 3.0f),
    vec3(3.0, 0.0, 1.0),
    vec3(-3.0, 0.0, 2.0) };
  for (int i = 0; i < 10; i++){
    float j = 0.2; 
    mat_p = std::make_shared<MaterialDiffuse::MaterialSettings>();
    mat_p->diffuse_color_ = vec3(1.0, 1.0, 0.0);
    mat_p->ambient_color_ = vec3(0.5,0.5,0.5);
    mat_p->specular_color_ = vec3(1.0,1.0,1.0);
      drawable_cube = std::make_shared<Drawable>();
      drawable_cube->setName("cube");
      drawable_cube->setGeometry(cube);
      drawable_cube->setMaterial(mater);
      drawable_cube->setMaterialSettings(mat_p);
      drawable_cube->setScale(vec3(0.5));
      drawable_cube->setPosition(positions[i]);
    //  drawable_cube->setRotation(vec3(10.0,0.0,60.0));
      scene->addChild(drawable_cube);
  }

  //////////////////////

  ///LIGHTS
  
  std::shared_ptr<Composer> composer = std::make_shared<Composer>();

  std::shared_ptr<PointLight> l2 = std::make_shared<PointLight>();
  l2->setPosition(vec3(0.0, 0.0, 5.0));
  l2->setAmbientColor(vec3(1.0, 0.0, 0.0));
  l2->setSpecularColor(vec3(1.0, 0.0, 0.0));
  l2->setDifusseColor(vec3(1.0, 0.0, 0.0));
  l2->setTypeLight(Light::LightType::T_POINT_LIGHT);
  scene->addLight(l2);



  scene->root_->setPosition(vec3(0.0,0.0,0.0));
  std::shared_ptr<CrazyPP>render_to_text = std::make_shared<CrazyPP>();
  render_to_text->init();
   //composer->addEffect(render_to_text);

  std::shared_ptr<NegativePP>n_pp = std::make_shared<NegativePP>();
  n_pp->init();
  //composer->addEffect(n_pp);

 
  while (window->processEvents()){
    glEnable(GL_DEPTH_TEST);
    scene->camera_->FpsCameraUpdate();
    scene->render();

    window->swap();
    

  }


  system("pause");
  return 0;
}