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

void DisplayList::update(){
	LoadMaterialCommand  *l_m_com;
	LoadGeometryCommand  *l_g_com;
	LoadTextureCommand *l_t_com;
	SetupCameraCommand *l_c_com;


	//Comm_ *t_com;
	for (int i = 0; i < listCommand_.size(); i++){


		//l_m_com = std::dynamic_pointer_cast<std::shared_ptr<LoadMaterialCommand>>(listCommand_[i].get());

		l_g_com = dynamic_cast<LoadGeometryCommand*>(listCommand_[i].get());
		l_m_com = dynamic_cast<LoadMaterialCommand*>(listCommand_[i].get());
		l_t_com = dynamic_cast<LoadTextureCommand*>(listCommand_[i].get());
	//	l_c_com = dynamic_cast<SetupCameraCommand*>(listCommand_[i].get());
		// l_c_com = std::make_shared<SetupCameraCommand>(listCommand_[i]);


		if (l_m_com != NULL){
			if (l_m_com->getMaterial()->is_compiled_){
				listCommand_.erase(listCommand_.begin() + i);
			}

		}

		if (l_g_com != NULL){
			if (l_g_com){
				listCommand_.erase(listCommand_.begin() + i);
			}
		}

		if (l_t_com != NULL){
			if (l_t_com->getMaterial()->getTexture().get()->getLoaded()){
				listCommand_.erase(listCommand_.begin() + i);
			}
		}

	}

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

	in.useTexture(t_mat);
}

///////// SETUP_CAMERA_COMMAND CLASS/////////////////
////////////////////////////////////////////
SetupCameraCommand::SetupCameraCommand(std::shared_ptr<Camera>cam,mat4 m_m){
	t_cam = std::move(cam);
	model_n_=m_m;
}


void SetupCameraCommand::runCommand(OpenGlInterFaz &in)const{

	
	/*glm::mat4 temp_model;
	temp_model = glm::rotate(temp_model, rot_.x, vec3(1.0, 0.0, 0.0));
	temp_model = glm::rotate(temp_model, rot_.y, vec3(0.0, 1.0, 0.0));
	temp_model = glm::rotate(temp_model, rot_.z, vec3(0.0, 0.0, 1.0));
	temp_model = glm::scale(temp_model, scal_);
	temp_model = glm::translate(temp_model, pos_);
	temp_model = model_n_ * temp_model;*/

	in.useUniformMat4("u_projection_m", glm::value_ptr(t_cam.get()->getProyection()));
	in.useUniformMat4("u_view_m", glm::value_ptr(t_cam.get()->getView()));
	in.useUniformMat4("u_model_m", glm::value_ptr(model_n_));

}

///////// LOAD_TEXTURE_COMMAND CLASS/////////////////
////////////////////////////////////////////
LoadTextureCommand::LoadTextureCommand(std::shared_ptr<Material>mat){
	t_mat = mat;
}

void LoadTextureCommand::runCommand(OpenGlInterFaz &in)const{
	in.loadTexture(t_mat);
	t_mat.get()->getTexture().get()->setLoaded(true);
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

		if (t_geo.get()->getBuffer()->isDirty()){
			std::vector<std::vector<float>>attrib;
      attrib = t_geo.get()->getBuffer()->getAttributes();
      in.loadBuffer(t_geo->getBuffer());
     t_geo.get()->getBuffer()->setDirty(true);
			delete_ = true;
			t_geo->setMes(t_geo->numMes() + 1);
		}
	t_geo->setMes(0);
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

  in.useGeometry(*t_geo.get()->getBuffer()->getVAO());


}

///////// DRAW_COMMAND CLASS/////////////////
////////////////////////////////////////////
DrawCommand::DrawCommand(std::shared_ptr<Geometry>g){
	
		t_geo = g;



}

void DrawCommand::runCommand(OpenGlInterFaz &in)const{

  in.drawGeometry(t_geo.get()->getBuffer()->getIndexes());

}

///////// USE_MATERIAL_COMMAND CLASS/////////
////////////////////////////////////////////
UseMaterialCommand::UseMaterialCommand(std::shared_ptr<Material> mat){
	t_mat = mat;
}

void UseMaterialCommand::runCommand(OpenGlInterFaz &in)const{
	in.useMaterial();
}