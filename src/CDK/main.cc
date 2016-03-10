#include <chrono>
#include <stdio.h>
#include <memory>
#include "CDK/window2.h"
#include "CDK/geometry.h"
#include "CDK/camera.h"
#include "CDK/material.h"
#include "CDK/node.h"
#include "CDK/loader.h"
#include "glm\glm.hpp"
#include "CDK/texture.h"
#include "post_process.h"
#include "CDK/gui_interface.h"

struct {
	std::shared_ptr<Node> root;
	std::shared_ptr<Camera> cam;

}Scene;



int Window::main(int argc, char** argv){

  std::shared_ptr<Window> window = std::make_shared<Window>();
  window->init(1024, 768);

  //Init root
  Scene.cam = std::make_shared<Camera>();
  Scene.cam->setPerspective(45, 1024.0 / 768.0, 0.1, 10000.0);
  
  Scene.root = std::make_shared<Node>();
  std::shared_ptr<Loader> loader = std::make_shared<Loader>();
  ///
  
  ///CREATE OBJECTS

  std::shared_ptr<Geometry> plane = std::make_shared<Geometry>();
  plane->createQuad();

  std::shared_ptr<Geometry> cube = std::make_shared<Geometry>();
  cube->createCube();

  std::shared_ptr<Drawable> drawable_cube;
  std::shared_ptr<Material> mater = std::make_shared<Material>(0);
  std::shared_ptr<Material::MaterialSettings> mat_s = std::make_shared<Material::MaterialSettings>();
  mat_s->diffuse_color_ = vec3(0.0, 1.0, 0.0);
  mat_s->ambient_color_ = vec3(0.5);
  mat_s->specular_color_ = vec3(1.0);
  mat_s->addTexture("textures/container.jpg");
  std::shared_ptr<Texture> texture_cube = loader->loadTexture("textures/container.jpg","diffuse");
  std::shared_ptr<Texture> texture_plane = loader->loadTexture("textures/wall.jpg", "diffuse");
  for (int i = 0; i < 5; i++){
      float j = 0.2;
      drawable_cube = std::make_shared<Drawable>();
      drawable_cube->setName("cube");

      drawable_cube->setGeometry(cube);
      drawable_cube->setMaterial(mater);
      drawable_cube->setMaterialSettings(mat_s);
      
      drawable_cube->setPosition(vec3(0.0 + i*10.0, 0.0, 0.0 + i*10.0));
      Scene.root->addChild(drawable_cube);
  }
  std::shared_ptr<Material::MaterialSettings> mat_p = std::make_shared<Material::MaterialSettings>();
  mat_p->addTexture("textures/wall.jpg");
  drawable_cube = std::make_shared<Drawable>();
  drawable_cube->setName("Plane");
  drawable_cube->setGeometry(plane);
  drawable_cube->setMaterial(mater);
  drawable_cube->setMaterialSettings(mat_p);
  drawable_cube->setPosition(vec3(0.0,-5.0,0.0));
  drawable_cube->setRotation(vec3(90.0, 0.0, 0.0));
  drawable_cube->setScale(vec3(100.0, 100.0, 100.0));
 
  Scene.root->addChild(drawable_cube);
  //////////////////////

  ///LIGHTS
  
  std::shared_ptr<Light> l1 = std::make_shared<Light>();
  l1->setPosition(vec3(0.0,0.0,60.0));
  l1->setAmbientColor(vec3(1.0, 1.0, 1.0));
  l1->setSpecularColor(vec3(1.0,1.0,1.0));
  l1->setDifusseColor(vec3(1.0,1.0,1.0));
  l1->setTypeLight(Light::LightType::T_POINT_LIGHT);

  std::shared_ptr<Light> l2 = std::make_shared<Light>();
  l2->setPosition(vec3(10.0, 0.0, 100.0));
  l2->setAmbientColor(vec3(1.0, 0.0, 0.0));
  l2->setSpecularColor(vec3(0.0, 1.0, 1.0));
  l2->setDifusseColor(vec3(1.0, 0.0, 1.0));
  l2->setTypeLight(Light::LightType::T_POINT_LIGHT);


  Scene.root->addLight(l1);
  Scene.root->addLight(l2);
  Scene.root->setPosition(vec3(0.0,0.0,90.0));

  std::shared_ptr<PostProcess>render_to_text = std::make_shared<PostProcess>();
  
  while (window->processEvents()){
    Scene.cam->FpsCameraUpdate();
    window->clearScreen(vec3(0.3, 0.2, 0.1));
  
    render_to_text->begin();
   Scene.cam->render(Scene.root);
    render_to_text->end();
    GuInterface::instance().draw(Scene.root);
    window->swap();
    

  }


  system("pause");
  return 0;
}