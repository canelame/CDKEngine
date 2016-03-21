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
	DrawCommand(Buffer* g);
	void runCommand()const;
private:
  Buffer *t_geo;
  int indices_size_;
  GLuint vao_;
};
#endif


///SHADOWS COMMAND CLASS

#ifndef __H_SHADOW_COMMAND__
#define __H_SHADOW_COMMAND__
class StartShadowCommand : public Command{
public:
  StartShadowCommand(std::shared_ptr<Light> lights);

  StartShadowCommand(){}
  void runCommand()const;
private:
 std::shared_ptr<Light> lights_;
  std::shared_ptr<FrameBuffer> depth_buffer_;
  std::shared_ptr<Material> shadow_shader_;
};

#endif
//
#ifndef __H_SEND_OBJECT_SHADOW__
#define __H_SEND_OBJECT_SHADOW__
class SendObjectShadow : public Command{
public:
  SendObjectShadow(mat4 m);

  SendObjectShadow(){}
  void runCommand()const;
private:
  mat4 m_;
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
  LightsCommand(std::vector<std::shared_ptr<Light>> geo);


  void runCommand()const;


private:
  mutable std::vector<std::shared_ptr<Light>> lights_;

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
	LoadMaterialCommand(Material* mat);
	void runCommand()const;
	Material*  getMaterial();
private:
	Material *t_mat;

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
	LoadTextureCommand(Material::MaterialSettings *mat);
	void runCommand()const;
	Material::MaterialSettings* getMaterial();
private:
	 Material::MaterialSettings *t_mat;
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
	void runCommand()const;
private:
  std::vector<std::string> textures_;
  int program_mat_;
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
  void runCommand()const;
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
	UseMaterialCommand(Material* mat,Material::MaterialSettings *mt_s);
  UseMaterialCommand(){}
	void runCommand()const;
private:
  Material::MaterialSettings *mat_set_;
  Material *t_mat;
  mutable const char* v_data;
  mutable const char* f_data;

};
#endif
//////////////////////////////////
#ifndef __H_USE_FRAME_BUFFER__
#define __H_USE_FRAME_BUFFER__
#include "command.h"
#include "frame_buffer.h"
#include "opengl_interfaz.h"
class UseFrameBuffer : public Command{
public:
  UseFrameBuffer(FrameBuffer *fb);
  void runCommand()const;
private:
  FrameBuffer* frame_buff_;


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
  *@brief Clean commands list
  * @param  Update the display list.
  */
  void clear();
private:
  void renderScene();

  std::shared_ptr<FrameBuffer> current_framebuffer_;

	List listCommand_;
  List shadowList_;

};


#endif

	