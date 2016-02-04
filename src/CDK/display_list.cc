#include "CDK/display_list.h"

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
UseTextureComman::UseTextureComman(std::shared_ptr<Material>mat){
	t_mat = mat;
}


void UseTextureComman::runCommand(OpenGlInterFaz &in)const{
  int num_diffuse_t = 1;
  int num_specular_t = 1;
  for (int i = 0; i < t_mat->totalTextures(); i++){ 
    if (!t_mat->getTextureAt(i)->getLoaded()){
      in.loadTexture(t_mat->getTextureAt(i));
      t_mat->getTextureAt(i)->setLoaded(true);
    }
    std::string type;
    std::string type_name = t_mat->getTextureAt(i)->getType();
    std::stringstream ssn;
    if (type_name == "diffuse"){
      type = "u_diffuse_texture";
      ssn << num_diffuse_t;
      num_diffuse_t++;
      in.useTexture(t_mat->getProgram(), t_mat->getTextureAt(i), i, (type+ssn.str()));
    }else  if (type_name == "specular"){
        type = "u_specular_texture";
        ssn << num_specular_t;
        num_specular_t++;
        in.useTexture(t_mat->getProgram(), t_mat->getTextureAt(i), i,(type+ssn.str()) );
    }

  }

}

///////// SETUP_CAMERA_COMMAND CLASS/////////////////
////////////////////////////////////////////
SetupCameraCommand::SetupCameraCommand(mat4 cam_proyec,mat4 cam_view,mat4 m_m){
  proyec_m_ = cam_proyec;
  view_m_ = cam_view;
	model_n_=m_m;
}


void SetupCameraCommand::runCommand(OpenGlInterFaz &in)const{

	in.useUniformMat4("u_projection_m", glm::value_ptr(proyec_m_));
	in.useUniformMat4("u_view_m", glm::value_ptr(view_m_));
	in.useUniformMat4("u_model_m", glm::value_ptr(model_n_));

}

///////// LOAD_TEXTURE_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadTextureCommand::LoadTextureCommand(std::shared_ptr<Material>mat){
	t_mat = mat;
}

void LoadTextureCommand::runCommand(OpenGlInterFaz &in)const{
  for (int i = 0; i < t_mat->totalTextures(); i++){
      in.loadTexture(t_mat->getTextureAt(i));
      t_mat->getTextureAt(i)->setLoaded(true);
  }
  t_mat.~shared_ptr();
}
std::shared_ptr<Material>  LoadTextureCommand::getMaterial(){
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
///////// SET_MODEL_COMMAND CLASS/////////////////
////////////////////////////////////////////

SetModelMatrixCommand::SetModelMatrixCommand(std::shared_ptr<Geometry>geo){

		t_geo = geo;

}
void SetModelMatrixCommand::runCommand(OpenGlInterFaz &in)const{


	in.useUniformMat4("u_model_m", glm::value_ptr(t_geo.get()->getModel()));

}
///////// USE_GEOMETRY CLASS/////////////////
////////////////////////////////////////////
UseGeometryCommand::UseGeometryCommand(std::shared_ptr<Geometry>geo){

		t_geo = geo;

}


void UseGeometryCommand::runCommand(OpenGlInterFaz &in)const{
  if (t_geo.get()->getBuffer()->isDirty()){
    in.loadBuffer(t_geo->getBuffer());
    t_geo->getBuffer()->setDirty(false);
    vao_ = *t_geo->getBuffer()->getVAO();

  }
  in.useGeometry(*t_geo->getBuffer()->getVAO());


}

///////// DRAW_COMMAND CLASS/////////////////
////////////////////////////////////////////
DrawCommand::DrawCommand(std::shared_ptr<Geometry>g){
	
		t_geo = g;

    indices_size_ = t_geo.get()->getBuffer()->getSizes()[5];

}

void DrawCommand::runCommand(OpenGlInterFaz &in)const{

  in.drawGeometry(indices_size_);

}

///////// USE_MATERIAL_COMMAND CLASS/////////
////////////////////////////////////////////
UseMaterialCommand::UseMaterialCommand(std::shared_ptr<Material> mat){
	t_mat = mat;
}

void UseMaterialCommand::runCommand(OpenGlInterFaz &in)const{
  if (!t_mat->is_compiled_){
   t_mat->setProgram( in.loadMaterial( t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str()));
    t_mat->is_compiled_ = true;
  }
	in.useMaterial(t_mat->getProgram());
  float color[] = {t_mat->getColor().x,t_mat->getColor().y,t_mat->getColor().z};

  in.useUnifor3f("diffuse_color", color);


}


LightsCommand::LightsCommand(std::vector<std::shared_ptr<Light>>l){
  lights_ = l;

}

void LightsCommand::runCommand(OpenGlInterFaz &in)const{
  for (int i = 0; i < lights_.size(); i++){
    in.sendLight(lights_[i].get(), i);
  }
}