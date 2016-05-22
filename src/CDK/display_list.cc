#include "CDK/display_list.h"
#include "CDK/texture_cache.h"

#include "CDK/engine_manager.h"

#define ENGINE EngineManager::instance()
DisplayList::DisplayList(){

}
DisplayList::~DisplayList(){
}
void DisplayList::add(Comm_ c){
	listCommand_.push_back(c);
  
}
void DisplayList::execute(){

  renderScene();

}


void DisplayList::clear(){
  listCommand_.clear();
}

int DisplayList::size(){ 
	return 0;
}






///////// DRAW_COMMAND CLASS/////////////////
////////////////////////////////////////////
DrawCommand::DrawCommand(Buffer *g){
	
		t_geo = g;
    indices_size_ = t_geo->indiceSize();
    vao_ = t_geo->getVAO();
}

void DrawCommand::runCommand()const{
  if (t_geo->isDirty() && t_geo != nullptr){
    OpenGlInterFaz::instance().loadBuffer(t_geo);
    t_geo->setDirty(false);
  }
  OpenGlInterFaz::instance().drawGeometry(t_geo->getVAO(), indices_size_);

}

///////// USE_MATERIAL_COMMAND CLASS/////////
////////////////////////////////////////////
UseMaterialCommand::UseMaterialCommand(Material *mat){
  material_ = mat;

}

void UseMaterialCommand::runCommand()const{
  if (!material_->is_compiled_){
    material_->setProgram(OpenGlInterFaz::instance().loadMaterial(material_));
    material_->is_compiled_ = true;
  }
  OpenGlInterFaz::instance().useMaterial(material_);
 // glUseProgram(material_->getProgram());

  
}
///////////////////////////////////////////////////
UseMaterialUniformsCommand::UseMaterialUniformsCommand(Material* mat, Material::MaterialSettings *mat_s,
  mat4 projection, mat4 view, mat4 model, std::vector<std::shared_ptr<Light>> lights, Light *dir_light){

  mat_set_ = mat_s;
  mat_ = mat;
  projection_ = projection;
  model_ = model;
  view_ = view;
  dir_light_ = dir_light;
  lights_ = lights;
}

void UseMaterialUniformsCommand::runCommand()const{

  switch (mat_->type_){
  case 0:
    OpenGlInterFaz::instance().useTextureMaterial(mat_, mat_set_, view_,projection_, model_,
      dir_light_, lights_);
    break;
  case 1:
    OpenGlInterFaz::instance().useDiffuseMaterial(mat_, mat_set_, view_, projection_, model_,
      dir_light_, lights_);
    break; 
  default:
    OpenGlInterFaz::instance().useMaterialUniforms(mat_);
    break;
  }
 

}

///////////////////////////////////////////////////

void DisplayList::renderScene(){

  for (int i = 0; i < listCommand_.size(); ++i){
    listCommand_[i]->runCommand();
  }
}


SendObjectShadow::SendObjectShadow(Buffer * g,mat4 m,bool is_directional){
  m_ = m;
  t_geo = g;
  is_directional_ = is_directional;
}

void SendObjectShadow::runCommand()const{
  if (is_directional_){
    int location = ENGINE.getShadowMap()->getUniformLocation("u_model_s");
    OpenGlInterFaz::instance().useUniformMat4(location, m_);
  }
  else{
    int location = ENGINE.getCubeShadowMap()->getUniformLocation("u_model_sp");
      OpenGlInterFaz::instance().useUniformMat4(location,m_);
  }

  if (t_geo->isDirty()){
    OpenGlInterFaz::instance().loadBuffer(t_geo);
    t_geo->setDirty(false);
   }
 
  OpenGlInterFaz::instance().drawGeometry(t_geo->getVAO(), (unsigned int)t_geo->indiceSize());
}

 EndShadowCommand::EndShadowCommand(){}
 void EndShadowCommand::runCommand()const{
   
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glViewport(0, 0, EngineManager::instance().width(), EngineManager::instance().height());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 }

 EndShadowCubeMapCommand::EndShadowCubeMapCommand(){}
 void EndShadowCubeMapCommand::runCommand()const{
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
 }

 RenderDirectionalShadowMapCommand::RenderDirectionalShadowMapCommand(Light* l){
   light_ = l;
 }
 void RenderDirectionalShadowMapCommand::useMaterial(){
  
 }
#include "CDK/directional_light.h"
 void RenderDirectionalShadowMapCommand::runCommand()const{
   
   if (!ENGINE.getShadowMap()->is_compiled_){
     ENGINE.getShadowMap()->setProgram(OpenGlInterFaz::instance().loadMaterial(ENGINE.getShadowMap()));
     ENGINE.getShadowMap()->is_compiled_ = true;
   }

   if (light_->getType() == Light::T_DIRECTION_LIGHT){

     DirectionalLight * dr_light = (DirectionalLight*)light_;
     //Directional light
     FrameBuffer * light_depth_map = dr_light->getShadowMap();

     if (!light_depth_map->isLoaded()){

       Texture  * d_texture = light_depth_map->getTexture().get();
       d_texture->setFormat(Texture::kTextureFormat::kTextureFormat_Depth);
       d_texture->setPixelType(Texture::kTexturePixelType::kTexturePixelType_Float);
       d_texture->setMagFilter(Texture::kTextureFiltering::kTextureFiltering_Nearest);
       d_texture->setMinFilter(Texture::kTextureFiltering::kTextureFiltering_Nearest);
       d_texture->setWrapCoordinateS(Texture::kTextureWrapping::kTextureWrapping_Clamp_Border);
       d_texture->setWrapCoordinateT(Texture::kTextureWrapping::kTextureWrapping_Clamp_Border);
       OpenGlInterFaz::instance().createFrameBuffer(*light_depth_map, false);
       ENGINE.getShadowMap()->setUniformMat4Value("light_screen", &dr_light->getLightProyection());
       light_depth_map->setLoaded(true);
     }
     glViewport(0, 0, 1024, 1024);
     OpenGlInterFaz::instance().bindFrameBuffer(dr_light->getShadowMap()->getId(),
                                                 FrameBuffer::kFramebufferBindType::
                                                 kFramebufferBindType_FrameBuffer);
     OpenGlInterFaz::instance().useMaterial(ENGINE.getShadowMap());
     int loca_proj_light = ENGINE.getShadowMap()->getUniformLocation("light_screen");
     OpenGlInterFaz::instance().useUniformMat4(loca_proj_light, dr_light->getLightProyection());
     glClear(GL_DEPTH_BUFFER_BIT);
     
   }
 }

#include "CDK/point_light.h"

 RenderPointShadowMapCommand::RenderPointShadowMapCommand(Light * l, int face){
   light_ = (PointLight*)l;
   face_ = face;
 }
 void RenderPointShadowMapCommand::runCommand()const{

   if (!ENGINE.getCubeShadowMap()->is_compiled_){
     ENGINE.getCubeShadowMap()->setProgram(OpenGlInterFaz::instance().loadMaterial(ENGINE.getCubeShadowMap()));
     ENGINE.getCubeShadowMap()->is_compiled_ = true;
   }

   if (light_->getShadowCubeMapTexture() < 0 && light_->getShadowCubeMapBuffer() < 0){
     OpenGlInterFaz::instance().createShadoCubeMap(light_);
   }
   //



   glViewport(0, 0, 1024, 1024);
   OpenGlInterFaz::instance().bindFrameBuffer(light_->getShadowCubeMapBuffer(),
     FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);

   OpenGlInterFaz::instance().useMaterial(ENGINE.getCubeShadowMap());
   
     std::vector<mat4> s_m = light_->getShadowMatrices();
     //Set correct values to uniforms
     for (int i = 0; i < 6; i++){
       int u_pos = ENGINE.getCubeShadowMap()->getUniformLocation(("shadow_matrices[" + std::to_string(i) + "]").c_str());
       OpenGlInterFaz::instance().useUniformMat4(u_pos, s_m[i]);
     }

     int l_p = ENGINE.getCubeShadowMap()->getUniformLocation("light_pos");
     if (l_p >= 0){
       OpenGlInterFaz::instance().useUnifor3f(l_p,light_->getPosition() );
     }

     int l_fp = ENGINE.getCubeShadowMap()->getUniformLocation("far_plane");
     if (l_fp >= 0){
       OpenGlInterFaz::instance().useUniformF(l_fp, 25.0);
     }

     glClear(GL_DEPTH_BUFFER_BIT);
 }

 PostProcessBegin::PostProcessBegin(){
   glViewport(0, 0, 1024, 1024);

   if (!fb_ptr_->isLoaded()){
     OpenGlInterFaz::instance().createFrameBuffer(*fb_ptr_, true);
     material_->setProgram(OpenGlInterFaz::instance().loadMaterial(material_));
   }


   OpenGlInterFaz::instance().bindFrameBuffer(fb_ptr_->getId(), FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
   glClear(GL_DEPTH_BUFFER_BIT);
 }
 PostProcessBegin::PostProcessBegin(FrameBuffer* fb, Material * mat){
   fb_ptr_ = fb;
   material_ = mat;
 }
 void PostProcessBegin::runCommand()const{
 
 }