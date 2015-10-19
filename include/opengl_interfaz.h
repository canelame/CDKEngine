#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__
#include<memory>
class Buffer;
class Material;

class OpenGlInterFaz{
public:
	OpenGlInterFaz(){
		
	};
	void useGeometry();
	void useMaterial();
	void useDrawGeometry();
	~OpenGlInterFaz();
private:
	Buffer *buf__ptr;
	Material * matM;



};

#endif