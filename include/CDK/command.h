#ifndef __H_COMMAND__
#define __H_COMMAND__

class OpenGlInterFaz;
/**
* command.h
* @author Alejandro Canela Mendez 2015.
* @brief This class represent a command .
*
*/

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

