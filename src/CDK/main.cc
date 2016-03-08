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

struct {
	std::shared_ptr<Node> root;
	std::shared_ptr<Camera> cam;

}Scene;



int Window::main(int argc, char** argv){

  std::shared_ptr<Window> window = std::make_shared<Window>();
  window->init(1024, 768);


  Scene.cam = std::make_shared<Camera>();
  Scene.cam->setPerspective(45, 1024.0 / 768.0, 0.1, 10000.0);
  //Create Root
  Scene.root = std::make_shared<Node>();
  std::shared_ptr<Loader> loader = std::make_shared<Loader>();

  //Create Camera

  std::shared_ptr<Light> l1 = std::make_shared<Light>();
  l1->setPosition(vec3(0.0,0.0,100.0));
  l1->setAmbientColor(vec3(0.0, 1.0, 1.0));
  l1->setSpecularColor(vec3(1.0,1.0,1.0));
  l1->setDifusseColor(vec3(1.0,0.0,1.0));
  l1->setTypeLight(Light::LightType::T_DIRECTION_LIGHT);

  std::shared_ptr<Light> l2 = std::make_shared<Light>();
  l2->setPosition(vec3(0.0, 100.0, 0.0));
  l2->setAmbientColor(vec3(1.0, 1.0, 1.0));
  l2->setSpecularColor(vec3(0.0, 1.0, 1.0));
  l2->setDifusseColor(vec3(1.0, 0.0, 1.0));
  l2->setTypeLight(Light::LightType::T_DIRECTION_LIGHT);


  Scene.root->addLight(l1);
  //Scene.root->addLight(l2);
  std::shared_ptr<Drawable> w;
  //std::shared_ptr<Drawable> w1 = loader->loadCDK("meshes/mmn.cdk");

  
  std::shared_ptr<Geometry> geo = std::make_shared<Geometry>();
  geo->createCube();

 
  std::shared_ptr<Material> mater = std::make_shared<Material>(1);
  std::shared_ptr <Material::MaterialSettings> mat_s = std::make_shared<Material::MaterialSettings>();

  w->setPosition(vec3(0.0 ,10.0, 0.0 ));
  for (int i = 0 ; i < 2; i++){
    float j = 0.2;
   
    w = std::make_shared<Drawable>();
    w->setName("cube");
    mat_s->diffuse_color_ = vec3(0.0,0.64,0.0);
    mat_s->ambient_color_ = vec3(0.0);
    mat_s->specular_color_ = vec3(0.0);
    w->setGeometry(geo);
    w->setMaterial(mater);
    w->setMaterialSettings(mat_s);
    w->setPosition(vec3(0.0+i*10.0,0.0,0.0+i*10.0));
    Scene.root->addChild(w);
  }
//  Scene.root->addChild(w1);
  Scene.root->setPosition(vec3(0.0,0.0,90.0));

  std::shared_ptr<PostProcess>render_to_text = std::make_shared<PostProcess>();
  
  while (window->processEvents()){
    Scene.cam->FpsCameraUpdate();
    window->clearScreen(vec3(0.3, 0.2, 0.1));
  
    render_to_text->begin();
    Scene.cam->render(Scene.root);
    render_to_text->end();
    window->swap();
    

  }


  system("pause");
  return 0;
}