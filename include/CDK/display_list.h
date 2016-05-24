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
  int vao_;
};
#endif


///SHADOWS COMMAND CLASS



///SHADOWS COMMAND CLASS

#ifndef __H_SHADOW_END_COMMAND__
#define __H_SHADOW_END_COMMAND__
class EndShadowCommand : public Command{
public:
  EndShadowCommand();
 
  void runCommand()const;
private:


};
#ifndef __H_SHADOW_CUBE_END_COMMAND__
#define __H_SHADOW_CUBE_END_COMMAND__
class EndShadowCubeMapCommand : public Command{
public:
  EndShadowCubeMapCommand();

  void runCommand()const;
private:


};
#endif
#endif


#ifndef __RENDER_SHADOW_MAP__
#define __RENDER_SHADOW_MAP__

class RenderDirectionalShadowMapCommand : public Command{
public:
  RenderDirectionalShadowMapCommand(Light * l);
  Light *light_;
  void runCommand()const;
  void useMaterial();
private:


};
#endif

#ifndef __RENDER_POINT_SHADOW_MAP__
#define __RENDER_POINT_SHADOW_MAP__

class RenderPointShadowMapCommand : public Command{
public:
  RenderPointShadowMapCommand(Light * l, int face);
  PointLight *light_;
  void runCommand()const;
private:
  int face_;

};
#endif

#ifndef __RENDER_SPOT_SHADOW_MAP__
#define __RENDER_SPOT_SHADOW_MAP__
#include "spot_light.h"
class RenderSpotShadowMapCommand : public Command{
public:
  RenderSpotShadowMapCommand(Light * l, int face);
  SpotLight *light_;
  void runCommand()const;
private:


};
#endif

//
#ifndef __H_SEND_OBJECT_SHADOW__
#define __H_SEND_OBJECT_SHADOW__
class SendObjectShadow : public Command{
public:
  SendObjectShadow(Buffer *g,mat4 m,bool is_directional);

  SendObjectShadow(){}
  void runCommand()const;
private:
  mat4 m_;
  mutable  Buffer* t_geo;
  bool is_directional_;
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
	UseMaterialCommand(Material *mat);
  UseMaterialCommand(){}
	void runCommand()const;
private:
  Material *material_;

};
#endif

#ifndef __H_USE_MATERIAL_UNIFORMS_COMMAND__
#define __H_USE_MATERIAL_UNIFORMS_COMMAND__
#include "command.h"
#include "material.h"
#include "opengl_interfaz.h"
class UseMaterialUniformsCommand : public Command{
public:
  UseMaterialUniformsCommand( Material* mat,Material::MaterialSettings *mat_s,
    mat4 projection,mat4 view,mat4 model, std::vector<std::shared_ptr<Light>> geo, Light *dir_light);
  UseMaterialUniformsCommand(){}
  void runCommand()const;
private:
  Material::MaterialSettings *mat_set_;
  Material * mat_;
  Light*  dir_light_;
  mat4 projection_;
  mat4 model_;
  mat4 view_;
  std::vector<std::shared_ptr<Light>> lights_;


};

#endif

#ifndef __H_BEGIN_POSTPROCESS__
#define __H_BEGIN_POSTPROCESS__
#include "command.h"
#include "../post_process.h"
#include "opengl_interfaz.h"
class PostProcessBegin : public Command{
public:
  PostProcessBegin(FrameBuffer* fb,PostProcess * mat);
  PostProcessBegin();
  void runCommand()const;
private:

  FrameBuffer *fb_ptr_;
  PostProcess * post_p_;
};
#endif

#ifndef __H_COMPOSE__
#define __H_COMPOSE__
#include "opengl_interfaz.h"
#include "composer.h"
class ComposePostProcess : public Command{
public:
  ComposePostProcess(Composer* composer);
  ComposePostProcess();
  void runCommand()const;
private:
  Composer* composer_;

};
#endif

#ifndef __H_END_POSTPROCESS__
#define __H_END_POSTPROCESS__
#include "command.h"
#include "../post_process.h"
#include "opengl_interfaz.h"
class PostProcessEnd : public Command{
public:
  PostProcessEnd(PostProcess*  post_p,FrameBuffer*  last_fb);
 ~ PostProcessEnd(){}
  void runCommand()const;
private:

  PostProcess*  post_p_;
  FrameBuffer* last_fb_;

};

#endif



#ifndef __H_RENDER_COMPOSER__
#define __H_RENDER_COMPOSER__
#include "command.h"
#include "composer.h"
class RenderComposer : public Command{
public:
  RenderComposer(Composer *comp);
  ~RenderComposer(){}
  void runCommand()const;
private:

  Composer *composer_;


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
  bool shadow_buffer_created_=false;
  GLuint  depth_buffer_id__;
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


  std::shared_ptr<Material> shadow_shader_;

	List listCommand_;

  List post_process_commands_;
  List shadowList_;

};


#endif

	