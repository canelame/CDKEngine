#ifndef __H_COMMAND__
#define __H_COMMAND__

class OpenGlInterFaz;

class Command{
public:
	enum Commands{
		USE_GEOMETRY = 0,
		LOAD_GEOMETRY,
		USE_MATERIAL,
		LOAD_MATERIAL,

	};

 // Command();
//  ~Command();
  /**
  * @brief This commands run OpenGL code, in subclasses.
  * @return Return command executed.
  */
	
	virtual void runCommand( OpenGlInterFaz in, OpenGlInterFaz &out)const = 0;

protected:
 
};



#endif

