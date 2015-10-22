#ifndef __H_LISTCOMMAND__
#define __H_LISTCOMMAND__

#include "command.h"
#include <deque>
#include <memory>
#include <vector>
#include "opengl_interfaz.h"
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

  List listCommand_;
  DisplayList(){
	 
	  interfaz_ = std::make_unique<OpenGlInterFaz>();
	  
  }
  ~DisplayList(){}
  int size(){ return 0; }
  void runCommand()const{};
  void add( Comm_ c){
	  listCommand_.push_back(c);
   }
  void execute(){
    for (int i = 0; i < listCommand_.size(); ++i){
		listCommand_[i].get()->runCommand(*interfaz_.get(),*interfaz_.get());
    }
   
  };
private:
	std::unique_ptr<OpenGlInterFaz> interfaz_;
};


#endif

	