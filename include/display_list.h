#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include <list>
#include "command.h"

class DisplayList: public Command{
public:

	void addCommand(const Commands& c);
	virtual void runCommand()const = 0;
private:
	std::list<Commands> display_list_;


};

void inline  DisplayList::addCommand(const Commands& c) {
	display_list_.push_back(c);

}

#endif

	