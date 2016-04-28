#include <chrono>
#include <stdio.h>
#include <memory>
#include "CDK/window2.h"
#include "CDK/geometry.h"
#include "CDK/camera.h"
#include "CDK/texture_material.h"
#include "CDK/point_light.h"
#include "CDK/spot_light.h"
#include "CDK/node.h"
#include "CDK/loader.h"
#include "glm\glm.hpp"
#include "CDK/texture.h"
#include "post_process.h"
#include "CDK/gui_interface.h"
#include "CDK/scene.h"
#include "terrain.h"

std::shared_ptr<Scene> scene = std::make_shared<Scene>();


int Window::main(int argc, char** argv){

  std::shared_ptr<Window> window = std::make_shared<Window>();
  window->init(1024, 1024);

  //Init root
  std::shared_ptr<Loader> loader = std::make_shared<Loader>();
  ///
  
  ///CREATE OBJECTS
  std::shared_ptr<Terrain> terrain = std::shared_ptr<Terrain>();

  std::shared_ptr<Geometry> plane = std::make_shared<Geometry>();
  plane->createQuad();

  std::shared_ptr<Geometry> cube = std::make_shared<Geometry>();
  cube->createCube();

  std::shared_ptr<Drawable> drawable_cube;
  std::shared_ptr<TextureMaterial> mater = std::make_shared<TextureMaterial>();
  std::shared_ptr<TextureMaterial::MaterialSettings> mat_s = std::make_shared<TextureMaterial::MaterialSettings>();
  mat_s->diffuse_color_ = vec3(0.0, 0.0, 0.0);
  mat_s->ambient_color_ = vec3(1.0);
  mat_s->specular_color_ = vec3(1.0);
  mat_s->addTexture("textures/container.jpg");
  std::shared_ptr<Texture> texture_cube = loader->loadTexture("textures/container.jpg","diffuse");
  std::shared_ptr<Texture> texture_plane = loader->loadTexture("textures/wall.jpg", "diffuse");

  std::shared_ptr<TextureMaterial::MaterialSettings> mat_p = std::make_shared<TextureMaterial::MaterialSettings>();
  mat_p->addTexture("textures/wall.jpg");
  drawable_cube = std::make_shared<Drawable>();
  drawable_cube->setName("Plane");
  drawable_cube->setGeometry(plane);
  drawable_cube->setMaterial(mater);
  drawable_cube->setMaterialSettings(mat_p);
  drawable_cube->setPosition(vec3(0.0, 0.0, 0.0));
  drawable_cube->setRotation(vec3(90.0, 0.0, 0.0));
  drawable_cube->setScale(vec3(25.0, 25.0, 25.0));


  std::shared_ptr<Drawable> wall = std::make_shared<Drawable>();
  wall->setGeometry(plane);
  wall->setMaterial(mater);
  wall->setMaterialSettings(mat_p);
  scene->addChild(drawable_cube);
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
      drawable_cube = std::make_shared<Drawable>();
      drawable_cube->setName("cube");
      drawable_cube->setGeometry(cube);
      drawable_cube->setMaterial(mater);
      drawable_cube->setMaterialSettings(mat_s);
      drawable_cube->setScale(vec3(0.5));
      drawable_cube->setPosition(positions[i]);
      //drawable_cube->setRotation(vec3(10.0,0.0,60.0));
      scene->addChild(drawable_cube);
  }

  //////////////////////

  ///LIGHTS
  


  std::shared_ptr<PointLight> l2 = std::make_shared<PointLight>();
  l2->setPosition(vec3(0.0, 0.0, 5.0));
  l2->setAmbientColor(vec3(1.0, 1.0, 1.0));
  l2->setSpecularColor(vec3(1.0, 1.0, 1.0));
  l2->setDifusseColor(vec3(1.0, 0.0, 1.0));
  l2->setTypeLight(Light::LightType::T_POINT_LIGHT);
  scene->addLight(l2);

  std::shared_ptr<SpotLight> l3 = std::make_shared<SpotLight>();
  l3->setPosition(vec3(1.0, 0.0, 1.0));
  l3->setAmbientColor(vec3(0.0, 0.0, 1.0));
  l3->setSpecularColor(vec3(0.0, 0.0, 1.0));
  l3->setDifusseColor(vec3(0.0, 0.0, 1.0));
  l3->setTypeLight(Light::LightType::T_SPOT_LIGHT);
  //scene->addLight(l3);

  scene->root_->setPosition(vec3(0.0,0.0,0.0));

  //std::shared_ptr<PostProcess>render_to_text = std::make_shared<PostProcess>();
  glEnable(GL_DEPTH_TEST);
  while (window->processEvents()){
    scene->camera_->FpsCameraUpdate();
//    window->clearScreen(vec3(0.3, 0.2, 0.1));
  
    scene->directional_light_->setPosition(vec3(scene->directional_light_->getPosition().x , 10.0, 1.0));
    scene->directional_light_->setPosition(vec3( (cos(window->time()) *10.0f)*0.5+0.5, (sin(window->time())*3.0) *0.5+0.5, 1.0));
  //  render_to_text->begin();
    scene->render();
   // render_to_text->end();
    //GuInterface::instance().draw(Scene.root);
    window->swap();
    

  }


  system("pause");
  return 0;
}