#include "opengl_interfaz.h"
#include "buffer.h"
#include "material.h"

void OpenGlInterFaz::useGeometry(Buffer *b){
	buf__ptr = b;
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
	glBindVertexArray(*buf__ptr->getVAO());
}
void OpenGlInterFaz::useMaterial(Material *m){
	mat_ptr_ = m;
	if (!mat_ptr_->is_compiled_){
		//GLuint prog = mat_ptr_->getProgram();
		mat_ptr_->program_ = glCreateProgram();

		mat_ptr_->vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
		GLint lenght = strlen(mat_ptr_->vertex_data_);
		glShaderSource(mat_ptr_->vertex_shader_, 1, &mat_ptr_->vertex_data_, &lenght);
		mat_ptr_->compileShader(mat_ptr_->vertex_shader_);

		//FRAGENT SHADER

		mat_ptr_->fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(mat_ptr_->fragment_shader_, 1, &mat_ptr_->fragment_data_, &lenght);
		mat_ptr_->compileShader(mat_ptr_->fragment_shader_);

		glLinkProgram(mat_ptr_->program_);
		GLint program_compiled;
		glGetProgramiv(mat_ptr_->program_, GL_COMPILE_STATUS, &program_compiled);

		
		if (program_compiled == GL_FALSE){
			GLchar info_log[512];
			glGetProgramInfoLog(mat_ptr_->program_, 512, NULL, info_log);
			printf("LINKED PROGRAM ERROR: %s\n", info_log);
		}
	}
}

void OpenGlInterFaz::useDrawGeometry(Buffer *b){
	glDrawElements(GL_TRIANGLES, b->indexes_.size(),GL_UNSIGNED_INT, &b->indexes_[0]);
}
