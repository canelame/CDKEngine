#ifndef __H_BUFFER__
#define __H_BUFFER__


#include <vector>
#include <memory>
#include <list>
#include "GL\glew.h"
#include "opengl_interfaz.h"
/**
* buffer.h
* @author Alejandro Canela Mendez
* @brief This class represents a buffer.
*/
class Buffer{

public:
  struct Data;
  Buffer();
  /**
  * @brief This function is used to load the attributes for a mesh. This attributes are,
  * positions, normals , uvs and indices.
  * 
  * The order of the attributes it's important. You must order the data in group of three ,that
  * represents a vertex.

  * Example:
  * 
  *  1.0, 1.0 ,1.0 Vertex 1
  *  0.0, 0.0 ,0.0 Vertex 2
  *  1.0, 0.0 ,1.0 Vertex 2
  *  ..... 
  * ......
  * @param positions Position attributes, all vertex of the mesh must be ordered.
  * @param normals  Normal attributes, all normals must be ordered.
  * @param uvs Texture coordinate , all uvs must be in order.
  * @param indexes Indexes to the mesh, must be in order respect the other attributes.

  */
	void loadData(std::vector<float>positions, std::vector<float>normals, std::vector<float>uvs,
	              std::vector<unsigned int> indexes);
  /**
  * @brif This function initilices the buffer whit size.
  * @param size Buffer size
  */
	void init(int size);
  /**
  * @brief Returns if the buffer has been modified.
  * @return Return true if the buffer has been modified, otherwise returns false;
  */
	bool isDirty();
  /**
  * @brief This function allow us to set if the buffer is dirty or not.
  * 
  */
  void setDirty(bool d);
  /**
  * @brief This function return where the vao is ;
  * @return Where the vao is binding.
  */
	GLuint* getVAO();
  /**
  * @brief This function return  vbos ;
  * @return Where the vbos is binding.
  */
	GLuint* getVBO();
  /**
  * @brief This function return three vectors, whose are the attributes. ;
  * @return Return three vectors.
  */
	std::vector<std::vector<float>> getAttributes();
  /**
  * @brief This function return the indices list ;
  * @return Indices list.
  */
	std::vector<unsigned int> getIndexes();
  /**
  * @brief This function is used to call opengl to use the geometry, and return the instance of
  opengl_interfaz.
  * @return A pointer to opengl_interfaz.
  */
	OpenGlInterFaz* useGeometry();

	OpenGlInterFaz* useDrawGeometry();
  /**
  * @brief This function is used to call opengl to draw the geomtry, and return the instance of
  opengl_interfaz.
  * @return A pointer to opengl_interfaz.
  */
	friend class OpenGlInterFaz;
		friend class OpenGlInterFaz;
private:
  Data *data_;
  
};




#endif