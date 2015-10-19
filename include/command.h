#ifndef __H_COMMAND__
#define __H_COMMAND__


class Command{
public:
 // Command();
//  ~Command();
  /**
  * @brief This commands run OpenGL code, in subclasses.
  * @return Return command executed.
  */
	virtual int runCommand()const =0;
  virtual void add()const=0;
protected:
  enum Commands{
    USE_GEOMETRY=0,
    USE_MATERIAL,
  };
};



#endif

