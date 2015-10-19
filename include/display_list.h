#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include "command.h"
#include <deque>
#include <memory>
/**
* command.h
* @author Alejandro Canela Mendez
* @brief This class makes a representation of an abstract DisplayList, we can add commands to the DL, 
* this commands will be executed in render fucntion.
*/
class DisplayList{
public:

  typedef std::shared_ptr<Command> Comm;
  typedef std::deque < Comm > List;

  List listCommand_;
  DisplayList(){}
  ~DisplayList(){}
  int size(){ return listCommand_.size(); }
  void add( Comm command){
    listCommand_.push_back(command);
  }
  void execute(){
    for (int i = 0; i < listCommand_.size(); ++i){
      listCommand_[i].get()->runCommand();
    }
   
  };

};


#endif

	