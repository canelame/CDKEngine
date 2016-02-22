#include "CDK/display_list.h"
#include "CDK/texture_cache.h"
#include "CDK/texture.h"


DisplayList::DisplayList(){
	interfaz_ = new OpenGlInterFaz();

}
DisplayList::~DisplayList(){
}
void DisplayList::add(Comm_ c){
	listCommand_.push_back(c);
}
void DisplayList::execute(){
	for (int i = 0; i < listCommand_.size(); ++i){
		listCommand_[i].get()->runCommand(*interfaz_);
	}
}

void DisplayList::update(Node *d){
  
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


void UseTextureComman::runCommand(OpenGlInterFaz &in)const{
  int num_diffuse_t = 1;
  int num_specular_t = 1;
  for (int i = 0; i < textures_.size(); i++){ 
    std::shared_ptr<Texture> current_texture = TextureCache::instance().getTexture(textures_[i].c_str());
    if (!current_texture->getLoaded()){
      in.loadTexture(current_texture);
      current_texture->setLoaded(true);
    }
    std::string type;
    std::string type_name = current_texture->getType();
    std::stringstream ssn;
    if (type_name == "diffuse"){
      type = "u_diffuse_texture";
      ssn << num_diffuse_t;
      num_diffuse_t++;
      in.useTexture(program_mat_, i, (type + ssn.str()), current_texture->getID());
     
    }else  if (type_name == "specular"){
        type = "u_specular_texture";
        ssn << num_specular_t;
        num_specular_t++;
        in.useTexture(program_mat_, i, (type + ssn.str()), current_texture->getID());
    }

  }

}

///////// SETUP_CAMERA_COMMAND CLASS/////////////////
////////////////////////////////////////////
SetupCameraCommand::SetupCameraCommand(){

}


void SetupCameraCommand::runCommand(OpenGlInterFaz &in)const{


}
///////// USE_CAMERA_COMMAND CLASS/////////////////
////////////////////////////////////////////
UseCameraCommand::UseCameraCommand(mat4 cam_proyec, mat4 cam_view, mat4 m_m){
  proyec_m_ = cam_proyec;
  view_m_ = cam_view;
  model_n_ = m_m;
}


void UseCameraCommand::runCommand(OpenGlInterFaz &in)const{


  in.useCamera(proyec_m_,model_n_,view_m_);
}

///////// LOAD_TEXTURE_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadTextureCommand::LoadTextureCommand(std::shared_ptr<Material::MaterialSettings>mat){
	t_mat = mat;
}

void LoadTextureCommand::runCommand(OpenGlInterFaz &in)const{
  for (int i = 0; i < t_mat->totalTextures(); i++){
      in.loadTexture(TextureCache::instance().getTexture(t_mat->getTextureAt(i)));
      TextureCache::instance().getTexture(t_mat->getTextureAt(i))->setLoaded(true);
  }

}
std::shared_ptr<Material::MaterialSettings>  LoadTextureCommand::getMaterial(){
	return t_mat;
}

///////// LOAD_MATERIAL_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadMaterialCommand::LoadMaterialCommand(std::shared_ptr<Material> mat){
	t_mat = mat;
}
void LoadMaterialCommand::runCommand(OpenGlInterFaz &in)const{
	in.loadMaterial(t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str());
	t_mat->is_compiled_ = true;
}

std::shared_ptr<Material>  LoadMaterialCommand::getMaterial(){ 
	return t_mat; 
}

///////// LOAD_GEO_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadGeometryCommand::LoadGeometryCommand(std::shared_ptr<Geometry> geo){

		t_geo = geo;
}
void LoadGeometryCommand::runCommand(OpenGlInterFaz &in)const{



}
bool LoadGeometryCommand::deleted(){
	return delete_;
}
void LoadGeometryCommand::shouldDelete(bool v){
	delete_ = v;
}

///////// USE_GEOMETRY CLASS/////////////////
////////////////////////////////////////////
UseGeometryCommand::UseGeometryCommand(std::shared_ptr<Buffer>geo){

		t_geo = geo;

}


void UseGeometryCommand::runCommand(OpenGlInterFaz &in)const{
  if (t_geo->isDirty() && t_geo!=nullptr){
    in.loadBuffer(t_geo);
    t_geo->setDirty(false);
    vao_ = *t_geo->getVAO();

  }
  in.useGeometry(*t_geo->getVAO());


}

///////// DRAW_COMMAND CLASS/////////////////
////////////////////////////////////////////
DrawCommand::DrawCommand(std::shared_ptr<Buffer>g){
	
		t_geo = g;

    indices_size_ = t_geo->indiceSize();

}

void DrawCommand::runCommand(OpenGlInterFaz &in)const{

  in.drawGeometry(indices_size_);

}

///////// USE_MATERIAL_COMMAND CLASS/////////
////////////////////////////////////////////
UseMaterialCommand::UseMaterialCommand(std::shared_ptr<Material> mat, std::shared_ptr<Material::MaterialSettings>mt_S){
	t_mat = mat;
  mat_set_ = mt_S;

}

void UseMaterialCommand::runCommand(OpenGlInterFaz &in)const{
  if (!t_mat->is_compiled_){

   t_mat->setProgram( in.loadMaterial( t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str()));
   for (int i = 0; i < 10; i++){
     in.loadLight(i);
   }
   in.loadCamera();
    t_mat->is_compiled_ = true;
  }
  in.useMaterial(*t_mat.get(),mat_set_->ambient_color_,mat_set_->diffuse_color_,mat_set_->specular_color_);

}


LightsCommand::LightsCommand(std::vector<std::shared_ptr<Light>>l){
  lights_ = l;

}

void LightsCommand::runCommand(OpenGlInterFaz &in)const{
  for (int i = 0; i < lights_.size(); i++){
    in.sendLight(lights_[i].get());

  }
  
}
/////////////////////////FRAMEBUFFER///////////////////////
UseFrameBuffer::UseFrameBuffer(){

}
void UseFrameBuffer::runCommand(OpenGlInterFaz &in)const{
  if (!frame_buff_->isLoaded()){
    frame_buff_->getTexture().loadTexture("", "fb");
    in.createFrameBuffer(*frame_buff_.get());
    frame_buff_->setLoaded(true);
  }
}
