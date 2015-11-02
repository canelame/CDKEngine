#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include "command.h"
#include <deque>
#include <memory>
#include <vector>
#include "opengl_interfaz.h"
#include "material.h"
#include "buffer.h"
#include "geometry.h"
/**
* command.h
* @author Alejandro Canela Mendez
* @brief This class makes a representation of an abstract DisplayList, we can add commands to the DL, 
* this commands will be executed in render fucntion.
*/



class UseGeometryCommand : public Command{
public:
	UseGeometryCommand(std::shared_ptr<Geometry*>&geo){
		
	}
	void runCommand(OpenGlInterFaz &in)const;

	void UseGeometryCommand::runCommand(OpenGlInterFaz &in){
		in.useGeometry();
	}
private:	
	

};


class LoadGeometryCommand: public Command{
public:	
	LoadGeometryCommand(std::shared_ptr<Geometry*>&geo){
		t_geo = geo;
	}

	void runCommand(OpenGlInterFaz &in)const;
	void LoadGeometryCommand::runCommand(OpenGlInterFaz &in){
		in.useGeometry();
	}
private:
	std::shared_ptr<Geometry*> t_geo;

};

class LoadMaterialCommand : public Command{

	LoadMaterialCommand(std::shared_ptr<Material*>&mat){
		t_mat = std::move(mat);
	}

	void runCommand(OpenGlInterFaz &in)const;
	void LoadMaterialCommand::runCommand(OpenGlInterFaz &in){
		//in.loadMaterial( ( (*t_mat)->getVertexData().c_str(), (*t_mat)->getFragmentData().c_str() );
	}

	std::shared_ptr<Material*> t_mat;

};

class LoadTextureCommand : public Command{
	LoadTextureCommand(std::unique_ptr<Material>mat){
		t_mat = std::move(mat);
	}
	void runCommand(OpenGlInterFaz &in)const;
	void LoadTextureCommand::runCommand(OpenGlInterFaz &in){
		//in.loadTexture();
	}

	std::unique_ptr<Material> t_mat;


};

class UseTextureComman : public Command {

	UseTextureComman(std::unique_ptr<Material>mat){
		t_mat = std::move(mat);
	}

	void runCommand(OpenGlInterFaz &in)const;
	void UseTextureComman::runCommand(OpenGlInterFaz &in){
		in.useTexture();
	}

	std::unique_ptr<Material> t_mat;
};

class  SetupCameraCommand : public Command {

	SetupCameraCommand(std::unique_ptr<Camera>cam){
	 t_cam = std::move(cam);
	}

	void runCommand(OpenGlInterFaz &in)const;
	void SetupCameraCommand::runCommand(OpenGlInterFaz &in){
		
	}

	std::unique_ptr<Camera> t_cam;

};



class UseMaterialCommand : public Command{
	void runCommand(OpenGlInterFaz &in)const;
	void UseMaterialCommand::runCommand(OpenGlInterFaz &in){
		in.useMaterial();
	}

};

class DisplayList{
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

    Comm_ t_com;
    for (int i = 0; i < listCommand_.size(); i++){
      t_com = listCommand_.at(i);
    }

  }
private:
	OpenGlInterFaz *interfaz_;
	
};


#endif

	