#include "CDK/display_list.h"
#include "CDK/texture_cache.h"

#include "CDK/engine_manager.h"


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
LoadTextureCommand::LoadTextureCommand(Material::MaterialSettings *mat){
	t_mat = mat;
}

void LoadTextureCommand::runCommand()const{
  for (int i = 0; i < t_mat->totalTextures(); i++){
    OpenGlInterFaz::instance().loadTexture(TextureCache::instance().getTexture(t_mat->getTextureAt(i)));
      TextureCache::instance().getTexture(t_mat->getTextureAt(i))->setLoaded(true);
  }

}
Material::MaterialSettings*  LoadTextureCommand::getMaterial(){
	return t_mat;
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
  OpenGlInterFaz::instance().drawGeometry(t_geo->getVAO(), indices_size_);

}

///////// USE_MATERIAL_COMMAND CLASS/////////
////////////////////////////////////////////
UseMaterialCommand::UseMaterialCommand(Material* mat, Material::MaterialSettings *mt_S){
	t_mat = mat;
  mat_set_ = mt_S;

}

void UseMaterialCommand::runCommand()const{
  if (!t_mat->is_compiled_){

    t_mat->setProgram(OpenGlInterFaz::instance().loadMaterial(t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str()));
    for (int i = 0; i < 10; i++){
      OpenGlInterFaz::instance().loadLight(i);
    }
    t_mat->is_compiled_ = true;
  }
    OpenGlInterFaz::instance().useMaterial(*t_mat, mat_set_->ambient_color_, mat_set_->diffuse_color_, mat_set_->specular_color_);
  
}


LightsCommand::LightsCommand(std::vector < std::shared_ptr< Light >> l){
  lights_ = l;

} 

void LightsCommand::runCommand()const{
  for (int i = 0; i < lights_.size(); i++){
    OpenGlInterFaz::instance().sendLight(lights_[i].get(), i);

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
StartShadowCommand::StartShadowCommand(std::shared_ptr<Light> lights){
  depth_buffer_ = std::make_shared<FrameBuffer>();
  depth_buffer_->setAttachment(FrameBuffer::kFrameBufferAttachment::kFrameBufferAttachment_DepthAttachment);
  shadow_shader_ = std::make_shared<Material>();
  shadow_shader_->loadShader("shaders/shadow_v.glsl", "shaders/shadow_f.glsl");
  lights_ = lights;
}

void StartShadowCommand::runCommand()const{

    if (lights_->getType() == Light::LightType::T_DIRECTION_LIGHT){

      if (!depth_buffer_->isLoaded()){
        Texture  * d_texture = depth_buffer_->getTexture().get();
        d_texture->setFormat(Texture::kTextureFormat::kTextureFormat_Depth);
        d_texture->setPixelType(Texture::kTexturePixelType::kTexturePixelType_Float);
        d_texture->setMagFilter(Texture::kTextureFiltering::kTextureFiltering_Nearest);
        d_texture->setMinFilter(Texture::kTextureFiltering::kTextureFiltering_Nearest);
        d_texture->setWrapCoordinateS(Texture::kTextureWrapping::kTextureWrapping_Repeat);
        d_texture->setWrapCoordinateT(Texture::kTextureWrapping::kTextureWrapping_Repeat);
        OpenGlInterFaz::instance().createFrameBuffer(*depth_buffer_.get(), false);
        OpenGlInterFaz::instance().setDrawBuffer(depth_buffer_->getId());
        OpenGlInterFaz::instance().setReadBuffer(depth_buffer_->getId());
      }

      mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
      mat4 light_view = glm::lookAt(lights_->getPosition(), vec3(0.0), vec3(0.0));
      mat4 light_space = light_projection * light_view;
      OpenGlInterFaz::instance().renderShadows(shadow_shader_->getProgram(),light_space);
      glViewport(0, 0, 1024, 1024);
      OpenGlInterFaz::instance().bindFrameBuffer(depth_buffer_->getId(), FrameBuffer::kFramebufferBindType::kFramebufferBindType_FrameBuffer);
      glClear(GL_DEPTH_BUFFER_BIT);
    }
}

void DisplayList::renderScene(){

  for (int i = 0; i < listCommand_.size(); ++i){
    listCommand_[i]->runCommand();
  }
}


SendObjectShadow::SendObjectShadow(mat4 m){
  m_ = m;
}

void SendObjectShadow::runCommand()const{
  OpenGlInterFaz::instance().useUniformMat4(m_);
}