/**
@author Alejandro Canela Mendez
ESAT 2016.
*/
///////////////////////////////////////// THIS PART OF FILE , MANAGE DIFERENT CLASSES OF TYPE COMMANDS, THAT REPRESENTS THE ///////////////////////////////////////////// 
///////////////////////////////////////// DISPLAY LIST TASK. ONLY PROGRAM PORPOUSE. NOT FOR THE USER OF LIBRARY             /////////////////////////////////////////////


///DRAW COMMAND CLASS
#ifndef __H_DRAW_COMMAND__
#define __H_DRAW_COMMAND__
#include "CDK/Core/command.h"
#include "CDK/Core/opengl_interfaz.h"
#include "CDK/Resources/geometry.h"
class DrawCommand : public Command{
public:
  /**
  @brief Constructor
  @param g Geometry buffer to load
  */
	DrawCommand(Buffer* g);
  /**
  @brief Reimplemented method , to give funtionality
  */
	void runCommand()const;
private:
  Buffer *t_geo;

};
#endif
#ifndef __H_BIND_SCREEN_COMMAND__
#define __H_BIND_SCREEN_COMMAND__
#include "CDK/Core/command.h"
#include "CDK/Core/opengl_interfaz.h"

class BindScreen : public Command{
public:
  /**
  @brief Constructor
  @param g Geometry buffer to load
  */
  BindScreen();
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:


};
#endif


#ifndef __H_BEGIN_RENDER_COMMAND__
#define __H_BEGIN_RENDER_COMMAND__
#include "CDK/Core/command.h"
#include "CDK/Core/opengl_interfaz.h"
class BeginRender : public Command{
public:
  /**
  @brief Constructor
  @param g Geometry buffer to load
  */
  BeginRender();
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:


};
#endif

///SHADOWS COMMAND CLASS

#ifndef __RENDER_SHADOW_MAP__
#define __RENDER_SHADOW_MAP__

class RenderDirectionalShadowMapCommand : public Command{
public:
  /**
  @brief Constructor
  @param Light to create depth map
  */
  RenderDirectionalShadowMapCommand(Light * l);
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:
  Light *light_;

};
#endif

#ifndef __RENDER_POINT_SHADOW_MAP__
#define __RENDER_POINT_SHADOW_MAP__

class RenderPointShadowMapCommand : public Command{
public:
  /**
  @brief Constructor
  @param l Light to create depth map
  */
  RenderPointShadowMapCommand(Light *l);
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:
  PointLight *light_;
};
#endif

#ifndef __RENDER_SPOT_SHADOW_MAP__
#define __RENDER_SPOT_SHADOW_MAP__
#include "CDK/Lights/spot_light.h"
class RenderSpotShadowMapCommand : public Command{
public:
  /**
  @brief Constructor
  @param l Light to create depth map
  */
  RenderSpotShadowMapCommand(Light * l, int face);
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:
  SpotLight *light_;

};
#endif

//
#ifndef __H_SEND_OBJECT_SHADOW__
#define __H_SEND_OBJECT_SHADOW__
class SendObjectShadow : public Command{
public:
  /**
  @brief Constructor
  @param g Object buffer 
  @param m Model mat for the object 
  @param is_directional Set if is a directional or not
  */
  SendObjectShadow(Buffer *g,mat4 m,bool is_directional);
  /**
  @brief Constructor
  */
  SendObjectShadow(){}
  /**
  @brief Reimplemented method , to give funtionality
  */
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
#include "CDK/Core/command.h"
#include "CDK/Material/material.h"
#include "CDK/Core/opengl_interfaz.h"
class UseMaterialCommand : public Command{
public:
  /**
  @brief Constructor
  @param mat Material to use
  */
	UseMaterialCommand(Material *mat);
  /**
  @brief Destructor
  */
  UseMaterialCommand(){}
  /**
  @brief Reimplemented method , to give funtionality
  */
	void runCommand()const;
private:
  Material *material_;

};
#endif

#ifndef __H_USE_MATERIAL_UNIFORMS_COMMAND__
#define __H_USE_MATERIAL_UNIFORMS_COMMAND__
#include "CDK/Core/command.h"
#include "CDK/Material/material.h"
#include "CDK/Core/opengl_interfaz.h"
class UseMaterialUniformsCommand : public Command{
public:
  /**
  @brief Constructor
  @param mat Material to use
  @param m Material settings to use
  @param projection Cam projection
  @param view Cam view
  @param model Cam model
  @param lights point lights
  @param dir_light Dir light
  */
  UseMaterialUniformsCommand( Material* mat,Material::MaterialSettings *mat_s,
    mat4 projection,mat4 view,mat4 model, std::vector<std::shared_ptr<Light>> lights, Light *dir_light);
  /**
  @brief Constructor
  */
  UseMaterialUniformsCommand(){}
  /**
  @brief Reimplemented method , to give funtionality
  */
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
#include "CDK/Core/command.h"
#include "CDK/PostProcess/post_process.h"
#include "CDK/Core/opengl_interfaz.h"
class PostProcessBegin : public Command{
public:
  /**
  @brief Constructor
  */
  PostProcessBegin(FrameBuffer* fb,PostProcess * mat);
  /**
  @brief Destructor
  */
  PostProcessBegin();
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:

  FrameBuffer *fb_ptr_;
  PostProcess * post_p_;
};
#endif

#ifndef __H_COMPOSE__
#define __H_COMPOSE__
#include "CDK/Core/opengl_interfaz.h"
#include "CDK/PostProcess/composer.h"
class ComposePostProcess : public Command{
public:
  /**
  @brief Constructor
  */
  ComposePostProcess(Composer* composer);
  /**
  @brief Destructor
  */
  ComposePostProcess();
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:
  Composer* composer_;

};
#endif





#ifndef __H_RENDER_COMPOSER__
#define __H_RENDER_COMPOSER__
#include "CDK/Core/command.h"
#include "CDK/PostProcess/composer.h"
/**
@brief Render post-process to their frambuffer
*/
class RenderComposer : public Command{
public:
  /**
  @brief Constructor
  */
  RenderComposer(Composer *comp);
  /**
  @brief Destructor
  */
  ~RenderComposer(){}
  /**
  @brief Reimplemented method , to give funtionality
  */
  void runCommand()const;
private:

  Composer *composer_;


};

#endif
/////////////////////////////////////////////////// END OF DISPLAY LIST TASK HEADER //////////////////////////////


/////////////////////////////////////////////////// START DISPLAY CLASS///////////////////////////////////////////
#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include "CDK/Core/command.h"
#include <memory>
#include <vector>

/**
* command.h
* @author Alejandro Canela Mendez
* @brief This class makes a representation of an abstract DisplayList, we can add commands to the DL,
* this commands will be executed in render fucntion.
*/

class DisplayList{

public:
  typedef std::shared_ptr<Command> Comm_;
  typedef std::vector < Comm_ > List;
  DisplayList();
	/**
	@brief Destructor
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
  /**
  *@brief Execute displaylist to render scene
  */
  void renderScene();

  //////////////////////
	List listCommand_;

};


#endif

	