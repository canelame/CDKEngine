#ifndef __H_OPENGL_INTERFAZ__
#define __H_OPENGL_INTERFAZ__
#include<memory>
class Buffer;
class Material;

class OpenGlInterFaz{
public:
	OpenGlInterFaz(){
		
	};
	void useGeometry(Buffer *f);
	void useMaterial(Material *m);
	void useDrawGeometry(Buffer *b);
	~OpenGlInterFaz();
private:
	Buffer *buf__ptr;
	Material * mat_ptr_;



};

#endif