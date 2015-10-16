#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include <list>
#include "command.h"

class DisplayList: public Command{
public:

  void runCommand(int c)const{}
private:
	std::map<Commands,int> display_list_;


};


#endif

	