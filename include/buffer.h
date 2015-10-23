#ifndef __H_BUFFER__
#define __H_BUFFER__
#include "GL\glew.h"
#include <vector>
#include <memory>
#include <list>
#include "opengl_interfaz.h"
class Buffer{

public:
	Buffer(){ 
  		interface_=new OpenGlInterFaz(); 
	};
	void loadData(std::vector<float>positions, std::vector<float>normals, std::vector<float>uvs,
				std::vector<unsigned int> indexes);
	
	void init(int size);

	bool isDirty();
	GLuint* getVAO();
	GLuint* getVBO();
	std::vector<std::vector<float>> getAttributes();
	std::vector<unsigned int> getIndexes();
	OpenGlInterFaz* useGeometry();
	OpenGlInterFaz* useDrawGeometry();
	void setDirty(bool d);
private:

	bool dirty_;
	int size_;
	std::vector<float>positions_;
	std::vector<float>normals_;
	std::vector<float>uvs_;
	std::vector<unsigned int>indexes_;
	OpenGlInterFaz *interface_;
	 GLuint vao_;
	 GLuint vbo_[4]; //0 positions, 1 normals, 2 uvs,3 indexes;
	 friend OpenGlInterFaz;
};




#endif