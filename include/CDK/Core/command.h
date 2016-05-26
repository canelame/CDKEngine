#ifndef __H_COMMAND__
#define __H_COMMAND__


/**
* command.h
* @author Alejandro Canela Mendez 2015.
* @brief This class represent a command .
*
*/

class Command{
public:

  /**
  * @brief This commands run OpenGL code, in subclasses.
  * 
  */
	virtual void runCommand()const = 0;

};



#endif

