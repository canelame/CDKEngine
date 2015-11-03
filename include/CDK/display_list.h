#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include "glm\glm.hpp"
#include "command.h"
#include <deque>
#include <memory>
#include <vector>
#include "opengl_interfaz.h"
#include "material.h"
#include "buffer.h"
#include "geometry.h"
#include "camera.h"
/**
* command.h
* @author Alejandro Canela Mendez
* @brief This class makes a representation of an abstract DisplayList, we can add commands to the DL, 
* this commands will be executed in render fucntion.
*/

class DrawCommand : public Command{
public:
  DrawCommand(){
   
  }


  void DrawCommand::runCommand(OpenGlInterFaz &in)const{

    in.drawGeometry();
  }

};


class UseGeometryCommand : public Command{
public:
	UseGeometryCommand(std::shared_ptr<Geometry>geo){
    t_geo = geo;
	}
	

	void UseGeometryCommand::runCommand(OpenGlInterFaz &in)const{
    
		in.useGeometry();
	}
private:	
	
  std::shared_ptr<Geometry> t_geo;
};


class LoadGeometryCommand: public Command{
public:	
	LoadGeometryCommand(std::shared_ptr<Geometry> geo){
		t_geo = geo;
	}


	void LoadGeometryCommand::runCommand(OpenGlInterFaz &in)const{
    if (t_geo.get()->getBuffer()->isDirty()){
      std::vector<std::vector<float>>attrib;
      attrib = t_geo.get()->getBuffer()->getAttributes();
      in.loadBuffer(attrib, t_geo.get()->getBuffer()->getIndexes());
      t_geo.get()->getBuffer()->setDirty(false);
      delete_=true;
    }
	}
  
  bool deleted(){ return delete_; }
  void shouldDelete(bool v){ delete_ = v; }
private:
	std::shared_ptr<Geometry> t_geo;
  mutable bool delete_ = false;

};

class LoadMaterialCommand : public Command{
public:
	LoadMaterialCommand(std::shared_ptr<Material> mat){
		t_mat = mat;
	}

 
	void LoadMaterialCommand::runCommand(OpenGlInterFaz &in)const{
	  in.loadMaterial( t_mat->getVertexData().c_str(), t_mat->getFragmentData().c_str() );
	}
  std::shared_ptr<Material>  getMaterial(){ return t_mat; }
private:
	std::shared_ptr<Material> t_mat;

};

class LoadTextureCommand : public Command{
public:
  LoadTextureCommand(std::shared_ptr<Material>mat){
		t_mat =mat;
	}

	void LoadTextureCommand::runCommand(OpenGlInterFaz &in)const{
		in.loadTexture("textures/o.jpg");
    t_mat.get()->getTexture().get()->setLoaded(true);
	}
  std::shared_ptr<Material>  getMaterial(){ return t_mat; }
private:
  std::shared_ptr<Material> t_mat;
  bool delete_ = false;

};

class UseTextureComman : public Command {
public:
	UseTextureComman(std::shared_ptr<Material>mat){
		t_mat = mat;
	}


	void UseTextureComman::runCommand(OpenGlInterFaz &in)const{
		in.useTexture();
	}

	std::shared_ptr<Material> t_mat;
};

class SetupCameraCommand : public Command {
public:
  SetupCameraCommand(std::shared_ptr<Camera>cam){
	 t_cam = std::move(cam);
	}


	void SetupCameraCommand::runCommand(OpenGlInterFaz &in)const{
    in.useUniformMat4("u_model_m", glm::value_ptr(t_cam.get()->getModel() ));
    in.useUniformMat4("u_projection_m", glm::value_ptr(t_cam.get()->getProyection()));
    in.useUniformMat4("u_view_m", glm::value_ptr(t_cam.get()->getModel()));
	}
private:
	std::shared_ptr<Camera> t_cam;

};

class UseMaterialCommand : public Command{
public:
  UseMaterialCommand(std::shared_ptr<Material> mat){
    t_mat = mat;
  }


  void UseMaterialCommand::runCommand(OpenGlInterFaz &in)const{
    in.useMaterial();
    t_mat->is_compiled_ = true;
  }
private:
  std::shared_ptr<Material> t_mat;

};




class DisplayList{
  class UseGeometryCommand;
public:
	friend class OpenGlInterFaz;
  typedef std::shared_ptr<Command> Comm_;
  typedef std::vector < Comm_ > List;

  List listCommand_;
  DisplayList(){
	 
	  interfaz_ = new OpenGlInterFaz();

	  
  }
  ~DisplayList(){}
  int size(){ return 0; }
  void runCommand()const{};

  void add( Comm_ c){
	  listCommand_.push_back(c);
   }

  void execute(){
    
    for (int i = 0; i < listCommand_.size(); ++i){
		listCommand_[i].get()->runCommand(*interfaz_);
    }
   
  }

  void update(){
    LoadMaterialCommand * m_com;
    LoadGeometryCommand  *g_com;
    LoadTextureCommand *t_com;
    //Comm_ *t_com;
    for (int i = 0; i < listCommand_.size(); i++){
        
   
      m_com = dynamic_cast<LoadMaterialCommand*>(listCommand_[i].get());
      g_com = dynamic_cast<LoadGeometryCommand*>(listCommand_[i].get());
      t_com = dynamic_cast<LoadTextureCommand*>(listCommand_[i].get());
        if (m_com != NULL){
          if (m_com->getMaterial()->is_compiled_){
            listCommand_.erase(listCommand_.begin() + i);
          }
          
        }

        if (g_com != NULL){
          if (g_com->deleted()){
            listCommand_.erase(listCommand_.begin() + i);
          }
        }

        if (t_com != NULL){
          if (t_com->getMaterial()->getTexture().get()->getLoaded()){
            listCommand_.erase(listCommand_.begin() + i);
          }
        }

    }
    
  }
private:
	OpenGlInterFaz *interfaz_;
	
};


#endif

	