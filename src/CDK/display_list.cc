#include "CDK/display_list.h"
#include "CDK/texture_cache.h"
#include "CDK/texture.h"
#include "CDK/engine_manager.h"


DisplayList::DisplayList(){

}
DisplayList::~DisplayList(){
}
void DisplayList::add(Comm_ c){
	listCommand_.push_back(c);
  
}
void DisplayList::execute(){

 
   
  

	for (int i = 0; i < listCommand_.size(); ++i){
    listCommand_[i]->runCommand();
	}


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
  OpenGlInterFaz::instance().drawGeometry(*t_geo->getVAO(), indices_size_);

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


LightsCommand::LightsCommand(std::vector<Light*>l){
  lights_ = l;

} 

void LightsCommand::runCommand()const{
  for (int i = 0; i < lights_.size(); i++){
    OpenGlInterFaz::instance().sendLight(lights_[i], i);

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
