#include "opengl_interfaz.h"
#include "buffer.h"

void OpenGlInterFaz::useGeometry(){
	if (buf__ptr->isDirty()){
		GLuint *vao = buf__ptr->getVAO();
		GLuint* vbo = buf__ptr->getVBO();
		std::vector<float > *attrib = buf__ptr->getAttributes();
		std::vector<unsigned int> index = buf__ptr->getIndexes();
		glGenVertexArrays(1, vao);
		glBindVertexArray(*vao);

		glGenBuffers(4, vbo);
		//Load positions
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, attrib[0].size()*sizeof(float), &attrib[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//Load normals
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, attrib[1].size()*sizeof(float), &attrib[1], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
		glEnableVertexAttribArray(1);
		//Load uvs
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, attrib[2].size()*sizeof(float), &attrib[2], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
		//Indexes
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()*sizeof(unsigned int), &index, GL_STATIC_DRAW);
		
		glBindVertexArray(0);
		buf__ptr->setDirty(true);
	}
	
}
