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

struct {
	std::shared_ptr<Node> root;
	std::shared_ptr<Camera> cam;

}Scene;



int Window::main(int argc, char** argv){

  std::shared_ptr<Window> window = std::make_shared<Window>();
  window->init(1280,980 );


  Scene.cam = std::make_shared<Camera>();
  Scene.cam->setPerspective(45, 800.0 / 600.0, 0.1, 100000.0);
  //Create Root
  Scene.root = std::make_shared<Node>();
  Scene.root->setName("Root");
  std::shared_ptr<Loader> loader = std::make_shared<Loader>();




  //Create Camera

  std::shared_ptr<Light> l1 = std::make_shared<Light>();
  l1->setPosition(vec3(0.0,0.0,95.0));
  l1->setAmbientColor(vec3(1.0, 1.0, 1.0));
  l1->setSpecularColor(vec3(1.0,1.0,1.0));
  l1->setDifusseColor(vec3(1.0,1.0,1.0));
  l1->setTypeLight(Light::LightType::T_DIRECTION_LIGHT);

  std::shared_ptr<Light> l2 = std::make_shared<Light>();
  l2->setPosition(vec3(0.0, 30.0, 0.0));
  l2->setAmbientColor(vec3(1.0, 0.0, 0.0));
  l2->setSpecularColor(vec3(1.0, 0.0, 0.0));
  l2->setDifusseColor(vec3(1.0, 1.0, 1.0));
  l2->setTypeLight(Light::LightType::T_DIRECTION_LIGHT);


 // Scene.root->addLight(l1);
  Scene.root->addLight(l2);
  std::shared_ptr<Drawable> w = std::make_shared<Drawable>();
  std::shared_ptr<Drawable> w1 = loader->loadCDK("meshes/milen.cdk");

  std::shared_ptr<Material> mater = std::make_shared<Material>(Material::TYPE::ONNLY_DIFFUSE_);
  std::shared_ptr<Geometry> geo = std::make_shared<Geometry>();
  geo->createCube(); w->setName("Cube");
  w1->setName("Alchon milenario");
  w->setGeometry(*&geo);
  w->setMaterial(*&mater);
 w->setPosition(vec3(0.0, 0.0, 0.0));
  w->setScale(vec3(100, 100, 100));

  Scene.root->setPosition(vec3(0.0,0.0,90.0));
  Scene.root.get()->addChild(w);
  Scene.root.get()->addChild(std::move(w1));
  while (window->processEvents()){
   if(Input::pressSpace()) Scene.cam->FpsCameraUpdate();

    window->clearScreen(vec3(0.3, 0.2, 0.1));
    Scene.cam->render(Scene.root);
    window->swap();

  }


  system("pause");
  return 0;
}