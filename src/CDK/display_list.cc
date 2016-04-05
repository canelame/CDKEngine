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
  int num_diffuse_t = 1;
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

  }

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
  OpenGlInterFaz::instance().loadMaterial(t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str());
	t_mat->is_compiled_ = true;
}

Material*  LoadMaterialCommand::getMaterial(){ 
	return t_mat; 
}

///////// DRAW_COMMAND CLASS/////////////////
////////////////////////////////////////////
DrawCommand::DrawCommand(Buffer *g){
	
		t_geo = g;
    vao_ =(GLuint) t_geo->getVAO();
    indices_size_ = t_geo->indiceSize();

}

void DrawCommand::runCommand()const{
  if (t_geo->isDirty() && t_geo != nullptr){
    OpenGlInterFaz::instance().loadBuffer(t_geo);
    t_geo->setDirty(false);
  }
  OpenGlInterFaz::instance().drawGeometry(vao_, indices_size_);

}

///////// USE_MATERIAL_COMMAND CLASS/////////
////////////////////////////////////////////
UseMaterialCommand::UseMaterialCommand(Material* mat){
	t_mat = mat;
 

}

void UseMaterialCommand::runCommand()const{
  if (!t_mat->is_compiled_){

    t_mat->setProgram(OpenGlInterFaz::instance().loadMaterial(t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str()));
    for (int i = 0; i < 10; i++){
      OpenGlInterFaz::instance().loadLight(i);
    }
    OpenGlInterFaz::instance().loadDirectionalLight();
    t_mat->is_compiled_ = true;
  }
  OpenGlInterFaz::instance().useMaterial(*t_mat, vec3(1.0), vec3(1.0), vec3(1.0));
  
}


LightsCommand::LightsCommand(std::vector < std::shared_ptr< Light >> l,std::shared_ptr<Light>dir_light){
  lights_ = l;
  dir_light_ = dir_light;
} 

void LightsCommand::runCommand()const{


  if (!dir_light_->getLoaded()) {
    OpenGlInterFaz::instance().sendLight(dir_light_.get(), 0, true);
    dir_light_->setLoaded(true);
  }

  for (int i = 0; i < lights_.size(); i++){
    if (!lights_[i]->getLoaded()){
      OpenGlInterFaz::instance().sendLight(lights_[i].get(), i, false);
      lights_[i]->setLoaded(true);
    }
  }
  
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

//SHAdow class
StartShadowCommand::StartShadowCommand(int depth_program,int depth_fb,std::shared_ptr<Light> lights){
  shader_program_ = depth_program;
  lights_ = lights;
  fb_id_ = depth_fb;
}

void StartShadowCommand::runCommand()const{

  if (!ENGINE.shadow_depth_buffer_->isLoaded()){

    Texture  * d_texture = ENGINE.shadow_depth_buffer_->getTexture().get();
    d_texture->setFormat(Texture::kTextureFormat::kTextureFormat_Depth);
    d_texture->setPixelType(Texture::kTexturePixelType::kTexturePixelType_Float);
    d_texture->setMagFilter(Texture::kTextureFiltering::kTextureFiltering_Nearest);
    d_texture->setMinFilter(Texture::kTextureFiltering::kTextureFiltering_Nearest);
    d_texture->setWrapCoordinateS(Texture::kTextureWrapping::kTextureWrapping_Clamp_Border);
    d_texture->setWrapCoordinateT(Texture::kTextureWrapping::kTextureWrapping_Clamp_Border);
    OpenGlInterFaz::instance().createFrameBuffer(*ENGINE.shadow_depth_buffer_.get(), false);
    OpenGlInterFaz::instance().setDrawBuffer(ENGINE.shadow_depth_buffer_->getId());
    OpenGlInterFaz::instance().setReadBuffer(ENGINE.shadow_depth_buffer_->getId());
    OpenGlInterFaz::instance().createFrameBuffer(*ENGINE.shadow_depth_buffer_.get(), true);
    // EngineManager::instance().setRenderTarget(frame_buff_.get());
    EngineManager::instance().depth_texture_id_ = d_texture->getID();
    ENGINE.shadow_depth_buffer_->setLoaded(true);
  }

  if (!ENGINE.shadow_shader_->is_compiled_){
    ENGINE.shadow_shader_->setProgram(OpenGlInterFaz::instance().loadMaterial(ENGINE.shadow_shader_->getVertexData().c_str(), ENGINE.shadow_shader_->getFragmentData().c_str()));
    ENGINE.shadow_shader_->is_compiled_ = true;
  }

  OpenGlInterFaz::instance().renderShadows(ENGINE.shadow_shader_->getProgram());
  glViewport(0, 0, 1024, 1024);
  glBindFramebuffer(GL_FRAMEBUFFER, ENGINE.shadow_depth_buffer_->getId());// , FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
  glClear(GL_DEPTH_BUFFER_BIT);
  glCullFace(GL_FRONT);
      
    //}
}

void DisplayList::renderScene(){

  for (int i = 0; i < listCommand_.size(); ++i){
    listCommand_[i]->runCommand();
  }
}


SendObjectShadow::SendObjectShadow(Buffer * g,mat4 m){
  m_ = m;
  t_geo = g;
}

void SendObjectShadow::runCommand()const{
  OpenGlInterFaz::instance().useUniformMat4(m_);
  if (t_geo->isDirty()){
    OpenGlInterFaz::instance().loadBuffer(t_geo);
    t_geo->setDirty(false);
   }
  OpenGlInterFaz::instance().drawGeometry(t_geo->getVAO(), (unsigned int)t_geo->indiceSize());
}

 EndShadowCommand::EndShadowCommand(){}
 void EndShadowCommand::runCommand()const{
   glCullFace(GL_BACK);
   OpenGlInterFaz::instance().bindFrameBuffer(0, FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
   glViewport(0,0,1024, 1024);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 }