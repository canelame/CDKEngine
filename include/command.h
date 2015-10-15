#ifndef __H_COMMAND__
#define __H_COMMAND__


class Command{
public:
		enum Commands{
			USE_GEOMETY_ = 0,
			USE_MATERIAL,
			DRAW_SCENE
		};
	
	virtual void runCommand()const =0;
	virtual void addComand()const=0;

};



#endif

