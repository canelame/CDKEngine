#ifndef __H_COMMAND__
#define __H_COMMAND__

class OpenGlInterFaz;

class Command{
public:


 // Command();
//  ~Command();
  /**
  * @brief This commands run OpenGL code, in subclasses.
  * 
  */
	
	virtual void runCommand( OpenGlInterFaz &in)const = 0;

protected:
 
};



#endif

