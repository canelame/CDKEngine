/**
@author Alejandro Canela Mendez
ESAT 2016.
*/
///////////////////////////////////////// THIS PART OF FILE , MANAGE DIFERENT CLASSES OF TYPE COMMANDS, THAT REPRESENTS THE ///////////////////////////////////////////// 
///////////////////////////////////////// DISPLAY LIST TASK. ONLY PROGRAM PORPOUSE. NOT FOR THE USER OF LIBRARY             /////////////////////////////////////////////


///DRAW COMMAND CLASS
#ifndef __H_DRAW_COMMAND__
#define __H_DRAW_COMMAND__
#include "command.h"
#include "opengl_interfaz.h"
#include "geometry.h"
class DrawCommand : public Command{
public:
	DrawCommand(std::shared_ptr<Buffer> g);
	void runCommand(OpenGlInterFaz &in)const;
private:
  std::shared_ptr<Buffer> t_geo;
  int indices_size_;
};
#endif
///USE GEOMETRY COMMAND CLASS
#ifndef __H_USE_GEO_COMMAND__
#define __H_USE_GEO_COMMAND__
#include "command.h"
#include "geometry.h"
#include "opengl_interfaz.h"
class UseGeometryCommand : public Command{
public:
	UseGeometryCommand(std::shared_ptr<Buffer>geo);
	void runCommand(OpenGlInterFaz &in)const;
private:	
	
  std::shared_ptr<Buffer> t_geo;
  mutable GLuint vao_;
};
#endif

///LOAD GEOMTRY COMMAND CLASS

#ifndef __H_LOAD_GEO_COMMAND__
#define __H_LOAD_GEO_COMMAND__
#include "command.h"
#include "geometry.h"
#include "opengl_interfaz.h"
class LoadGeometryCommand: public Command{
public:	
	LoadGeometryCommand(std::shared_ptr<Geometry> geo);


	void runCommand(OpenGlInterFaz &in)const;
  
	bool deleted();
	void shouldDelete(bool v);
private:
	std::shared_ptr<Geometry> t_geo;
  mutable bool delete_ = false;

};
#endif

///USE LIGHT COMMAND CLASS
#ifndef __H_LIGHTS_COMMAND__
#define __H_LIGHTS_COMMAND__  
#include "command.h"
#include "light.h"
#include <vector>
#include "opengl_interfaz.h"
class LightsCommand : public Command{
public:
  LightsCommand(std::vector<std::shared_ptr< Light>> geo);


  void runCommand(OpenGlInterFaz &in)const;


private:
  mutable std::vector<std::shared_ptr< Light>> lights_;

};
#endif
///LOAD MATERIAL COMMMAND CLASS
#ifndef __H_LOAD_MAT_COMMAND__
#define __H_LOAD_MAT_COMMAND__
#include "command.h"
#include "material.h"
#include "opengl_interfaz.h"
class LoadMaterialCommand : public Command{
public:
	LoadMaterialCommand(std::shared_ptr<Material> mat);
	void runCommand(OpenGlInterFaz &in)const;
	std::shared_ptr<Material>  getMaterial();
private:
	std::shared_ptr<Material> t_mat;

};
#endif
///LOAD TEXTURE COMMAND CLASS
#ifndef __H_LOAD_TEXTURE_COMMAND__
#define __H_LOAD_TEXTURE_COMMAND__
#include "command.h"
#include "material.h"
#include "opengl_interfaz.h"

class LoadTextureCommand : public Command{
public:
	LoadTextureCommand(std::shared_ptr<Material::MaterialSettings>mat);
	void runCommand(OpenGlInterFaz &in)const;
	std::shared_ptr<Material::MaterialSettings>  getMaterial();
private:
	 std::shared_ptr<Material::MaterialSettings> t_mat;
	 bool delete_ = false;

};
#endif
//USE TEXTURE COMMAND CLASS
#ifndef __H_USE_TEXTURE_COMMAND__
#define __H_USE_TEXTURE_COMMAND__
#include "command.h"
#include "material.h"
#include "opengl_interfaz.h"
class UseTextureComman : public Command {
public:
	UseTextureComman(int pro,std::vector<std::string>textures);
	void runCommand(OpenGlInterFaz &in)const;
private:
  std::vector<std::string> textures_;
  int program_mat_;
};
#endif
/// SETUP CAMERA COMMAND CLASS
#ifndef __H_SETUP_CAM_COMMAND__
#define __H_SETUP_CAM_COMMAND__
#include "command.h"
#include "camera.h"
#include "opengl_interfaz.h"
class SetupCameraCommand : public Command {
public:
  SetupCameraCommand();
  void runCommand(OpenGlInterFaz &in)const;
private:

};
#endif
/// USE CAMERA COMMAND CLASS
#ifndef __H_USE_CAM_COMMAND__
#define __H_USE_CAM_COMMAND__
#include "command.h"
#include "camera.h"
#include "opengl_interfaz.h"
class UseCameraCommand : public Command {
public:
  UseCameraCommand(mat4 cam_proyec, mat4 cam_view, mat4 m_mm);
  void runCommand(OpenGlInterFaz &in)const;
private:
  mat4 proyec_m_;
  mat4 view_m_;
  mat4 model_n_;
  
};
#endif
///USE MATERIAL COMMAND CLASS
#ifndef __H_USE_MATERIAL_COMMAND__
#define __H_USE_MATERIAL_COMMAND__
#include "command.h"
#include "material.h"
#include "opengl_interfaz.h"
class UseMaterialCommand : public Command{
public:
	UseMaterialCommand(std::shared_ptr<Material> mat,std::shared_ptr<Material::MaterialSettings> mt_s);
	void runCommand(OpenGlInterFaz &in)const;
private:
  std::shared_ptr<Material::MaterialSettings> mat_set_;
  std::shared_ptr<Material> t_mat;
  mutable const char* v_data;
  mutable const char* f_data;

};
#endif

/////////////////////////////////////////////////// END OF DISPLAY LIST TASK HEADER //////////////////////////////


/////////////////////////////////////////////////// START DISPLAY CLASS///////////////////////////////////////////
#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include "command.h"
#include <memory>
#include <vector>

/**
* command.h
* @author Alejandro Canela Mendez
* @brief This class makes a representation of an abstract DisplayList, we can add commands to the DL,
* this commands will be executed in render fucntion.
*/

class DisplayList{
 //private funtions
  ///Draw Command variable
  unsigned int indices_size_;
  unsigned int vao_;

public:
  friend class OpenGlInterFaz;
  typedef std::shared_ptr<Command> Comm_;
  typedef std::vector < Comm_ > List;

  DisplayList();
	/**
	*
	*/
  ~DisplayList();
	/**
	* @brief Returns the size of the display list
	* @return Size of display list.
	*/
  int size();
	/**
	* @brief Add a command to display list.
	* @param c The coomand to add.
	*/
  void add(Comm_ c);
	/**
	* @brief Execute display list
	*/
  void execute();
	/**
	* @param  Update the display list.
	*/
  void update(Node*dr);
  /**
  *@brief Clean commands list
  * @param  Update the display list.
  */
  void clear();
private:

	OpenGlInterFaz *interfaz_;

	List listCommand_;

};


#endif

	