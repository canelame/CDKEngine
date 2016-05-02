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
///////// USE_TEXTURE_COMMAND CLASS/////////////////
////////////////////////////////////////////
UseTextureComman::UseTextureComman(int pro,std::vector<std::string>textures){
  textures_ = textures;
  program_mat_ = pro;
}


void UseTextureComman::runCommand()const{
  /*int num_diffuse_t = 1;
  int num_specular_t = 1;
  for (int i = 0; i < textures_.size(); i++){ 
    std::shared_ptr<Texture> current_texture = TextureCache::instance().getTexture(textures_[i].c_str());
    if (!current_texture->getLoaded()){
      OpenGlInterFaz::instance().loadTexture(current_texture);
      current_texture->setLoaded(true);
    }
    std::string type;
    std::string type_name = current_texture->getType();
    std::stringstream ssn;
    if (type_name == "diffuse"){
      type = "u_diffuse_texture";
      ssn << num_diffuse_t;
      num_diffuse_t++;
      OpenGlInterFaz::instance().useTexture(program_mat_, i, (type + ssn.str()), current_texture->getID());
    }else  if (type_name == "specular"){
        type = "u_specular_texture";
        ssn << num_specular_t;
        num_specular_t++;
        OpenGlInterFaz::instance().useTexture(program_mat_, i, (type + ssn.str()), current_texture->getID());
    }

  }*/

}


///////// USE_CAMERA_COMMAND CLASS/////////////////
////////////////////////////////////////////
UseCameraCommand::UseCameraCommand(mat4 cam_proyec, mat4 cam_view, mat4 m_m){
  proyec_m_ = cam_proyec;
  view_m_ = cam_view;
  model_n_ = m_m;
}


void UseCameraCommand::runCommand()const{


  OpenGlInterFaz::instance().useCamera(proyec_m_, model_n_, view_m_);
}

///////// LOAD_TEXTURE_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadTextureCommand::LoadTextureCommand(TextureMaterial::MaterialSettings *mat){
	t_mat = mat;
}

void LoadTextureCommand::runCommand()const{
  for (int i = 0; i < t_mat->totalTextures(); i++){
    OpenGlInterFaz::instance().loadTexture(TextureCache::instance().getTexture(t_mat->getTextureAt(i)));
      TextureCache::instance().getTexture(t_mat->getTextureAt(i))->setLoaded(true);
  }

}


///////// LOAD_MATERIAL_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadMaterialCommand::LoadMaterialCommand(Material* mat){
	t_mat = mat;
}
void LoadMaterialCommand::runCommand()const{
  OpenGlInterFaz::instance().loadMaterial(t_mat);
	t_mat->is_compiled_ = true;
}

Material*  LoadMaterialCommand::getMaterial(){ 
	return t_mat; 
}

///////// DRAW_COMMAND CLASS/////////////////
////////////////////////////////////////////
DrawCommand::DrawCommand(Buffer *g){
	
		t_geo = g;
    indices_size_ = t_geo->indiceSize();

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
    for (int i = 0; i < 10; i++){
      OpenGlInterFaz::instance().loadLight(i);
      OpenGlInterFaz::instance().loadDirectionalLight();
    }

    material_->is_compiled_ = true;
  }
  OpenGlInterFaz::instance().useMaterial(material_->getProgram());


  //OpenGlInterFaz::instance().useMaterial(*t_mat, vec3(1.0), vec3(1.0), vec3(1.0));
  
}
///////////////////////////////////////////////////
UseMaterialUniformsCommand::UseMaterialUniformsCommand(Material* mat, Material::MaterialSettings *mat_s,
  mat4 projection, mat4 view, mat4 model, std::vector<std::shared_ptr<Light>> lights, Light *dir_light){

  mat_set_ = mat_s;
  mat_ = mat;
  projection = projection_;
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
    OpenGlInterFaz::instance().useDiffuseMaterial(mat_);
    break; 
  default:
    break;
  }
 

}

///////////////////////////////////////////////////

LightsCommand::LightsCommand(std::vector < std::shared_ptr< Light >> l,std::shared_ptr<Light>dir_light){
  lights_ = l;
  dir_light_ = dir_light;
} 

void LightsCommand::runCommand()const{

/*  OpenGlInterFaz::instance().sendLight(dir_light_.get(), 0, true);

  for (int i = 0; i < lights_.size(); i++){ 
      OpenGlInterFaz::instance().sendLight(lights_[i].get(), i, false);
      lights_[i]->setLoaded(true);
  }*/
  
}
/////////////////////////FRAMEBUFFER///////////////////////
UseFrameBuffer::UseFrameBuffer(FrameBuffer *fb){
  frame_buff_ = fb;
}
void UseFrameBuffer::runCommand()const{
  if (!frame_buff_->isLoaded()){
    OpenGlInterFaz::instance().createFrameBuffer(*frame_buff_,true);
    frame_buff_->setLoaded(true);
  }

}



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
    ENGINE.shadow_shader_->setUniformMat4Value("u_model_s",m_);
  }
  else{
    //OpenGlInterFaz::instance().usePointShadowModel(m_);
    ENGINE.shadow_points_shader_->setUniformMat4Value("u_model_sp",m_);
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
 
#include "CDK/directional_light.h"
 void RenderDirectionalShadowMapCommand::runCommand()const{
   
   if (!ENGINE.shadow_shader_->is_compiled_){
     ENGINE.shadow_shader_->setProgram(OpenGlInterFaz::instance().loadMaterial(ENGINE.shadow_shader_.get() ));
     ENGINE.shadow_shader_->is_compiled_ = true;
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
       OpenGlInterFaz::instance().setDrawBuffer(light_depth_map->getId());
       OpenGlInterFaz::instance().setReadBuffer(light_depth_map->getId());
       light_depth_map->setLoaded(true);
     }


     glViewport(0, 0, 1024, 1024);
     glBindFramebuffer(GL_FRAMEBUFFER, dr_light->getShadowMap()->getId());
   //  OpenGlInterFaz::instance().renderShadows(ENGINE.shadow_shader_->getProgram(), dr_light->getLightProyection());
     OpenGlInterFaz::instance().useShadowMapMaterial(ENGINE.shadow_shader_.get(), dr_light->getLightProyection());
     glClear(GL_DEPTH_BUFFER_BIT);
     
   }
 }

#include "CDK/point_light.h"

 RenderPointShadowMapCommand::RenderPointShadowMapCommand(Light * l, int face){
   light_ = (PointLight*)l;
   face_ = face;
 }
 void RenderPointShadowMapCommand::runCommand()const{

   if (!ENGINE.shadow_points_shader_->is_compiled_){
     ENGINE.shadow_points_shader_->setProgram(OpenGlInterFaz::instance().loadMaterial(ENGINE.shadow_points_shader_.get()));
     ENGINE.shadow_points_shader_->is_compiled_ = true;
   }

   if (light_->getShadowCubeMapTexture() < 0 && light_->getShadowCubeMapBuffer() < 0){
     OpenGlInterFaz::instance().createShadoCubeMap(light_);
   }
   //
   glViewport(0, 0, 1024, 1024);
   glBindFramebuffer(GL_FRAMEBUFFER,light_->getShadowCubeMapBuffer());
   glClear(GL_DEPTH_BUFFER_BIT);
   glUseProgram(ENGINE.shadow_points_shader_->getProgram());
   std::vector<mat4> s_m = light_->getShadowMatrices();

   for (int i = 0; i < 6; i++){
     OpenGlInterFaz::instance().sendPointLightMatrix(0, i,s_m[i]);
   }

   
   OpenGlInterFaz::instance().sendPointLightFar(light_->getPosition(),25.0f);


 }

